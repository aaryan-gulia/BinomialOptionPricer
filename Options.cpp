#include "Options.hpp"
#include <iostream>
#include <unordered_map>

using namespace std;

Options::Options(){
    cout<<"strike price: ";
    cin>> strike;
    cout<<"underlying asset price: ";
    cin>> underlying;
    cout<<"volatility: ";
    cin>> vol;
    cout<<"time period: ";
    cin>> timePeriod;
    cout<<"number of steps: ";
    cin>> steps;
    cout<<"risk free interest rate: ";
    cin>> rate;
    
    dt = timePeriod/steps;
    upFactor = exp(vol * sqrt(dt));
    downFactor = exp(-vol * sqrt(dt));
    riskNeutralProb = (std::exp(rate * dt) - downFactor)/(upFactor - downFactor);
}

Options::hashMap Options::underlyingPrices(){
    hashMap underlyingTree;
    for(int i = 0; i <= steps; i++){
        for(int j = 0; j <= i; j++){
            float node = underlying * pow(upFactor ,i - j) * pow(downFactor, j);
            vector<int>temp { i,j };
            underlyingTree[temp] = node;
        }
    }
    return underlyingTree;
}

Options::hashMap Options::callOptionPrices(hashMap underlyingTree){
    hashMap optionTree;
    
    for(int i = 0; i <= steps; i++){
        optionTree[{steps, i}] = max(float(0), underlyingTree[{steps, i}] - strike);
    }
    
    for(int i = steps - 1; i >= 0; i--){
        for(int j = 0; j <= i; j++){
            float node = 1 / (1 + rate * dt) * (riskNeutralProb * optionTree[{i+1,j}] + (1 - riskNeutralProb) * optionTree[{i+1, j+1}]);
            optionTree[{i,j}] = node;
        }
    }
    return optionTree;
}

float Options::priceEuropeanCall(){
    hashMap europeanTree;
    hashMap underlyingTree = underlyingPrices();
    hashMap optionTree = callOptionPrices(underlyingTree);
    return optionTree[{0,0}];
}

float Options::price(){
    return priceEuropeanCall();
}
