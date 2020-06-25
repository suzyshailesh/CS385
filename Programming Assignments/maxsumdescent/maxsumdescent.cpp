
/*******************************************************************************
 * Name        : maxsumdescent.cpp
 * Author      : Susmitha Shailesh
 * Version     : 1.0
 * Date        : 4/27/20
 * Description : Dynamic programming solution to max sum descent problem.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

const char DELIMITER = ' ';

int **values, // This is your 2D array of values, read from the file.
    **sums;   // This is your 2D array of partial sums, used in DP.

int num_rows; // num_rows tells you how many rows the 2D array has.
              // The first row has 1 column, the second row has 2 columns, and
              // so on...

/**
 * Displays the 2D array of values read from the file in the format of a table.
 */
void display_table() {
    //finds maximum number of digits
    int max_digits = 1;
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j <= i; j++){
            //2 digits for 2 digit positive numbers
            if(values[i][j] > 9 && values[i][j] < 100){
                max_digits = 2;
            }
            else if(values[i][j] < -9){
            //3 digits for 2 digit negative numbers
                max_digits = 3;
            }
            else if(values[i][j] < 0){
            //2 digits for 1 digit negative numbers
                max_digits = 2;
            }
        }
    }

    //prints each row of triangle
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < i; j++){
            cout << setw(max_digits) << values[i][j] << " ";
        }
        cout << setw(max_digits) << values[i][i] << endl;
    }
}

/**
 * Returns the maximum sum possible in the triangle of values.
 * By starting at the top of the triangle and moving to adjacent numbers on the
 * row below, this function uses dynamic programming to build up another table
 * of partial sums.
 */
int compute_max_sum() {
    // Populate the 2D array of partial sums. It should still work even if
    // num_rows is 0 (i.e. the file was blank).

    //handles case of empty triangle
    if(num_rows == 0){
        return 0;
    }

    //first value of sums is first value in values 
    sums[0][0] = values[0][0];

    int i = 1;
    while(i < num_rows){
    //creates table of partial sums
        for(int j = 0; j <= i; j++){
            sums[i][j] = values[i][j];
            if(j == 0) {
                //for leftmost value in a row, you can only move there from the right
                sums[i][j] = sums[i][j] + sums[i-1][j];
            }
            else if(j == i){
                //for rightmost value in a row, you can only move there from the left
                sums[i][j] = sums[i][j] + sums[i-1][j-1];
            }
            else{
                //for all inner values in a row, you move from left or right depending on which one creates the larger sum
                sums[i][j] = sums[i][j] + std::max(sums[i-1][j-1], sums[i-1][j]);
            }
        }
        //increment row
        i++;
    }

    // Loop over the last row to find the max sum.
    int max_sum = 0;
    for(int j = 0; j < num_rows; j++){
        if(sums[num_rows - 1][j] > max_sum){
            max_sum = sums[num_rows - 1][j];
        }
    }

    // Return the max sum.
    return max_sum;
}

/**
 * Returns a vector of ints with the values from the top to the bottom of the
 * triangle that comprise the maximum sum.
 */
vector<int> backtrack_solution() {
    vector<int> solution;

    //handles case of empty triangle
    if(num_rows == 0){
        solution = {};
        return solution;
    }

    //finds index of max sum in bottom row of sums
    int index = -1;
    int max_sum = 0;
    for(int j = 0; j < num_rows; j++){
        if(sums[num_rows - 1][j] > max_sum){
            max_sum = sums[num_rows - 1][j];
            index = j;
        }
    }

    int i = num_rows - 1;
    while(i > 0){
    //starting at index of max sum, inserts value at index of values into solutions vector
    //then moves index to the left or right depending on which sum is greater
        solution.insert(solution.begin(), values[i][index]);
        if(index == 0) {
                index = 0;
        }
        else if(index == i){
            index = index - 1;
        }
        else{
            if(sums[i-1][index-1] > sums[i-1][index]){
                index = index - 1;
            }
            else{
                index = index;
            }
        }
        //decrement row
        i--;
    }

    //inserts first value
    solution.insert(solution.begin(), values[0][0]);

    return solution;
}

/**
 * Reads the contents of the file into the global 2D array 'values'. If
 * successful, the function also allocates memory for the 2D array 'sums'.
 */
bool load_values_from_file(const string &filename) {
    ifstream input_file(filename.c_str());
    if (!input_file) {
        cerr << "Error: Cannot open file '" << filename << "'." << endl;
        return false;
    }
    input_file.exceptions(ifstream::badbit);
    string line;
    vector<string> data;
    try {
        while (getline(input_file, line)) {
            data.push_back(line);
        }
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << filename << "'.";
        return false;
    }
    
    //find number of rows in triangle
    num_rows = data.size();

    //allocate space for arrays
    values = (int**)malloc(num_rows*num_rows*(sizeof(int)));
    sums = (int**)malloc(num_rows*num_rows*(sizeof(int)));
    

    vector<int> temp;

    //set each line of input to an index in values
    //make space in sums for later use
    for(size_t i = 0; i < size_t(num_rows); i++){
        stringstream iss(data[i]);
        int num;
        while(iss >> num){
            //create each line
            temp.push_back(num);
        }
        while(temp.size() != i+1){
            //add 100's for empty values
            temp.push_back(100);
        }
        values[i] = new int[temp.size()];
        //add line to values
        for(size_t j = 0; j < temp.size(); j++){
            values[i][j] = temp[j];
        }
        sums[i] = new int[temp.size()];
        temp.clear();
    }

    return true;
}

/**
 * Frees up the memory allocated for the 2D array of values and the 2D array of
 * partial sums.
 */
void cleanup() {
    for( int i = 0 ; i < num_rows; i++ )
    {
        //delete each array within matrices
        delete[] values[i];
        delete[] sums[i]; 
    }
    // delete actual matrices
    free(values);
    free(sums);
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    string filename(argv[1]);
    if (!load_values_from_file(filename)) {
        return 1;
    }

    //calls functions to find max sum and find path to max sum
    int max_sum = compute_max_sum();
    vector<int> solution = backtrack_solution();

    //full display- prints table, max sum, and solution array
    display_table();
    cout << "Max sum: " << max_sum << endl;
    if(num_rows > 0){
        cout << "Values: [";
        for(size_t i = 0; i < solution.size()-1; i++){
            cout << solution[i] << ", ";
        }
        cout << solution[solution.size()-1] << "]" << endl;
    }
    else{
        cout << "Values: []";
    }
    
    //frees up memory
    cleanup();


    return 0;
}
