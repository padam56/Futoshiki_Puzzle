# Monte Carlo Optimizer
This project provides a C++ implementation of a Monte Carlo-based optimization algorithm designed to locate global minima of various mathematical functions.

# Building the Project

Compile all source files using:

c++ -o mcoptimizer *.cc


# Running the Optimizer

The project includes a bash script varyingVariables.sh, which allows you to run multiple optimization scenarios with different parameters. To execute the script:

Make the script executable:

chmod +x varyingVariables.sh


# Run the script:


./varyingVariables.sh


# Function Selection

The optimizer supports multiple test functions. You can switch between these functions by editing main.cc (lines 38-39):

// Uncomment one of the following lines to select a function:

// easyFunction* pOptimizationFunction = new easyFunction(xGuess, yGuess);
boothFunction* pOptimizationFunction = new boothFunction(xGuess, yGuess);

# Available Functions


easyFunction: A simple function for basic optimization tests.
boothFunction: The Booth function, commonly used as a benchmark for optimization algorithms.
goldsteinPriceFunction: Another popular benchmark function for testing optimization methods.

Project Structure:
main.cc: The main entry point for the program, where you can select which function to optimize.
*.cc: Source files containing the implementation of various components.
varyingVariables.sh: A bash script that runs multiple test scenarios with different parameter settings.

The output includes visualizations of energy values across X-Y coordinates, helping to track the optimization process.

# Note

This optimizer uses Monte Carlo techniques to explore the solution space. The delta parameter controls the step size during this exploration and can be adjusted for different levels of precision and exploration.


# Directory Structure:


DocumentSubmission: Contains a PDF document summarizing the questions from Homework 2 and their solutions.
Question1: Includes results and plots for varying parameters in question 1 (easyFunction).
Question2_BoothFunction: Similar to Question 1 but applied to the Booth Function.
