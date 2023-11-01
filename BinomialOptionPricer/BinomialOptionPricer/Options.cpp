#include "Options.hpp"
#include <iostream>
#include <unordered_map>

using namespace std;

Options::Options(){
    cout<<"option type \n(European Call: EC, European Put: EP, American Call: AC, American Put: AP)\n";
    cin>>currType;
    cout<<"strike price: ";
    cin>> strike;
    cout<<"underlying asset price: ";
    cin>> underlying;
    cout<<"up multiplier: ";
    cin>> upFactor;
    cout<<"down multiplier: ";
    cin>> downFactor;
    cout<<"time period: ";
    cin>> timePeriod;
    cout<<"number of steps: ";
    cin>> steps;
    cout<<"risk free interest rate: ";
    cin>> rate;
    
    dt = timePeriod/steps;
    //upFactor = exp(vol * sqrt(dt));
    //downFactor = exp(-vol * sqrt(dt));
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

float Options::priceEuropeanCall(hashMap underlyingTree){
    hashMap optionTree;
    
    for(int i = 0; i <= steps; i++){
        optionTree[{steps, i}] = max(float(0), underlyingTree[{steps, i}] - strike);
    }
    
    for(int i = steps - 1; i >= 0; i--){
        for(int j = 0; j <= i; j++){
            float node = exp(-rate * dt) * (riskNeutralProb * optionTree[{i+1,j}] + (1 - riskNeutralProb) * optionTree[{i+1, j+1}]);
            optionTree[{i,j}] = node;
        }
    }
    return optionTree[{0,0}];
}

float Options::priceEuropeanPut(hashMap underlyingTree){
    hashMap optionTree;
    
    for(int i = 0; i <= steps; i++){
        optionTree[{steps, i}] = max(float(0), strike - underlyingTree[{steps, i}]);
    }
    
    for(int i = steps - 1; i >= 0; i--){
        for(int j = 0; j <= i; j++){
            float node = exp(-rate * dt) * (riskNeutralProb * optionTree[{i+1,j}] + (1 - riskNeutralProb) * optionTree[{i+1, j+1}]);
            optionTree[{i,j}] = node;
        }
    }
    return optionTree[{0,0}];
}

float Options::priceAmericanCall(hashMap underlyingTree){
    hashMap optionTree;
    
    for(int i = 0; i <= steps; i++){
        optionTree[{steps, i}] = max(float(0), underlyingTree[{steps, i}] - strike);
    }
    
    for(int i = steps - 1; i >= 0; i--){
        for(int j = 0; j <= i; j++){
            float node = exp(-rate * dt) * (riskNeutralProb * optionTree[{i+1,j}] + (1 - riskNeutralProb) * optionTree[{i+1, j+1}]);
            optionTree[{i,j}] = max(node,max(float(0), underlyingTree[{i, j}] - strike));
        }
    }
    return optionTree[{0,0}];
}

float Options::priceAmericanPut(hashMap underlyingTree){
    hashMap optionTree;
    
    for(int i = 0; i <= steps; i++){
        optionTree[{steps, i}] = max(float(0), strike - underlyingTree[{steps, i}]);
    }
    
    for(int i = steps - 1; i >= 0; i--){
        for(int j = 0; j <= i; j++){
            float node = exp(-rate * dt) * (riskNeutralProb * optionTree[{i+1,j}] + (1 - riskNeutralProb) * optionTree[{i+1, j+1}]);
            optionTree[{i,j}] = max(node,max(float(0), strike - underlyingTree[{i, j}]));
        }
    }
    return optionTree[{0,0}];
}

float Options::price(){
    hashMap underlyingTree = underlyingPrices();
    switch (currType) {
        case europeanCall:
            return priceEuropeanCall(underlyingTree);
            break;
        case europeanPut:
            return priceEuropeanPut(underlyingTree);
            break;
        case americanCall:
            return priceAmericanCall(underlyingTree);
            break;
        case americanPut:
            return priceAmericanPut(underlyingTree);
            break;
            
        default:
            cout<<"SOMETHING WENT WRONG!!!";
    }
    return 0;
}
