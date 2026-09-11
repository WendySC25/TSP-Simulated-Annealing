#include "SolutionTSP.hpp"

SolutionTSP::SolutionTSP(const std::vector<int> &ids, const std::vector<std::vector<double> > & m, double norm, int seed) 
: matrix(m), normalizer(norm), n(m.size()), path(ids), rd(seed), uniform(0,n-1){
    path.resize(n);
    for(int i = 0; i < n; i++) path[i] = i; 
    evaluate();
    saveBest();
}

SolutionTSP::SolutionTSP(const std::vector<std::vector<double> > & matrix, double normalizer, int seed) 
: matrix(matrix), normalizer(normalizer), n(matrix.size()), rd(seed), uniform(0,n-1){
    generateSolution();
    evaluate();
    saveBest();
}


double SolutionTSP::proposeNeightborhCost(){
    iP = uniform(rd);
    jP = uniform(rd);

    while(iP == jP) jP = uniform(rd);
            
    return getSwapCost(iP,jP);
}

void SolutionTSP::acceptPropose(){
    std::swap(path[iP], path[jP]);
    cost = costP;
}

double SolutionTSP::evaluate(){
    double acc = 0;
    for(int i = 1; i < n; i++) 
        acc += matrix[path[i]][path[i-1]];
    
    return cost = acc / normalizer;
 }

double SolutionTSP::getSwapCost(int i, int j){
    if (i == j) return cost;
    if (i > j) std::swap(i, j);
    
    double old = 0.0;
    double neww = 0.0;
    double delta = 0.0;
    
    int u = path[i];
    int v = path[j];
    
    if(i > 0) {
        old += matrix[path[i-1]][u];
        neww += matrix[path[i-1]][v];
    }
    
    if(j < n - 1) {
        old += matrix[v][path[j+1]];
        neww += matrix[u][path[j+1]];
    }
    
    if(i + 1 == j){
        old += matrix[u][v];
        neww += matrix[v][u];
    } else { 

        if(i < n - 1) { 
            old += matrix[u][path[i+1]];
            neww += matrix[v][path[i+1]];
        }
        
        if(j > 0) {
            old += matrix[path[j-1]][v];
            neww += matrix[path[j-1]][u];
        }
    }
    
    delta = (neww - old) / normalizer;
    costP = cost + delta;
    return costP;
}

std::vector<int> SolutionTSP::getPath(){
    return path;
}

std::string SolutionTSP::toString() {
    std::string s;
    for(auto i : path) {
        s.append(std::to_string(i));
        s.append("-");
    }
    s.append("\n");
    return s;
}

void SolutionTSP::saveBest(){
    bestPath = path;
    bestSavedCost = cost;
}

void SolutionTSP::restoreBest(){
    path = bestPath;
    cost = bestSavedCost;
}

bool SolutionTSP::isFactible(){
    return cost <= 1.0;
}
