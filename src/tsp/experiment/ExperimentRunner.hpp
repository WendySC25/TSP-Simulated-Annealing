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

/**
 * @brief Manages and executes single or multi-threaded Simulated Annealing experiments.
 */
class ExperimentRunner {
    private:
        /** Reference to the distance matrix between cities. */
        const std::vector<std::vector<double> > &matrix;

        /** Normalizer. */
        double normalizer;

        /** Number of concurrent threads to use for execution. */
        int    numThreads;
        
        /**
         * @brief Generates a string representation of the current time.
         * @return The formatted timestamp.
         */
        std::string nowTimestamp();

        /**
         * @brief Executes a single experiment configuration.
         * @param cfg The configuration to run.
         * @return The results of the execution.
         */
        RunResult runOne(const RunConfig &cfg);

        /**
         * @brief Thread worker function to process a subset of configurations.
         * @param configs List of configurations to run.
         * @param results Shared array to store the results.
         * @param begin Starting index for this thread.
         * @param end Ending index for this thread.
         */
        void worker(const std::vector<RunConfig> &configs, std::vector<RunResult> &results, size_t begin, size_t end);

    public:
        /**
         * @brief Constructs the ExperimentRunner.
         * 
         * @param matrix .
         * @param normalizer Value used to normalize costs/distances.
         * @param numThreads Number of threads to use (0 = auto-detect).
         */
        ExperimentRunner(const std::vector<std::vector<double> > &matrix, double normalizer, int numThreads = 0);

        /**
         * @brief Runs a batch of experiments based on the provided configurations.
         * 
         * @param configs A list of configurations to execute.
         * @return A list of results corresponding to each configuration.
         */
        std::vector<RunResult> run(const std::vector<RunConfig> &configs);
        
        /**
         * @brief Duplicates a base configuration with different random seeds.
         * 
         * @param numSeeds Number of configurations to generate.
         * @param baseCofig The base configuration template.
         * @return A list of configurations with unique seeds.
         */
        static std::vector<RunConfig> assignSeeds(int numSeeds, const RunConfig &baseCofig);

        /**
         * @brief Generates random configurations for hyperparameter exploration.
         * 
         * @param numExperiments Number of random configurations to generate.
         * @param baseConfig The baseline configuration to deviate from.
         * @return A list of random configurations.
         */
        static std::vector<RunConfig> generateRandomConfigs(int numExperiments, const RunConfig &baseConfig);
};
