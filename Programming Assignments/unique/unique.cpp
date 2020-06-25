/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Susmitha Shailesh
 * Date        : Sept 17, 2019
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise
	for(auto i = s.cbegin(); i != s.cend(); ++i){
		if(*i<'a' || *i>'z'){
			return false;
		}
	}
	return true;
}

bool all_unique_letters(const string &s) {
    // returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
   unsigned int stor = 0;
   for(auto i = s.cbegin(); i != s.cend(); ++i){
   		unsigned int chr = 1 << (*i-'a');
   		if((stor & chr) > 0){
   			//checks if letter has been seen already
   			return false;
   		}
   		else{
   			//updates stor to store new character
   			stor = (stor | chr);
   		}
   }
   return true;
}

int main(int argc, char * const argv[]) {
    // Reads and parses command line arguments.
    // Calls other functions to produce correct output.
	if(argc != 2){
		cout << "Usage: ./unique <string>" << endl;
		return 0;
	}

	if(!is_all_lowercase(argv[1])){
	//Prints error if input is not all lowercase
		cerr << "Error: String must contain only lowercase letters." << endl;
		return 0;
	}
	else{
		if(all_unique_letters(argv[1])){
		//Checks if unique are unique and prints corresponding message
			cout << "All letters are unique." <<endl;
			return 0;
		}
		else{
			cout << "Duplicate letters found." <<endl;
			return 0;
		}
	}
}
