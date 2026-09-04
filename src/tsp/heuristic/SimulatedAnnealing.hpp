#include "tsp/core/Solution.hpp"
#include <limits>
#include<iostream>

class SimulatedAnnealing{
private:
    double coolingFactor;
    double epsilon;
    int    batchSize;
    int    maxAttemps;

public:
    SimulatedAnnealing(double coolingFactor, double epsilon, int batch, int attemps);
    ~SimulatedAnnealing();

    void run(double T, Solution &s);
    double calculateBatch(double T, Solution &s);
};
