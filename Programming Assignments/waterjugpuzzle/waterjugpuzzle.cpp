/*******************************************************************************
 * Name    : waterjug.cpp
 * Author  : Susmitha Shailesh and Aparajita Rana
 * Version : 1.0
 * Date    : October 15, 2019
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int cap_a, cap_b, cap_c;
vector<vector<bool>> visits;

struct State{
    //state class- given
    int a, b, c;
    vector<string> directions;

    State(int _a, int _b, int _c): a(_a), b(_b), c(_c) {}

    string to_string(){
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};


State pour(State temp, int pour_from, int pour_to)
{
    // create general containers of letters, temps, maxs
    vector<char> letters{'A', 'B', 'C'};
    vector<int> temps{temp.a, temp.b, temp.c};
    vector<int> maxs{cap_a, cap_b, cap_c};

    int amount;
    amount=maxs[pour_to]-temps[pour_to];

    int newstate_a;
    int newstate_b;
    int newstate_c;

    newstate_a = temp.a;
    newstate_b = temp.b;
    newstate_c = temp.c;
    int pour_amount;
    pour_amount = 0;
    
    //check if there is space left in the pour_to jug
    if(temps[pour_to] != maxs[pour_to]) 
    {
        // A=0, B=1, C=2, below is C to A
        if(pour_from == 2 && pour_to == 0)
        {
            if(amount<temps[pour_from])
            {
                //if the amount of space in the pour_to jug is more than the amount in the pour_from jug
                newstate_a = temp.a+amount;
                newstate_c = temp.c-amount;
                pour_amount = amount;
            }
            else
            {
                newstate_a = temp.a+temp.c;
                newstate_c=0;
                pour_amount = temp.c;
            }
        }
        
        // A=0, B=1, C=2, below is B to A
        if(pour_from == 1 && pour_to == 0)
        {
            if(amount<temps[pour_from])
            {
                //if the amount of space in the pour_to jug is more than the amount in the pour_from jug
                newstate_a = temp.a+amount;
                newstate_b = temp.b-amount;
                pour_amount = amount;
            }
            else
            {
                newstate_a = temp.a+temp.b;
                newstate_b=0;
                pour_amount = temp.b;
            }
        }
        
        // A=0, B=1, C=2, below is C to B
        if(pour_from == 2 && pour_to == 1)
        {
            if(amount<temps[pour_from])
            {
                //if the amount of space in the pour_to jug is more than the amount in the pour_from jug
                newstate_b = temp.b+amount;
                newstate_c = temp.c-amount;
                pour_amount = amount;
            }
            else
            {
                newstate_b = temp.b+temp.c;
                newstate_c=0;
                pour_amount = temp.c;
            }
        }
        
        // A=0, B=1, C=2, below is A to B
        if(pour_from == 0 && pour_to == 1)
        {
            if(amount<temps[pour_from])
            {
                //if the amount of space in the pour_to jug is more than the amount in the pour_from jug
                newstate_b = temp.b+amount;
                newstate_a = temp.a-amount;
                pour_amount = amount;
            }
            else
            {
                newstate_b = temp.b+temp.a;
                newstate_a=0;
                pour_amount = temp.a;
            }
        }
        
        // A=0, B=1, C=2, below is B to C
        if(pour_from == 1 && pour_to == 2)
        {
            if(amount<temps[pour_from])
            {
                //if the amount of space in the pour_to jug is more than the amount in the pour_from jug
                newstate_c = temp.c+amount;
                newstate_b = temp.b-amount;
                pour_amount = amount;
            }
            else
            {
                newstate_c = temp.c+temp.b;
                newstate_b=0;
                pour_amount = temp.b;
            }
        }
        
        // A=0, B=1, C=2, below is A to C
        if(pour_from == 0 && pour_to == 2)
        {
            if(amount<temps[pour_from])
            {
                //if the amount of space in the pour_to jug is more than the amount in the pour_from jug
                newstate_c = temp.c+amount;
                newstate_a = temp.a-amount;
                pour_amount = amount;
            }
            else
            {
                newstate_c = temp.c+temp.a;
                newstate_a=0;
                pour_amount = temp.a;
            }
        }
        
    }
    State newjug(newstate_a, newstate_b, newstate_c);
    
    ostringstream s;
    // determines various gallon quantities based upon the value recieved
    if(pour_amount == 1){
        s << "Pour " << pour_amount << " gallon from " << letters[pour_from] << " to " << letters[pour_to] << ". " << newjug.to_string();
    }
    else{
        s << "Pour " << pour_amount << " gallons from " << letters[pour_from] << " to " << letters[pour_to] << ". " << newjug.to_string();
    }   
    //cout<<s.str();
    newjug.directions = temp.directions;
    newjug.directions.push_back(s.str());
    
    
    //cout<<newjug.to_string()<<endl;
    return newjug;
}

//prints the result of the pour and prints out hte initial state and values 
void print_result(State initial, State final_state){
    vector<string> direct;
    direct=final_state.directions;
    cout << "Initial state. " << initial.to_string() << endl;
    //cout<< direct.size() << endl;
    for(size_t i=0; i<direct.size(); i++){
        cout << direct.at(i) << endl;
    }
    
}

// BFS utilizing the intitial value, max value, goal value and finds the BFS for best path
int BFS(State initial, State max, State goal)
{
    queue<State> tracker;
    tracker.push(initial);
    while(!(tracker.empty()))
    {
        State temp=tracker.front();
        tracker.pop();
        
        if((temp.a==goal.a) && (temp.b==goal.b)){
            print_result(initial, temp);
            return 1;
        }
        
        //gets different pour values
        if(!visits[temp.a][temp.b]){
            visits[temp.a][temp.b] = true;
            tracker.push(pour(temp, 2, 0));
            tracker.push(pour(temp, 1, 0));
            tracker.push(pour(temp, 2, 1));
            tracker.push(pour(temp, 0, 1));
            tracker.push(pour(temp, 1, 2));
            tracker.push(pour(temp, 0, 2));
        }
    }
    
    return -1;
}

//error check for exceeded capacity
bool check_caps_goals(int cap, int goal, int arg_num){
    vector<char> letters{'A', 'B', 'C'};

    if(goal > cap){
        cerr<<"Error: Goal cannot exceed capacity of jug " << letters[arg_num] << "." <<endl;
        return false;
    }
    return true;

}

//prints the valid waterjug solutions or potential errors
int main(int argc, char * const argv[]) {
    vector<char> letters{'A', 'B', 'C'};

    if(argc != 7){ 
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }

// checks for invalid capacity and invalid goal errors 
    for (int i = 1; i <= 6; ++i) {
        int temp;
        //bool check=false;

        istringstream stream(argv[i]);
        if (!(stream >> temp) || (temp < 0) || (temp == 0 && i == 3)) {
            if (i <= 3) {
                cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << letters[i-1] <<"." << endl;
                return 1;
            }
            if (i >= 4) {
                cerr << "Error: Invalid goal '" << argv[i] << "' for jug " << letters[i-4] <<"." << endl;
                return 1;
            }
        }
    }
// determines the check caps goals and whether true or false
    bool valid_arg = true;
    for(int i = 1; i < 4; i++){
        valid_arg = check_caps_goals(atoi(argv[i]), atoi(argv[i+3]), i-1);
        if(valid_arg == false){
            return 1;
        }
    }
// returns error in the case that the goal state is not equal to the capacity of jug C
    if(atoi(argv[4]) + atoi(argv[5]) + atoi(argv[6]) != atoi(argv[3])){
        cerr<<"Error: Total gallons in goal state must be equal to the capacity of jug C."<<endl;
        return 1;
    }
    
//conversion
    cap_a = atoi(argv[1]);
    cap_b = atoi(argv[2]);
    cap_c = atoi(argv[3]);

//adds to queue
    vector<vector<bool>> initialize;
    visits = initialize;
    for (int i = 0; i<=cap_a; i++){
        visits.push_back(vector<bool>(cap_b+1));

    }
    //cout<<visits.size()<<endl;
    State initial(0, 0, atoi(argv[3]));
    State max(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    State goal(atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
    int result = BFS(initial, max, goal);
    //cout<<result<<endl;
    if(result == 1){
        return 1;
    }
    else{
        cout<<"No solution."<<endl;
        return 1;
    }

}