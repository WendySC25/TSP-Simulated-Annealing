#include <sqlite3.h>

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "../model/City.hpp"
#include "../model/Connection.hpp"

/**
 * @brief DAO. Manages database operations for retrieving City and Connection data using SQLite3.
 */

class CityDatabase {

    private:
        /** SQLite database connection */
        std::unique_ptr<sqlite3, decltype(&sqlite3_close)> db;

    public:
        /**
         * @brief Constructs the CityDatabase and initializes the connection.
         * 
         * @param sql_path Path to the SQL script used for setup or queries.
         * @param db_path Path to the SQLite database file (optional).
         */
        CityDatabase(const std::string& sql_path, const std::string& db_path = "");

        /**
         * @brief Retrieves a list of cities from the database based on their identifiers.
         * 
         * @param ids A sequence of city IDs to query.
         * @return A vector of populated City objects.
         */
        std::vector<City>       getCities(const std::vector<int>& ids);

        /**
         * @brief Retrieves a list of connections involving the specified cities.
         * 
         * @param ids A sequence of city IDs to query connections for.
         * @return A vector of Connection objects representing paths between the requested cities.
         */
        std::vector<Connection> getConnections(const std::vector<int>& ids);
};      