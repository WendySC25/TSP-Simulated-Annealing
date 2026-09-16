#pragma once
#include<vector>
#include<random>
#include<algorithm>
#include "Solution.hpp"

class SolutionTSP : public Solution {
    private:    
 
        int              n;                                /*Number of cities*/
        std::vector<int> path;                             /*Solution path of cities*/
        double           normalizer;                       /*Normalizer*/
        const std::vector<std::vector<double> > & matrix;  /*Matrix*/
        std::mt19937     rd;                               /*Random number generator*/
        std::uniform_int_distribution<int>        uniform; /*Random number generator*/

        /*Proposed values*/
        int iP;
        int jP;
        double costP;

        std::vector<int> bestPath;
        double           bestSavedCost;

        bool useTwoOpt = true;

        void generateSolution(){
            path.resize(n);
            for(int i = 0; i < n; i++) path[i] = i; 
            std::shuffle(path.begin(), path.end(), rd);
        }

    public:
        SolutionTSP(const std::vector<int> &ids, const std::vector<std::vector<double> > & m, double norm, int seed);
        SolutionTSP(const std::vector<std::vector<double> > & matrix, double normalizer, int seed);
        double getSwapCost(int i, int j);
        std::vector<int> getPath();

        double proposeNeightborhCost() override;
        void acceptPropose() override;
        double evaluate() override;
        std::string toString() override;

        void saveBest() override;
        void restoreBest() override;
    
        double getTwoOptCost(int i, int j);

        bool isFactible();

};