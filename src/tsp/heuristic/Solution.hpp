#pragma once
#include<string>

/**
 * @brief Abstract base class representing a generic solution for optimization.
 */
class Solution {
    protected:
        /** Current cost or objective function value of the solution. */
        double cost;

    public:
        /**
         * @brief Proposes a new neighbor solution and calculates its cost.
         * @return The cost of the proposed neighbor solution.
         */
        virtual double proposeNeightborhCost() = 0;

        /**
         * @brief Accepts the previously proposed neighbor, making it the current solution.
         */
        virtual void   acceptPropose() = 0;

        /**
         * @brief Evaluates and updates the cost of the current solution.
         * @return The evaluated cost.
         */
        virtual double evaluate() = 0;

        /**
         * @brief Returns a string representation of the solution state.
         * @return Formatted string with solution details.
         */
        virtual std::string toString() = 0;

        /** @brief Saves the current solution as the best found so far. */
        virtual void saveBest() = 0;

        /** @brief Restores the solution state to the best found so far. */
        virtual void restoreBest() = 0;

        /** @brief Exhaustively evaluates the neighborhood. */
        virtual void scanning() = 0;

        /**
         * @brief Retrieves the current cost of the solution.
         * @return The current cost.
         */
        double getCost(){
            return cost;
        }
};