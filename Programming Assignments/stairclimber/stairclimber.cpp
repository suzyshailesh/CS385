/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Susmitha Shailesh
 * Date        : 9/29/19
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // Returns a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
	vector<vector<int>> ways;

	if(num_stairs<=0){
		//base case: if the number of stairs has been satisfied or exceeded
		ways.push_back(vector<int>());
	}
	else{
		for(int i = 1; i < 4; i++){
			if(num_stairs >= i){
				//recursive call
				vector<vector<int>> result = get_ways(num_stairs-i);
				for(unsigned int j = 0; j < result.size(); j++){
					result[j].push_back(i);
					ways.push_back(result[j]);
				}
				
			}
		}
	}
	return ways;
}

void display_ways(const vector< vector<int> > &ways) {
    // Displays the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
 	
	for(unsigned int i = 0; i < ways.size(); i++){ 

		//ensure spacing and formatting are correct
		int x = ways.size();
		int digits = 1;
		while(x>=10){
			digits++;
			x=x/10;
		}
        
        if(ways.size()>9){
        	cout<<setw(digits);
        }

        //print ways with proper formatting
		cout<<i+1<<". [";
        
		for(unsigned int j = ways[i].size() - 1; j > 0; j--)
        {
			cout<<ways[i][j]<<", ";
		}
        
		cout<<ways[i][0]<<"]"<<endl;
	}
}


int main(int argc, char * const argv[]) {
	int x;
	istringstream check;

	if(argc != 2){
		//error if there is not the correct number of arguments
		cerr<<"Usage: ./stairclimber <number of stairs>"<<endl;
		return 1;
	}

	if(argc <= 0){
		//error if the arguments is negative or equal to 0
		cerr<<"Error: Number of stairs must be a positive integer."<<endl;
		return 1;
	}

	check.str(argv[1]);
	if(!(check >> x) || x < 1){
		//error if the arguments isn't a number
		cerr<<"Error: Number of stairs must be a positive integer."<<endl;
        return 1;
	}
	check.clear();

	//print ways to climb stairs
    vector<vector<int>> result = get_ways(x);
    if(x == 1){
        cout<<"1 way to climb 1 stair."<<endl;
        display_ways(result);
    }
    else
    {
        cout<<result.size()<<" ways to climb "<<x<<" stairs."<<endl;
        display_ways(result);
    }
    
    return 0;
}


