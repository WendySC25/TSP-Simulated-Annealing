#pragma once
#include "tsp/core/Solution.hpp"
#include <limits>
#include<iostream>

/**
 * @brief Executes the Simulated Annealing metaheuristic optimization by threshold accepting.
 */
class SimulatedAnnealing{
private:

    /** Multiplier used to reduce the temperature. */
    double coolingFactor;

    /** Minimum temperature threshold to stop the algorithm. */
    double epsilon;

    /** Number of iterations evaluated at each temperature step. */
    int    batchSize;

    /** Maximum consecutive temperature drops without improvement. */
    int    maxAttemps;

public:
    SimulatedAnnealing(double coolingFactor, double epsilon, int batch, int attemps);
    ~SimulatedAnnealing();

    /**
     * @brief Starts the optimization process.
     * 
     * @param T The initial starting temperature.
     * @param s Reference to the solution to be optimized.
     */
    void run(double T, Solution &s);

    /**
     * @brief Starts the optimization process.
     * 
     * @param T The initial starting temperature.
     * @param s Reference to the solution to be optimized.
     */
    double calculateBatch(double T, Solution &s);
};
