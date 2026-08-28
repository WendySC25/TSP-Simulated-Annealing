#include <sqlite3.h>

#include <string>
#include <iostream>
#include <vector>

#include "../model/City.hpp"
#include "../utils/Haversine.hpp"

class CityDatabase {

    private:
        std::unique_ptr<sqlite3, decltype(&sqlite3_close)> db;

    public:
        CityDatabase(const std::string& db_path);
        std::vector<std::unique_ptr<City> > getCities(const std::vector<int>& ids);
        std::vector<std::vector<double> >   getAdjMatrix(const std::vector<int>& ids);
};      