
#ifndef IO_hpp
#define IO_hpp

#include "Options.hpp"
#include <iostream>

#include <stdio.h>

class IO{
public:
    
    static inline void read(const std::istream &is, Options::OptionType &currType);
    static inline void read(const std::istream &is, float &numVal);
    static inline void read(const std::istream &is, int &intVal);
};

#endif /* IO_hpp */
