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
#include "tsp/experiment/ExperimentRunner.hpp"
#include "tsp/experiment/ExperimentReporter.hpp"

using namespace std;

int main(int argc, char** argv) {
    try {

        auto optsOpt = parseArgs(argc, argv);
        if (!optsOpt) {
            std::cout << "Ups ..." << std::endl;
            return 1;
        }

        std::string outDir  = "./results/sep11/bestSolution.csv";
        const Args opts = *optsOpt;    
        std::vector<int> ids = readFile(opts.instancePath);

        CityDatabase db(opts.dbPath);
        std::vector<City>       cities = db.getCities(ids);
        std::vector<Connection> connections = db.getConnections(ids);

        EnvironmentTSP env(cities, connections);

        RunConfig config = {
            .seed = opts.seed, 
            .epsilonP = opts.epsilonP,
            .targetP = opts.targetP,
            .initialT = opts.initialT,
            .tempSample = opts.tempSample,
            .coolingFactor = opts.coolingFactor,
            .epsilon = opts.epsilon,
            .batch = opts.batchSize,
            .maxAttempts = opts.maxAttempts,
            .label = "exp12"
        };

        std::vector<RunConfig> allConfigs;
        allConfigs.push_back(config);
        ExperimentRunner runner(env.getMatrix(), env.getNormalizer(), 0);
        std::vector<RunResult> results = runner.run(allConfigs);

        double best = std::numeric_limits<double>::infinity();
        int bestId = -1;
        for(size_t i = 0; i < results.size(); ++i){
            if(results[i].finalCost < best){
                best = results[i].finalCost;
                bestId = static_cast<int>(i);
            }
        }

        std::cout << "Best cost: " << best << std::endl;

        ExperimentReporter repporter;
        repporter.generateReportCSV(outDir, results);


    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}