#include "tsp/core/Solution.hpp"
#include <limits>
#include<iostream>

class SimulatedAnnealing{
private:
    double coolingFactor;
    double epsilon;
    int    batch;
    int    ATTEMPS;

public:
    SimulatedAnnealing(double cf, double e, int b, int n);
    ~SimulatedAnnealing();

    void run(double T, Solution &s);
    double calculateBatch(double T, Solution &s);
};
