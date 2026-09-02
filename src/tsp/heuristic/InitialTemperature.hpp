#include "tsp/core/Solution.hpp"

class InitialTemperature{
    private:
        double epsilonP ;
        double P ;
        double initialT; 
        int    N = 100;

    public:
        InitialTemperature(double e, double p, double t, int n);
        ~InitialTemperature();

        double binarySerchT(Solution &s, double T1, double T2, double P);
        double computeInitialT(Solution &s);
        double calculateAcceptanceRate(Solution &s, double T);

};