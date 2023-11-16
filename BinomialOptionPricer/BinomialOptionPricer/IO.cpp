
#include "IO.hpp"
#include "Algorithms.hpp"
#include <iostream>
#include <cmath>
#include <cstdlib>

using std::cout, std::cin, std::endl, std::istream;

void IO::read(const std::istream &is, Options::ExpirationType &currType){
    while(!(cin>>currType)){
        cout<<"ENTER A VALID OPTION TYPE"<<endl;
        cin.clear();
        cin.ignore(100,'\n');
    }
    
}

void IO::read(const std::istream &is, Algorithms::ModelSelector &model){
    while(!(cin>>model)){
        cout<<"ENTER A VALID MODEL NUMBER"<<endl;
        cin.clear();
        cin.ignore(100,'\n');
    }
}

void IO::read(const std::istream &is, double &numVal){
    while(!(cin>>numVal) || numVal < 0){
        cout<<"ENTER A POSITIVE NUMERICAL VALUE"<<endl;
        cin.clear();
        cin.ignore(100,'\n');
    }
}

void IO::read(const std::istream &is, int &intVal){
    float temp;
    while(!(cin>>temp) || temp - floor(temp) || intVal <  0){
        cout<<"ENTER AN POSITIVE INTEGER VALUE"<<endl;
        cin.clear();
        cin.ignore(100,'\n');
    }
    intVal = (int)temp;
}

void IO::read(const std::istream &is, int &intVal, const int &min, const int &max){
    float temp;
    while(!(cin>>temp) || temp - floor(temp) || intVal <  min || intVal > max){
        cout<<"ENTER A VALID INTEGER"<<endl;
        cin.clear();
        cin.ignore(100,'\n');
    }
    intVal = (int)temp;
}

istream& operator>>(std::istream& is, Options &option){
    cout<<"option type (European(E), American(A)): ";
    IO::read(cin, option.currType);
    cout<<"strike price: ";
    IO::read(cin, option.strike);
    cout<<"underlying asset price: ";
    IO::read(cin, option.underlying);
    cout<<"volitility: ";
    IO::read(cin, option.vol);
    cout<<"annual yield: ";
    IO::read(cin, option.yield);
    cout<<"time to maturity: ";
    IO::read(cin, option.timePeriod);
    cout<<"risk free interest rate: ";
    IO::read(cin, option.rate);
    
    return is;
}

std::ostream& operator<<(std::ostream& os, const Options &option){
    cout<<"THIS IS AN OPTION";
    return os;
}

istream& operator>>(istream& is, Options::ExpirationType& currType)
{
    std::string name;
    is >> name;

    if (name == "E")
        currType = Options::ExpirationType::european;
    else if (name == "A")
        currType = Options::ExpirationType::american;
    else{
        is.setstate(std::ios::failbit);
    }

    return is;
}

std::istream& operator>>(std::istream& is, Algorithms::ModelSelector& currType){
    std::string name;
    is >> name;

    if (name == "1")
        currType = Algorithms::ModelSelector::binomial_model;
    else if (name == "2")
        currType = Algorithms::ModelSelector::blackscholes_model;
    else if (name == "3")
        currType = Algorithms::ModelSelector::montecarlo_model;
    else{
        is.setstate(std::ios::failbit);
    }

    return is;
}
