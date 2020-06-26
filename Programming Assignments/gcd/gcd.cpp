/*******************************************************************************
 * Name    : gcd.cpp
 * Author  : Susmitha Shailesh
 * Version : 1.0
 * Date    : August 30, 2019
 * Description : Computes the GCD of two command-line arguments.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

int gcd_iterative(int m, int n) {
    //return the gcd
    int a;
    while(n != 0){
        a = m;
        m = n;
        n = a%n;
    }
    return m;
}

int gcd_recursive(int m, int n) {
    //return the gcd
    if (n == 0){
        return m;
    }
    else return gcd_recursive(n, m%n);

}

int main(int argc, char* const argv[]) {
    int m, n;
    istringstream iss;

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <integer m> <integer n>"
             << endl;
        return 1;
    }
    iss.str(argv[1]);
    if ( !(iss >> m) ) {
        cerr << "Error: The first argument is not a valid integer."
             << endl;
        return 1;
    }
    iss.clear(); // clear the error code
    iss.str(argv[2]);
    if ( !(iss >> n) ) {
        cerr << "Error: The second argument is not a valid integer."
             << endl;
        return 1;
    }


    cout << "Iterative: gcd(" << m << ", " << n << ") = " << gcd_iterative(abs(m),abs(n)) << endl;
    cout << "Recursive: gcd(" << m << ", " << n << ") = " << gcd_recursive(abs(m),abs(n)) << endl;
    return 0;
}
