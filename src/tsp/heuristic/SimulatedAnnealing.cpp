#include "SimulatedAnnealing.hpp"

SimulatedAnnealing::SimulatedAnnealing(double cf, double e, int b, int n)
: coolingFactor(cf), epsilon(e), batch(b){
    ATTEMPS = n*n*2; 
}

SimulatedAnnealing::~SimulatedAnnealing(){}

void SimulatedAnnealing::run(double T, Solution &s){
    double p = 0;
    double bestCost = s.getCost();


    while(T > epsilon) {
        double q = std::numeric_limits<double>::infinity();
        while (p <= q){
            q = p;
            p = calculateBatch(T,s);

            if (p == 0) {
                // Hmmmm, no lo sé
                break; 
            }
            
            double currentCost = s.getCost();
            if (currentCost < bestCost) {
                bestCost = currentCost;
                s.saveBest();
            }
        }

        
        T = T*coolingFactor;
    }

    s.restoreBest();
}


double SimulatedAnnealing::calculateBatch(double T, Solution &s){
    int c = 0;
    double r = 0.0;
    int attemps = 0;
    while(c < batch && attemps < ATTEMPS){
        attemps++;
        double currentCost = s.getCost();
        double neightborhCost = s.proposeNeightborhCost();
        if( neightborhCost <= currentCost + T ) {
            c++;
            r += neightborhCost;
            s.acceptPropose();
        }   
    }

    if(c == 0) return 0.0;
    return r/static_cast<double>(c);
}

