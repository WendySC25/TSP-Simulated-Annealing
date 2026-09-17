#pragma once
#include "tsp/core/Solution.hpp"

/**
 * @brief Computes the optimal initial temperature for Simulated Annealing.
 */
class InitialTemperature{
    private:
        /** Tolerance for the target acceptance rate. */
        double epsilonP;

        /** Target acceptance rate (probability). */
        double P;

        /** Starting point for the temperature search. */
        double initialT; 

        /** Sample size for estimating the acceptance rate. */
        int    N;

    public:
        InitialTemperature(double epsilon, double acceptanceRate, double initT, int sampleSize);
        ~InitialTemperature();

        /**
         * @brief Performs a binary search to find a temperature matching the target acceptance rate.
         * 
         * @param s Reference to the current solution.
         * @param T1 Lower bound temperature.
         * @param T2 Upper bound temperature.
         * @return The optimized initial temperature.
         */
        double binarySerchT(Solution &s, double T1, double T2);

        /**
         * @brief Computes the optimal initial temperature.
         * 
         * @param s Reference to the current solution.
         * @return The calculated initial temperature.
         */
        double computeInitialT(Solution &s);

        /**
         * @brief Estimates the acceptance rate for a given temperature.
         * 
         * @param s Reference to the current solution.
         * @param T The temperature to evaluate.
         * @return The estimated acceptance rate [0.0, 1.0].
         */
        double calculateAcceptanceRate(Solution &s, double T);

};