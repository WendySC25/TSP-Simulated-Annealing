#include "CityDatabase.hpp"

CityDatabase::CityDatabase(const std::string& db_path) : db(nullptr, sqlite3_close) {

    sqlite3* ppDb = nullptr;
    
    if (sqlite3_open(db_path.c_str(), &ppDb) != SQLITE_OK) {
        std::string err = sqlite3_errmsg(ppDb);
        sqlite3_close(ppDb);
        throw std::runtime_error("DB error: " + err);
    }

    db.reset(ppDb);
}

std::vector<std::unique_ptr<City> > CityDatabase::getCities(const std::vector<int>& ids) {

    std::vector<std::unique_ptr<City> > cities;
    cities.reserve(ids.size()+1);
    
    const char* query = "SELECT id, name, latitude, longitude FROM cities WHERE id = ?";

    sqlite3_stmt* ppStmt = nullptr;
    if (sqlite3_prepare_v2(db.get(), query, -1, &ppStmt, nullptr) != SQLITE_OK) 
        throw std::runtime_error("Error query");
        
    std::unique_ptr<sqlite3_stmt, decltype(&sqlite3_finalize)> stmt(ppStmt, sqlite3_finalize);
    
    for (int id : ids){
        sqlite3_bind_int(stmt.get(), 1, id);
        
        if (sqlite3_step(stmt.get()) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt.get(), 0);
            std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 1));
            double lat = sqlite3_column_double(stmt.get(), 2);
            double lon = sqlite3_column_double(stmt.get(), 3);
            cities.push_back(std::make_unique<City>(id, name, lat, lon));
        }         
        sqlite3_reset(stmt.get());
    }
    
    return cities;
}

std::vector<std::vector<double> > CityDatabase::getAdjMatrix(const std::vector<int>& ids) {
    
    int n = ids.size();
    std::vector<std::vector<double> > matrix(n, std::vector<double>(n, -1.0));
    std::vector<std::unique_ptr<City> > cities = getCities(ids);
    std::unordered_map<int, int> idToIndex;
    
    for (int i = 0; i < n; ++i) {
        matrix[i][i] = 0.0;
        idToIndex[cities[i]->id] = i;
    }
    
    const char* query = "SELECT id_city_2, distance FROM connections WHERE id_city_1 = ?";

    sqlite3_stmt* ppStmt = nullptr;
    if (sqlite3_prepare_v2(db.get(), query, -1, &ppStmt, nullptr) != SQLITE_OK) 
        throw std::runtime_error("Error with connection table");
        
    std::unique_ptr<sqlite3_stmt, decltype(&sqlite3_finalize)> stmt(ppStmt, sqlite3_finalize);
    double maxDS = -1e9; // QUÉ PASA SI NO HAY NINGUNA SOLUCIÓN FACTIBLE?
    
    for(int i = 0; i < n; ++i) {
        sqlite3_bind_int(stmt.get(), 1, ids[i]);
        while (sqlite3_step(stmt.get()) == SQLITE_ROW) {
            int idFinal = sqlite3_column_int(stmt.get(), 0);
            auto it = idToIndex.find(idFinal);
            if (it != idToIndex.end()) {
                int j = it->second;
                double dist = sqlite3_column_double(stmt.get(), 1);
                matrix[i][j] = dist;
                matrix[j][i] = dist;
                if (dist > maxDS) maxDS = dist;
            } else {
                std::cout << "Hmmmm ..." << std::endl;
            }
        }
        sqlite3_reset(stmt.get());
    }
    
    if(maxDS == -1e9) maxDS = R; 
    std::cout << "DisMax" << maxDS << std::endl;
    
    for(int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] < 0.0) {
                double dist = getNaturalDistance(cities[i]->latitude, cities[i]->longitude, cities[j]->latitude, cities[j]->longitude);
                matrix[i][j] = dist * maxDS;
            }
        }
    }
            
    return matrix;
}

