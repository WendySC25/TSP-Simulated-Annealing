#include <iostream>
#include <sqlite3.h>
#include "tsp/model/City.hpp"
#include "tsp/io/FileReader.hpp"
#include "tsp/db/CityDatabase.hpp"

using namespace std;

int main() {
    try {

        // Temporalmente ...
        std::string dir = "/Users/wendysc/Desktop/E/Ciencias/Semestre7/HDCO/TSP-Simulated-Annealing/data/inputs/input-3.tsp";
        std::vector<int> ids = readFile(dir);

        // Temporalmente ...
        std::string database = "/Users/wendysc/Desktop/E/Ciencias/Semestre7/HDCO/TSP-Simulated-Annealing/data/db/tsp.db";
        CityDatabase db(database);
        
        std::vector<std::vector<double> > matriz = db.getAdjMatrix(ids);

        for (vector<double>& row : matriz) {
            for (double& d : row ){
                std::cout << d << " \t\t\t";
            }
            std::cout << "\n";
        }
            
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}