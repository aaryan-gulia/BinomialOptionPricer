# Option Pricing Tool

This C++ command-line tool implements various optimized models to calculate the prices for American and European Call and Put options. You can download the repository and directly access the executable files on MacOS. For any other system, follow the below instructions to execute the source code and have your own version of the command-line app!

## Current Features
- Binomial model for vanilla options on various underlying assets (stocks, bonds, etc)
- Closed-form Black-Scholes solution for European options
- Numerical solution of Black-Scholes model for American options

## Upcoming Features
- Support for more complicated assets and exotic options
- Additional features or pricing option strategies and obtaining payoff functions
- Support to calculate simple Greeks using the Black-Scholes formula and numerical methods

# Getting Started
Requirement: 
- C++ compiler (supporting C++11 or higher)
- Boost library properly set up with access to header files. https://www.boost.org

Step 1: Clone git repo
`git clone https://github.com/aaryan-gulia/BinomialOptionPricer.git`

Step 2: Navigate to the main project directory
`cd BinomialOptionPricer/BinomialOptionPricer`

Step 3: Compile code and run the tool
```
g++ -std=c++11 main.cpp Options.hpp Options.cpp IO.hpp IO.cpp Algorithms.hpp Algorithms.cpp -o options_pricing
./options_pricing.out
```
Note that these steps may vary depending on your operating system

# Contributions
Any and all contributions are welcome. I will continue to add further features to this basic tool, and I look forward to receiving input from the community!

# License
This project is licensed under the [MIT License](https://opensource.org/license/mit/)
