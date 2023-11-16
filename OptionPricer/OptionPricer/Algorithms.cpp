#include "Algorithms.hpp"
#include "IO.hpp"
#include <iostream>
#include <vector>
#include </Users/aaryangulia/Downloads/boost_1_82_0/boost/math/distributions/normal.hpp>

Algorithms::ModelSelector Algorithms::model;

const std::vector<double> Algorithms::price(double strike, double underlying, double rate, double vol, double timePeriod, double yield, int currType){
    switch (model) {
            
        case blackscholes_model:
            return BlackScholesModel::europeanPrice(strike, underlying, rate, vol, timePeriod);
            break;
            
        case binomial_model:
            int steps;
            std::cout<<"number of steps in binomial tree: ";
            IO::read(std::cin, steps);
            return BinomialModel::optionPrice(strike, underlying, rate, vol, timePeriod, yield, steps, currType);
            break;
            
        case montecarlo_model:
            std::cout<<"SELECT ANOTHER MODEL - MONTE-CARLO WILL BE HERE SOON!\n";
            return std::vector<double> {0,0};
            break;
            
        default:
            std::cout<<"SOMETHING WENT WRONG!!!";
    }
    return std::vector<double> {0,0};
}
//Black-Scholes Model for European call option: C(S,t) = S * N(d1) - K * exp(-r * T) N(d2)
//Using Put-Call parity, European put option: K * e^(r*T) - S + C(S,t)
//d1 = (log(S/K) + (r + v^2/2)T)/v*sqrt(T)
//d2 = d1 - v * sqrt(t)

//standard normal cumulative distribution function: N(d1) and N(d2)
double Algorithms::BlackScholesModel::normCdf(const double &x){
    
    //uses boost library nomarl distribution to calculate required CDF
    boost::math::normal_distribution<> normalDistribution;
    return boost::math::cdf(normalDistribution, x);
}

//calculates d1 and d2
const double Algorithms::BlackScholesModel::dj(const int &j, const double& strike, const double& underlying, const double& rate, const double& vol, const double& time) {
    return (log(strike/underlying) + (rate + (pow(-1,j-1))*0.5*vol*vol)*time)/(vol*(pow(time,0.5)));
}

//implements the blackschole model's solution for the european options
std::vector<double> Algorithms::BlackScholesModel::europeanPrice(const double& strike, const double& underlying, const double& rate, const double& vol, const double& time){
    
    double call_price = strike * normCdf(dj(1, strike, underlying, rate, vol, time))- underlying *exp(-rate*time) * normCdf(dj(2, strike, underlying, rate, vol, time));
    double put_price = underlying * exp(-rate*time) - strike + call_price;
    
    return std::vector<double> {call_price, put_price};
}


Algorithms::BinomialModel::hashMap Algorithms::BinomialModel::underlyingPrices(const double& strike, const double& underlying, const double& rate, const double& vol, const double& time, const double& yield, const int& steps){
    double u = upFactor(vol, dt(time,steps));
    double d = downFactor(vol, dt(time,steps));
    hashMap underlyingTree;
    for(int i = 0; i <= steps; i++){
        for(int j = 0; j <= i; j++){
            double node = underlying * pow(u ,i - j) * pow(d, j);
            std::vector<int>temp { i,j };
            underlyingTree[temp] = node;
        }
    }
    return underlyingTree;
}

std::vector<double> Algorithms::BinomialModel::optionPrice(const double& strike, const double& underlying, const double& rate, const double& vol, const double& time, const double& yield, int& steps, int& expType){
    double time_step = dt(time,steps);
    double u = upFactor(vol, time_step);
    double d = downFactor(vol, time_step);
    double rnp = riskNeutralProb(rate, yield, time_step, u, d);
    hashMap underlyingTree = underlyingPrices(strike,underlying,rate,vol,time,yield,steps);
    hashMap callTree;
    hashMap putTree;
    
    for(int i = 0; i <= steps; i++){
        callTree[{steps, i}] = exp(-rate * time_step) * std::max(double(0), underlyingTree[{steps, i}] - strike);
        putTree[{steps, i}] = exp(-rate * time_step) * std::max(double(0), strike - underlyingTree[{steps, i}]);
    }
    
    for(int i = steps - 1; i >= 0; i--){
        for(int j = 0; j <= i; j++){
            double node = exp(-rate * time_step) * (rnp * callTree[{i+1,j}] + (1 - rnp) * callTree[{i+1, j+1}]);
            callTree[{i,j}] = (expType == 1? node : std::max(node,exp(-rate * time_step * i) * std::max(double(0), underlyingTree[{i, j}] - strike)));
            node = (rnp * putTree[{i+1,j}] + (1 - rnp) * putTree[{i+1, j+1}]);
            putTree[{i,j}] = exp(-rate * time_step) * (expType == 1? node : std::max(node,exp(-rate * time_step * i) * std::max(double(0), strike - underlyingTree[{i, j}])));
        }
    }
    return std::vector<double> {callTree[{0,0}],putTree[{0,0}]};
}
