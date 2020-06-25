/*******************************************************************************
 * Name        : sqrt.cpp
 * Author      : Susmitha Shailesh
 * Version     : 1.0
 * Date        : 1/29/2020
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

using namespace std;
#include <iostream>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <istream>
#include <sstream>

double sqrt(double num, double epsilon){
	//Return numeric_limits<double>::quiet_NaN(), if the num < 0.  This constant is found in the limits header.
	if(num < 0){
    	return numeric_limits<double>::quiet_NaN();
    }
	
	//Return num, if num is 0 or 1.
    if(num == 0 or num == 1){
    	return num;
    }

	//Repeat next_guess = (last_guess + num/last_guess) / 2 until abs(last_guess - next_guess) <= epsilon.
    double last_guess = num;
    double next_guess = (last_guess + (num/last_guess)) / 2;

    while(abs(last_guess - next_guess) > epsilon){
    	last_guess = next_guess;
    	next_guess = (last_guess + (num/last_guess)) / 2;
    }
    
	//Ultimately, return the last value of next_guess.

	return next_guess;

}

int main(int argc, char *argv[]) {
	//wrong inputs
	if (argc != 2 && argc != 3) {
        cerr << "Usage: ./sqrt <value> [epsilon]" << endl;
        return 1;
    }

    double check;
    istringstream iss;

    //check if value is a double
    iss.str(argv[1]);
    if (!(iss >> check)) {
        cerr << "Error: Value argument must be a double." << endl;
        return 1;
    }

    iss.clear();
    double epsilon = 1e-7;
    double check2;

    //epsilon value is not a double or is not positive
    if(argc == 3){
    	iss.str(argv[2]);
	    if (!(iss >> check2 and check2>0)) {
	        cerr << "Error: Epsilon argument must be a positive double." << endl;
	        return 1;
	    }
	    

    	epsilon = check2;
    }

    //set precision
    std::cout << std::fixed << std::showpoint;
    std::cout << std::setprecision(8);
    std::cout << sqrt(check, epsilon) << '\n';

    return 0;

    

}
