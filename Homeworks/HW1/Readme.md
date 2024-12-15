Floating-Point Spacing Calculator:


This project implements a calculator to determine the spacing between consecutive floating-point numbers, utilizing custom classes APNumber and FloatSimulator. The program calculates and displays these spacings for specific exponents, providing insight into how floating-point precision changes as the exponent increases.

Project Files
- Main.cpp: The main driver of the program, responsible for calculating and displaying the spacing between floating-point numbers.
- APNumber.hpp / APNumber.cpp: These files define and implement an arbitrary precision number class, enabling high-precision arithmetic operations.
- FloatSimulator.hpp / FloatSimulator.cpp: These files define and implement a simulator for floating-point numbers, following the IEEE 754 single-precision standard.

Compilation Instructions:
To compile the project, use the following command in your terminal:

g++ Main.cpp APNumber.cpp FloatSimulator.cpp -o HW

Running the Program:

Once compiled, you can execute the program by running:

./HW

The program will calculate and display the spacing between consecutive floating-point numbers for exponents ranging from 10 to 15.

Output Details
For each exponent in the specified range, the program will output:
- The value of the exponent.
- The calculated spacing between two consecutive floating-point numbers.
- The spacing expressed in scientific notation for clarity.

Key Features
- APNumber Class: Supports arbitrary precision arithmetic, allowing for highly accurate calculations beyond standard floating-point precision.
- FloatSimulator Class: Simulates single-precision floating-point arithmetic as defined by the IEEE 754 standard.
- Main Program: For each exponent, a FloatSimulator object is created. The program increments this object and computes the corresponding spacing between consecutive values.


