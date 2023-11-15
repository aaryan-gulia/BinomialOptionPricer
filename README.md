# Option Pricing Model

This C++ command-line tool implements a simple binomial model method to calculate the prices for American and European Call and Put options. You can download the repository and directly access the executable files on MacOS. For any other system, follow the below instructions to execute the source code and have your own version of the command-line app!

## Current Features
European/American put and call options for
-  Dividend and non-dividend stocks
-  foreign currencies (use dividend yield as currency's risk-free rate)
-  interest-yielding simple bonds

## Upcoming Features
- Support for more complicated assets and Asian options
- Additional features or pricing option strategies and obtaining payoff functions
- Support to calculate simple Greeks through the binomial approximation

# Getting Started
Requirement: C++ compiler (supporting C++11 or higher)

Step 1: Clone git repo
`git clone https://github.com/aaryan-gulia/BinomialOptionPricer.git`

Step 2: Navigate to the main project directory
`cd BinomialOptionPricer/BinomialOptionPricer`

Step 3: Compile code and run the tool
```
g++ -std=c++11 main.cpp Options.hpp Options.cpp -o options_pricing
./options_pricing.out
```
Note that these steps may vary depending on your operating system

# Contributions
Any and all contributions are welcome. I will continue to add further features to this basic tool, and I look forward to receiving input from the community!

# License
This project is licensed under the [MIT License](https://opensource.org/license/mit/)
