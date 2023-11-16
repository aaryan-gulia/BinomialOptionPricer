//
//  Algorithms.hpp
//  BinomialOptionPricer
//
//  Created by Aaryan Gulia on 15/11/2023.
//
#include <vector>
#include <unordered_map>

#ifndef Algorithms_hpp
#define Algorithms_hpp

struct VectorHasher {
    int operator()(const std::vector<int> &V) const {
        int hash = static_cast<int>(V.size());
        for(auto &i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

class Algorithms{
private:
    class BlackScholesModel;
    class BinomialModel;
    class MonteCarloPricer;
    
public:
    enum ModelSelector{
        binomial_model = 1,
        blackscholes_model = 2,
        montecarlo_model = 3
    };
    static ModelSelector model;
    friend std::istream& operator>>(std::istream& is, ModelSelector& currType);
    static const std::vector<double> price(double strike, double underlying, double rate, double vol, double timePeriod, double yield, int currType);
};

//C(S,t) = S * N(d1) - K * exp(-r * T) N(d2)
class Algorithms::BlackScholesModel{
private:
    static const double dj(const int &j, const double& strike, const double& underlying, const double& rate, const double& vol, const double& time);
    static double normCdf(const double &x);

    
public:
    static std::vector<double> europeanPrice(const double& strike, const double& underlying, const double& rate, const double& vol, const double& time);
    
};

class Algorithms::BinomialModel{
    typedef std::unordered_map<std::vector<int>,double,VectorHasher> hashMap;
private:
    //calculate constants required to create the binomial tree
    static inline double dt(const double& timePeriod, const int& steps){return timePeriod/steps;}
    static inline double upFactor(const double& vol, const double& dt){return std::exp(vol * std::sqrt(dt));}
    static inline double downFactor(const double& vol, const double& dt){return std::exp(-vol * std::sqrt(dt));}
    static inline double riskNeutralProb(const double& rate, const double& dividend, const double& dt, const double& upFactor, const double& downFactor){return (std::exp((rate - dividend) * dt) - downFactor)/(upFactor - downFactor);}
    
    //binomial tree of underlying prices. the vector in the unordered_map contains coordinate for each node [step, position]
    static hashMap underlyingPrices(const double& strike, const double& underlying, const double& rate, const double& vol, const double& time, const double& yield, const int& steps);
    
public:
    static std::vector<double> optionPrice(const double& strike, const double& underlying, const double& rate, const double& vol, const double& time, const double& yield, int& steps, int& expType);
};

#endif /* Algorithms_hpp */
