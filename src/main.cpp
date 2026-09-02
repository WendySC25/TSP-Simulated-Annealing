#include <iostream>
#include <sqlite3.h>
#include "tsp/model/City.hpp"
#include "tsp/model/Connection.hpp"
#include "tsp/io/FileReader.hpp"
#include "tsp/db/CityDatabase.hpp"
#include "tsp/core/SolutionTSP.hpp"
#include "tsp/core/EnvironmentTSP.hpp"
#include "tsp/heuristic/InitialTemperature.cpp"

using namespace std;

int main() {
    try {

        // Temporalmente ...
        std::string dir = "/Users/wendysc/Desktop/E/Ciencias/Semestre7/HDCO/TSP-Simulated-Annealing/data/inputs/input-40.tsp";
        std::vector<int> ids = readFile(dir);

        // Temporalmente ...
        std::string database = "/Users/wendysc/Desktop/E/Ciencias/Semestre7/HDCO/TSP-Simulated-Annealing/data/db/tsp.db";
        CityDatabase db(database);
        std::vector<City> cities = db.getCities(ids);
        std::vector<Connection> connections = db.getConnections(ids);

        EnvironmentTSP env(cities, connections);
        SolutionTSP s(ids, env.getMatrix(), env.getNormalizer(), 25);

        InitialTemperature temp(0.01,0.95,8,100);
        cout << temp.computeInitialT(s) << endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}