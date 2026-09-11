#pragma once
#include <string>

struct RunConfig {
    std::string label = "";
    int         seed;

    // Initial Temperature parameters
    double targetP;
    double epsilonP;
    double initialT;
    int    tempSample;
    
    // Simulated Annealing
    int    batch;
    int    maxAttempts;
    double coolingFactor;
    double epsilon;
};


