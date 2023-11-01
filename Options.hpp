//
//  Options.hpp
//  
//
//  Created by Aaryan Gulia on 31/10/2023.
//
#include <cmath>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

#ifndef Options_hpp
#define Options_hpp

struct VectorHasher {
    int operator()(const vector<int> &V) const {
        int hash = V.size();
        for(auto &i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

class Options{

private:
    typedef unordered_map<vector<int>,float,VectorHasher> hashMap;
    
    int steps;
    float rate, vol, strike, underlying, timePeriod;
    float dt, upFactor, downFactor, riskNeutralProb;
    enum Style{
        europeanCall = 0,
        europeanPut = 1,
        AmericanCall = 3,
        AmericanPut = 4
    }currStyle;
    
    hashMap underlyingPrices();
    hashMap callOptionPrices(hashMap underlyingTree);
    
    float priceEuropeanCall();
    float priceEuropeanPut();
    float priceAmericanCall();
    float priceAmericanPut();
    
public:
    float price();
    Options();
    
};

#include <stdio.h>

#endif /* Options_hpp */
