#pragma once
#include <vector>
#include <thread>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>
#include <algorithm>
#include <random>

#include "RunConfig.hpp"
#include "RunResult.hpp"
#include "tsp/core/SolutionTSP.hpp"
#include "tsp/heuristic/InitialTemperature.hpp"
#include "tsp/heuristic/SimulatedAnnealing.hpp"

class ExperimentRunner {
    private:
        const std::vector<std::vector<double> > &matrix;
        double normalizer;
        int    numThreads;
        
        std::string nowTimestamp();
        RunResult runOne(const RunConfig &cfg);
        void worker(const std::vector<RunConfig> &configs, std::vector<RunResult> &results, size_t begin, size_t end);

    public:
        ExperimentRunner(const std::vector<std::vector<double> > &matrix, double normalizer, int numThreads = 0);
        std::vector<RunResult> run(const std::vector<RunConfig> &configs);
        
        static std::vector<RunConfig> assignSeeds(int numSeeds, const RunConfig &baseCofig);
        static std::vector<RunConfig> generateRandomConfigs(int numExperiments, const RunConfig &baseConfig);
};
