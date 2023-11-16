//
//  Options.hpp
//
//
//  Created by Aaryan Gulia on 31/10/2023.
//

#ifndef Options_hpp
#define Options_hpp
#include<iostream>

class Options{
private:
    friend std::istream& operator>>(std::istream& is, Options &option);
    friend std::ostream& operator<<(std::ostream& os, const Options &option);

    double rate, vol, yield, strike, underlying, timePeriod;
    
public:
    enum ExpirationType{
        european = 1,
        american = 2
    }currType;
    friend std::istream& operator>>(std::istream& is, ExpirationType& currType);
    std::vector<double> price();
    
};

#endif /* Options_hpp */
