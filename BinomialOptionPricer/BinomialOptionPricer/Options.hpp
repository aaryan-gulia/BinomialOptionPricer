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
#include <string>

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
    enum OptionType{
        europeanCall = 1,
        europeanPut = 2,
        americanCall = 3,
        americanPut = 4
    }currType;
    
    friend istream& operator>>(std::istream& is, OptionType& optionType);
    friend istream& operator>>(std::istream& is, Options &option);
    friend ostream& operator<<(std::ostream& os, const Options &option);
    friend class IO;
    
    typedef unordered_map<vector<int>,float,VectorHasher> hashMap;
    
    int steps;
    float rate, vol, dividend, strike, underlying, timePeriod;
    float dt, upFactor, downFactor, riskNeutralProb;
    
    void calc();

    hashMap underlyingPrices();
    
    float priceEuropeanCall(hashMap underlyingTree);
    float priceEuropeanPut(hashMap underlyingTree);
    float priceAmericanCall(hashMap underlyingTree);
    float priceAmericanPut(hashMap underlyingTree);
    
public:
    float price();
    
};

#include <stdio.h>

#endif /* Options_hpp */
