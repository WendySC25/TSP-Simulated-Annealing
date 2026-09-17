#pragma once
#include "RunConfig.hpp"

/**
 * @brief Stores the output and metrics of a completed Simulated Annealing experiment.
 */
struct RunResult {
    /** The configuration used for this execution. */
    RunConfig config;
    
    /** The sequence of city IDs representing the optimized route. */
    std::vector<int> finalPath;   
    
    /** Date and time when the experiment finished. */
    std::string timestamp;   

    /** Cost of the solution before optimization. */
    double initialCost = 0.0;   
    
    /** Computed starting temperature for the algorithm. */
    double initialTemperature = 0.0;
    
    /** Cost of the final optimized solution. */
    double finalCost = 0.0;
    
    /** Total execution time in milliseconds. */
    long long elapsedMs = 0;
};