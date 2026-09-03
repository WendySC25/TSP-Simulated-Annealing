#pragma once
#include<string>

class Solution {
    protected:
        double cost;

    public:
        virtual double proposeNeightborhCost() = 0;
        virtual void   acceptPropose() = 0;
        virtual double evaluate() = 0;
        virtual std::string toString() = 0;

        virtual void saveBest() = 0;
        virtual void restoreBest() = 0;
  
        double getCost(){
            return cost;
        }
};