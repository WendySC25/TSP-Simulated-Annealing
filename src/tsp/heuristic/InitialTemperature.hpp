#pragma once
#include "tsp/core/Solution.hpp"

class InitialTemperature{
    private:
        double epsilonP;
        double P;
        double initialT; 
        int    N;

    public:
        InitialTemperature(double epsilon, double acceptanceRate, double initT, int sampleSize);
        ~InitialTemperature();

        double binarySerchT(Solution &s, double T1, double T2);
        double computeInitialT(Solution &s);
        double calculateAcceptanceRate(Solution &s, double T);

};