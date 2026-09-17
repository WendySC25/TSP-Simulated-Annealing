#include "TSPApp.hpp"

int TSPApp::run(const Args& opts) {
    
    std::vector<int> ids = readFile(opts.instancePath);

    CityDatabase db(opts.dbPath);
    std::vector<City> cities = db.getCities(ids);
    std::vector<Connection> connections = db.getConnections(ids);

    EnvironmentTSP env(cities, connections);

    RunConfig baseConfig = {
        .label = "exp_base",
        .seed = opts.seed, 
        .targetP = opts.targetP,
        .epsilonP = opts.epsilonP,
        .initialT = opts.initialT,
        .tempSample = opts.tempSample,
        .batch = opts.batchSize,
        .maxAttempts = opts.maxAttempts,
        .coolingFactor = opts.coolingFactor,
        .epsilon = opts.epsilon
    };

    std::vector<RunConfig> allConfigs;

    switch (opts.mode) {
        case ExecutionMode::Single:
            allConfigs.push_back(baseConfig);
            break;
            
        case ExecutionMode::Random:
            allConfigs = ExperimentRunner::generateRandomConfigs(opts.nRuns, baseConfig);
            break;
            
        case ExecutionMode::Seeds:
            allConfigs = ExperimentRunner::assignSeeds(opts.nRuns, baseConfig);
            break;
    }

    std::cout << "Starting experiments:\n\n";
    ExperimentRunner runner(env.getMatrix(), env.getNormalizer(), 0);
    std::vector<RunResult> results = runner.run(allConfigs);
    
    double bestCost = std::numeric_limits<double>::infinity();
    int bestId = -1;
    for (size_t i = 0; i < results.size(); ++i) {
        if (results[i].finalCost < bestCost) {
            bestCost = results[i].finalCost;
            bestId = i;
        }
    }

    auto bestInternalPath = results[bestId].finalPath;
    auto bestCoords = env.getPathCoords(bestInternalPath);

    for (auto& res : results) 
        res.finalPath = env.getPathIds(res.finalPath);
    
    auto bestRealPath = results[bestId].finalPath;

    ExperimentReporter reporter;

    std::string baseName = opts.outPath;
    size_t lastDot = baseName.find_last_of(".");
    if (lastDot != std::string::npos) 
        baseName = baseName.substr(0, lastDot);
    

    std::cout << "Execution finished. Best cost found: " << bestCost << "\n\n";

    std::cout << "Saving CSV report:\n";
    reporter.generateReportCSV(opts.outPath, results);
    
    std::cout << "Saving best solution path to " << baseName << ".tsp\n";
    reporter.generateSolutionFile(baseName + ".sol", bestRealPath);
    
    std::cout << "Saving best solution coordinates to " << baseName << ".coords\n";
    reporter.generateCoordsFile(baseName + ".coords", bestCoords);

    return 0;
}