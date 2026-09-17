#pragma once
#include <string>
#include <vector>

/**
 * @brief Configuration parameters for a single Simulated Annealing experiment.
 */
struct RunConfig {
    /** Identifier or label for this specific configuration. */
    std::string label = "";
    
    /** Seed. */
    int seed;

    // Initial Temperature parameters
    
    /** Target acceptance probability for initial temperature. */
    double targetP;
    
    /** Tolerance for the initial temperature search. */
    double epsilonP;
    
    /** Starting temperature. */
    double initialT;
    
    /** Sample size for temperature initialization. */
    int tempSample;
    
    // Simulated Annealing
    
    /** Number of iterations per temperature level. */
    int batch;
    
    /** Maximum consecutive temperature drops without improvement. */
    int maxAttempts;
    
    /** Multiplier for cooling the temperature. */
    double coolingFactor;
    
    /** Minimum temperature threshold to stop execution. */
    double epsilon;
};
