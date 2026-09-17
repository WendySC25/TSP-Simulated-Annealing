#pragma once
#include "tsp/io/Args.hpp"
#include <iostream>
#include <limits>
#include "tsp/io/FileReader.hpp"
#include "tsp/db/CityDatabase.hpp"
#include "tsp/core/EnvironmentTSP.hpp"
#include "tsp/experiment/ExperimentRunner.hpp"
#include "tsp/experiment/ExperimentReporter.hpp"

/**
 * @brief Main application orchestrator for setting up and running TSP experiments.
 */
class TSPApp {
    public:
        /**
         * @brief Executes the main application logic based on parsed arguments.
         * 
         * @param opts Parsed command-line arguments.
         * @return 0 on success, other is failure.
         */
        int run(const Args& opts);
};


