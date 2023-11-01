#include <iostream>
#include <string>

#include "Options.hpp"

using namespace std;

int main() {
    
    string launchPricer;
    cout<<"Do you want to price an option?\n";
    cin >> launchPricer;
    cout<<"-----------------------\n";
    
    while(launchPricer == "yes"){
        Options option;
        float optionPrice = option.price();
        cout<<"-----------------------\n"<<"Option price: " << optionPrice <<"\n-----------------------\n"<<std::endl;
        cout<<"Do you want to price another option?\n";
        cin >> launchPricer;
        cout<<"-----------------------\n";
    }
    
    return 0;
}
