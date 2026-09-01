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

std::vector<City> CityDatabase::getCities(const std::vector<int>& ids) {

    std::vector<City> cities;
    cities.reserve(ids.size());
    
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
            cities.emplace_back(id, name, lat, lon);
        }         
        sqlite3_reset(stmt.get());
    }
    
    return cities;
}

std::vector<Connection> CityDatabase::getConnections(const std::vector<int>& ids) {
    
    std::vector<Connection> connections;
    const char* query = "SELECT id_city_2, distance FROM connections WHERE id_city_1 = ?";

    sqlite3_stmt* ppStmt = nullptr;
    if (sqlite3_prepare_v2(db.get(), query, -1, &ppStmt, nullptr) != SQLITE_OK) 
        throw std::runtime_error("Error with connection table");
        
    std::unique_ptr<sqlite3_stmt, decltype(&sqlite3_finalize)> stmt(ppStmt, sqlite3_finalize);
    
    for(int id1 : ids) {
        sqlite3_bind_int(stmt.get(), 1, id1);
        
        while (sqlite3_step(stmt.get()) == SQLITE_ROW) {
            int id2 = sqlite3_column_int(stmt.get(), 0); 
            double d = sqlite3_column_double(stmt.get(), 1); 

            connections.emplace_back(id1, id2, d);
        }
        sqlite3_reset(stmt.get());
    }

    return connections;
}

