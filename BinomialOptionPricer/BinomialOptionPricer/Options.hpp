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
    typedef unordered_map<vector<int>,float,VectorHasher> hashMap;
    
    int steps;
    float rate, vol, strike, underlying, timePeriod;
    float dt, upFactor, downFactor, riskNeutralProb;
    enum OptionType{
        europeanCall = 0,
        europeanPut = 1,
        americanCall = 3,
        americanPut = 4
    }currType;
    
    friend istream& operator>>(std::istream& is, OptionType& optionType)
    {
        string name;
        is >> name;

        if (name == "EC")
            optionType = europeanCall;
        else if (name == "EP")
            optionType = europeanPut;
        else if (name == "AC")
            optionType = americanCall;
        else if (name == "AP")
            optionType = americanPut;

        return is;
    }
    
    hashMap underlyingPrices();
    
    float priceEuropeanCall(hashMap underlyingTree);
    float priceEuropeanPut(hashMap underlyingTree);
    float priceAmericanCall(hashMap underlyingTree);
    float priceAmericanPut(hashMap underlyingTree);
    
public:
    float price();
    Options();
    
};

#include <stdio.h>

#endif /* Options_hpp */
