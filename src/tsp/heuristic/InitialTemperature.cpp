#include "InitialTemperature.hpp"

InitialTemperature::InitialTemperature(double epsilon, double acceptanceRate, double initT, int sampleSize)
: epsilonP(epsilon), P(acceptanceRate), initialT(initT), N(sampleSize) {}

InitialTemperature::~InitialTemperature(){}

double InitialTemperature::computeInitialT(Solution &s){
    double T = initialT;
    double p = calculateAcceptanceRate(s,T);
    if(std::fabs(P-p) <= epsilonP) return T;

    double T1,T2;
    if(p < P){
        while(p < P){
            T = 2 * T;
            p = calculateAcceptanceRate(s,T);
        }
        T1 = T/2;
        T2 = T;
    } else {
        while(p > P){
            T = T/2;
            p = calculateAcceptanceRate(s,T);
        }
        T1 = T;
        T2 = T*2;
    }

    return binarySerchT(s,T1,T2);
}

double InitialTemperature::calculateAcceptanceRate(Solution &s, double T){
    
    int acc = 0;
    int n;

    for(int i = 0; i < N; i++){
        double currentCost = s.getCost();
        double neightborhCost = s.proposeNeightborhCost();
        if( neightborhCost <= currentCost + T ) {
            acc++;
            s.acceptPropose();
        }   
    }
    return static_cast<double>(acc) / static_cast<double>(N);
}

double InitialTemperature::binarySerchT(Solution &s, double T1, double T2){
    
    double Tm = (T1+T2)/2.0;
    if(T2 - T1 < epsilonP) return Tm;

    double p = calculateAcceptanceRate(s, Tm);
    if(std::fabs(P-p) < epsilonP) return Tm;

    if(p > P) return binarySerchT(s,T1,Tm);
    else return binarySerchT(s,Tm,T2);

}
