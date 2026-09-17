#pragma once
#include<vector>
#include<random>
#include<algorithm>
#include "tsp/heuristic/Solution.hpp"

/**
 * @brief Represents a specific solution for the Traveling Salesperson Problem (TSP).
 */
class SolutionTSP : public Solution {
    private:    
        /** Number of cities in the TSP instance. */
        int n;                                
        
        /** Ordered sequence of city indices representing the current route. */
        std::vector<int> path;                             
        
        /** Scaling factor for distance normalization. */
        double normalizer;                       
        
        /** Reference to the distance matrix between cities. */
        const std::vector<std::vector<double> > & matrix;  
        
        /** Random number generator. */
        std::mt19937 rd;                               
        
        /** Uniform integer distribution generator */
        std::uniform_int_distribution<int> uniform; 


        // Proposed values for the next neighborhood move
        
        /** First index proposed for a swap or 2-opt move. */
        int iP;
        
        /** Second index proposed for a swap or 2-opt move. */
        int jP;
        
        /** Cost of the proposed neighbor solution. */
        double costP;

        /** The best route found. */
        std::vector<int> bestPath;
        
        /** The cost of the best route found. */
        double bestSavedCost;

        /** Flag indicating whether to use the 2-opt neighborhood operator or simple swap. */
        bool useTwoOpt = true;

        /** @brief Initializes a random path permutation. */
        void generateSolution(){
            path.resize(n);
            for(int i = 0; i < n; i++) path[i] = i; 
            std::shuffle(path.begin(), path.end(), rd);
        }

    public:
        
        /**
         * @brief Constructs a TSP solution with specific city IDs.
         * 
         * @param ids Vector of city identifiers.
         * @param m Distance matrix.
         * @param norm Normalization factor.
         * @param seed Random number generator seed.
         */
        SolutionTSP(const std::vector<int> &ids, const std::vector<std::vector<double> > & m, double norm, int seed);

        /**
         * @brief Constructs a TSP solution using only the distance matrix. It will generate a random inicial solution.
         * 
         * @param matrix Distance matrix.
         * @param normalizer Normalization factor.
         * @param seed Random number generator seed.
         */
        SolutionTSP(const std::vector<std::vector<double> > & matrix, double normalizer, int seed);

        /**
         * @brief Calculates the cost difference of swapping cities at indices i and j.
         * 
         * @param i First index.
         * @param j Second index.
         * @return The delta cost of the swap.
         */
        double getSwapCost(int i, int j);

        double getTwoOptCost(int i, int j);

        /**
         * @brief Retrieves the current route.
         * @return The sequence of city indices.
         */
        std::vector<int> getPath();

        /**
         * @brief Verifies if the current solution is valid.
         * @return True if feasible, false otherwise.
         */
        bool isFactible();
        
        // Overridden methods from Solution base class
        double proposeNeightborhCost() override;
        void acceptPropose() override;
        double evaluate() override;
        std::string toString() override;
        void saveBest() override;
        void restoreBest() override;
        void scanning() override;

};