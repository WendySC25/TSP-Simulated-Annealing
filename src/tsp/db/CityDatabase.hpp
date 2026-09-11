#include <sqlite3.h>

#include <string>
#include <iostream>
#include <vector>
#include <memory>

#include "../model/City.hpp"
#include "../model/Connection.hpp"

class CityDatabase {

    private:
        std::unique_ptr<sqlite3, decltype(&sqlite3_close)> db;

    public:
        CityDatabase(const std::string& db_path);
        std::vector<City>       getCities(const std::vector<int>& ids);
        std::vector<Connection> getConnections(const std::vector<int>& ids);
};      