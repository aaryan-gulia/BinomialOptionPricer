#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

float europeanCall(float timePeriod, int steps, float rate, float upFactor, float downFactor, float strike, float underlying){
    float dt = timePeriod/steps;
    float riskNeutralProb = (std::exp(rate * dt) - downFactor)/(upFactor - downFactor);
    float high = std::max((underlying * upFactor - strike), float(0.0));
    float low = std::max((underlying * downFactor - strike), float(0.0));
    float optionPrice = 1 / (1 + rate * dt) * (riskNeutralProb * high + (1 - riskNeutralProb) * low);
    return optionPrice;
}

int main() {
    float timePeriod,steps,rate,upFactor,downFactor,strike,underlying;
    //taking user input for information about call option
    cout<<"Enter the strile price: ";
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
    cout << "option price: " << optionPrice << std::endl;
    return 0;
}
