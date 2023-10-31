#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

float europeanCall(float timePeriod, int steps, float rate, float upFactor, float downFactor, float strike, float underlying){
    float dt = timePeriod/steps;
    float riskNeutralProb = (std::exp(rate * dt) - downFactor)/(upFactor - downFactor);
    vector<float> optionPayouts;
    
    for(int i = 0; i <= steps; i++){
        float underlyingFinal = underlying * pow(upFactor, steps - i) * pow(downFactor, i);
        optionPayouts.push_back(max(underlyingFinal - strike,float(0.0)));
    }
    
    while(optionPayouts.size() > 1){
        vector<float> tempPrice;
        for(int j = 0; j < optionPayouts.size()-1; j++){
            tempPrice.push_back(1 / (1 + rate * dt) * (riskNeutralProb * optionPayouts[j]+ (1 - riskNeutralProb) * optionPayouts[j+1]));
        }
        optionPayouts = tempPrice;
    }
    
    return optionPayouts[0];
}

int main() {
    float timePeriod,steps,rate,upFactor,downFactor,strike,underlying;
    //taking user input for information about call option
    cout<<"Enter the strike price: ";
    cin>> strike;
    cout<<"Enter the current price of the underlying asset: ";
    cin>> underlying;
    cout<<"Enter the increasing factor: ";
    cin>> upFactor;
    cout<<"Enter the decreasing factor: ";
    cin>> downFactor;
    cout<<"Enter the total time period: ";
    cin>> timePeriod;
    cout<<"Enter the number of time steps: ";
    cin>> steps;
    cout<<"Enter the Interest rate: ";
    cin>> rate;
    
    float optionPrice = europeanCall(timePeriod,steps,rate,upFactor,downFactor,strike,underlying);
    cout <<"------------------------------------------------------\n"<<"Option price: " << optionPrice << std::endl;
    return 0;
}
