/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Susmitha Shailesh
 * Version     : 1.0
 * Date        : 10/25/19
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    long count = 0;
    for(int i = 0; i < length; i++){
        for(int j = i + 1; j < length; j++){
            if(array[i] > array[j]){
                count++;
            }
        }
    }
    return count;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!

    //calls merge to complete task
    int *scratch = new int[length];
    long ans = mergesort(array, scratch, 0, length-1);
    delete[] scratch;
    return ans;
}

long merge(int array[], int scratch[], int low, int mid, int high) {
    
    int x;
    int y;
    int z;
    long count = 0;

    x = low;
    y = mid;
    z = low;


    while ((x <= mid - 1) && (y <= high)) {
        if (array[x] <= array[y]) {
            scratch[z] = array[x];
            z++;
            x++;
        }
        else {
            scratch[z] = array[y];
            count += (mid - x);
            z++;
            y++;
        }
    }
    

    //shifts rest of array
    while (y <= high){
        scratch[z] = array[y];
        z++;
        y++;
    }

    while (x <= mid - 1){
        scratch[z] = array[x];
        z++;
        x++;
    }

    for (int i = low; i < high +1; i++){
        array[i] = scratch[i];
    }
    return count;
}

/*Sorts an array and returns the number of inversions in the array.
 */
static long mergesort(int array[], int scratch[], int low, int high) {
    int mid;
    long count = 0;
    if (high > low) {
        mid = (high + low) / 2;
        //recursion
        count = count + mergesort(array, scratch, low, mid);
        count = count + mergesort(array, scratch, mid + 1, high);
        //calls merge to merge two array segments
        count = count + merge(array, scratch, low, mid + 1, high);
    }
    return count;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument

    if(!(argc == 1 || argc == 2)){
        cout  << "Usage: ./inversioncounter [slow]" << endl;
        return 1;
    }

    if(argc == 2){
        string x = argv[1];
        if(x.compare("slow") != 0) {
            cout << "Error: Unrecognized option '" << x <<"'." << endl;
            return 0;
        }
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // TODO: produce output
    if (values.empty()) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }
    
    if (argc == 1) {
        cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size()) << endl;
        return 0;
    }
    else {
        cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size()) << endl;
        return 0;
    }

    return 0;
}
