#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

float europeanCall(float timePeriod, int steps, float rate, float vol, float strike, float underlying){
    float dt = timePeriod/steps;
    float upFactor = exp(vol * sqrt(dt));
    float downFactor = exp(-vol * sqrt(dt));
    cout<<downFactor<<" " <<upFactor<<endl;
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
    float timePeriod,steps,rate,vol,strike,underlying;
    //taking user input for information about call option
    cout<<"Enter the required option parameters\n"<<"-------------------------------------\n";
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
    
    float optionPrice = europeanCall(timePeriod,steps,rate,vol,strike,underlying);
    cout <<"-------------------------------------\n"<<"Option price: " << optionPrice << std::endl;
    return 0;
}
