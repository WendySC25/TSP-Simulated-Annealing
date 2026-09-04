#include <iostream>
#include <sqlite3.h>
#include "tsp/model/City.hpp"
#include "tsp/model/Connection.hpp"
#include "tsp/io/FileReader.hpp"
#include "tsp/io/Args.hpp"
#include "tsp/db/CityDatabase.hpp"
#include "tsp/core/SolutionTSP.hpp"
#include "tsp/core/EnvironmentTSP.hpp"
#include "tsp/heuristic/InitialTemperature.hpp"
#include "tsp/heuristic/SimulatedAnnealing.hpp"

int main(int argc, char** argv) {
    try {
        auto optsOpt = parseArgs(argc, argv);
        if (!optsOpt) {
            std::cout << "Ups ..." << std::endl;
            return 1;
        }
        const Args opts = *optsOpt;

        std::vector<int> ids = readFile(opts.instancePath);

        CityDatabase db(opts.dbPath);
        std::vector<City>       cities = db.getCities(ids);
        std::vector<Connection> connections = db.getConnections(ids);

        EnvironmentTSP env(cities, connections);
        InitialTemperature temp(opts.epsilonP, opts.targetP, opts.initialT, opts.tempSample);
        SimulatedAnnealing sa(opts.coolingFactor, opts.epsilon, opts.batchSize, opts.maxAttempts); 
        SolutionTSP s(ids, env.getMatrix(), env.getNormalizer(), opts.seed);

        double ti = temp.computeInitialT(s);
        sa.run(ti, s);
        double finalCost = s.getCost();

        std::cout << "Semilla: " << opts.seed << std::endl;
        std::cout << "Mejor costo: " << finalCost << std::endl;
        std::cout << "Sol: " << s.toString() << std::endl; // Ay! Lon índices xd

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}