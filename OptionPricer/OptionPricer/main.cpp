#include <iostream>
#include <string>

#include "Algorithms.hpp"
#include "Options.hpp"

using namespace std;

int main() {
    
    string launchPricer;
    cout<<"Do you want to price an option?(yes/no)\n";
    cin >> launchPricer;
    cout<<"-----------------------\n";
    
    while(launchPricer == "yes"){
        Options option;
        cin>>option;
        cout<<"select a pricing model\n"<<"1. Binomial Model\n"<<"2. Black-Scholes Model\n"<<"3. MonteCarlo Model\n"<<"enter a valid model number: ";
        cin>>Algorithms::model;
        vector<double> optionPrice = option.price();
        cout<<"-----------------------\n"<<"Call Option Price: " << optionPrice[0]
            <<"\nPut Option Price: " << optionPrice[1]
            <<"\n-----------------------\n"<<std::endl;
        cout<<"Do you want to price another option?\n";
        cin >> launchPricer;
        cout<<"-----------------------\n";
    }
    
    return 0;
}
