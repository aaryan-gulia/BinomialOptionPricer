#include "Options.hpp"
#include "Algorithms.hpp"

std::vector<double> Options::price(){
    return Algorithms::price(strike, underlying, rate, vol, timePeriod, yield, int(currType));
}
