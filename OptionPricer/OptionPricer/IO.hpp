
#ifndef IO_hpp
#define IO_hpp

#include "Options.hpp"
#include <iostream>
#include "Algorithms.hpp"

#include <stdio.h>

class IO{
public:
    
    static void read(const std::istream &is, Options::ExpirationType &currType);
    static void read(const std::istream &is, Algorithms::ModelSelector &model);
    static void read(const std::istream &is, double &numVal);
    static void read(const std::istream &is, int &intVal);
    static void read(const std::istream &is, int &intVal, const int &max, const int &min);
};

#endif /* IO_hpp */
