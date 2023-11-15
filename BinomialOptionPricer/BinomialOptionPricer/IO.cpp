
#include "IO.hpp"

#include<iostream>
#include <cmath>
#include <cstdlib>

using std::cout, std::cin;

inline void IO::read(const std::istream &is, Options::OptionType &currType){
    while(!(cin>>currType)){
        cout<<"ENTER A VALID OPTION TYPE"<<endl;
        cin.clear();
        cin.ignore(100,'\n');
    }
    
}

inline void IO::read(const std::istream &is, float &numVal){
    while(!(cin>>numVal) || numVal < 0){
        cout<<"ENTER A POSITIVE NUMERICAL VALUE"<<endl;
        cin.clear();
        cin.ignore(100,'\n');
    }
}

inline void IO::read(const std::istream &is, int &intVal){
    float temp;
    while(!(cin>>temp) || temp - floor(temp) || intVal <  0){
        cout<<"ENTER AN POSITIVE INTEGER VALUE"<<endl;
        cin.clear();
        cin.ignore(100,'\n');
    }
    intVal = (int)temp;
}

istream& operator>>(std::istream& is, Options &option){
    cout<<"option type \n(European Call: EC, European Put: EP, American Call: AC, American Put: AP)\n";
    IO::read(cin, option.currType);
    cout<<"strike price: ";
    IO::read(cin, option.strike);
    cout<<"underlying asset price: ";
    IO::read(cin, option.underlying);
    cout<<"volitility: ";
    IO::read(cin, option.vol);
    cout<<"Dividend Yield: ";
    IO::read(cin, option.dividend);
    cout<<"time period: ";
    IO::read(cin, option.timePeriod);
    cout<<"number of steps: ";
    IO::read(cin, option.steps);
    cout<<"risk free interest rate: ";
    IO::read(cin, option.rate);
    
    return is;
}

ostream& operator<<(std::ostream& os, const Options &option){
    cout<<"THIS IS AN OPTION";
    return os;
}

istream& operator>>(istream& is, Options::OptionType& optionType)
{
    string name;
    is >> name;

    if (name == "EC")
        optionType = Options::OptionType::europeanCall;
    else if (name == "EP")
        optionType = Options::OptionType::europeanPut;
    else if (name == "AC")
        optionType = Options::OptionType::americanCall;
    else if (name == "AP")
        optionType = Options::OptionType::americanPut;
    else{
        is.setstate(std::ios::failbit);
    }

    return is;
}
