/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Susmitha Shailesh
 * Date        : September 11, 2019
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // Display the primes in the specified format
    const int max_prime_width = num_digits(max_prime_),
         primes_per_row = (80 / (max_prime_width + 1));

    //display for only one row of primes
    if(count_num_primes()<=primes_per_row){
        for(int i=2; i<=limit_; i++){
            if(is_prime_[i] == true){
                if(i==2){
                    cout<<i;
                }
                else{
                    cout<<" "<<i;
                }
            } 
        }
        cout<<endl;  
    }
    //display for multiple rows of primes
    else{
        int count = 0;
        for(int i=2; i<=limit_; i++){
            if(is_prime_[i] == true){
                if(count==0){
                    cout<<setw(max_prime_width)<<i;
                }
                else{
                    cout<<setw(max_prime_width+1)<<i;
                }
                count++;
            }
            if(count==primes_per_row){
                cout<<endl;
                count = 0;
            }
        }
    } 
}

int PrimesSieve::count_num_primes() const {
    // Counts the number of primes found
    int num = 0;
    for(int i=0; i<=limit_; i++){
        if(is_prime_[i]==true){
            num++;
        }
    }
    return num;
}

void PrimesSieve::sieve() {
    //Set all prime number values in is_prime_ equal to true
    //Set all non-prime values equal to false
    //Set max_prime_ and num_primes_

    //set all values in is_prime_ to true initially
    for(int i=2; i<=limit_; i++){
        is_prime_[i] = true;
    }

    //for each value in is_prime_ that is still true,
    //set all multiples of that value to false
    for(int i=2; i<=sqrt(limit_); i++){
        if(is_prime_[i] == true){
            for(int j=(i*i); j<=limit_; j=j+i){
                is_prime_[j] = false;
            }
        }
    }

    //set max_prime_ equal to the largest prime number
    for(int i=limit_; i>=0; i--){
        if(is_prime_[i] == true){
            max_prime_ = i;
            break;
        }
    }

    num_primes_=count_num_primes();
}

int PrimesSieve::num_digits(int num) {
    // Determines how many digits are in an integer
    int dig = 0;
    while(num>0){
        num/=10;
        dig++;
    }
    return dig;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    PrimesSieve sieve(limit);

    //runs program
    cout<<endl;
    cout<<"Number of primes found: "<<sieve.num_primes()<<endl;
    cout<<"Primes up to "<<limit<<":"<<endl; 
    sieve.display_primes();

    return 0;
}
