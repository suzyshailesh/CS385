/*******************************************************************************
 * Name    : student.cpp
 * Author  : Susmitha Shailesh
 * Version : 1.0
 * Date    : January 31, 2020
 * Description : Learn classes and vectors
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Student{

public: 
	//constructor
	Student(string first, string last, float gpa, int id) : first_{first}, last_{last}, gpa_{gpa}, id_{id} {}

	//returns full name of student
	string full_name() const{
		string full = first_ + " " + last_;
		return full;
	}

	//id accessor
	int id() const{
		return id_;
	}

	//gpa accessor
	float gpa() const{
		return gpa_;
	}

	//prints all student info
	void print_info() const{
		cout << full_name() << ", GPA: " << fixed << setprecision(2) 
			<< gpa() << ", ID: " << id() << endl;
	}


private:
	//variables
	string first_;
	string last_;
	float gpa_;
	int id_;

};


//Takes a vector of Student objects, and returns a new vector with all Students whose GPA is < 1.0.
vector<Student> find_failing_students(const vector<Student> &students){
	vector<Student> failing_students;

	for(auto i = students.cbegin(); i != students.cend(); ++i)
		if(i->gpa() < 1.0)
			failing_students.push_back(*i);

	return failing_students;
}

//Takes a vector of Student objects and prints them to the screen
void print_students(const vector<Student> &students){
		for(auto i = students.cbegin(); i != students.cend(); ++i)
		i->print_info();
}

//main function
//prompts user for information and stores provided information in students vector
//prints all student information to screen and prints all failing students to screen
int main(){
	string first_name, last_name;
	float gpa;
	int id;
	char repeat;
	vector<Student> students;

	do{
		cout << "Enter student's first name: ";
		cin >> first_name;
		cout << "Enter student's last name: ";
		cin >> last_name;
		gpa = -1;
		while(gpa < 0 || gpa > 4){
			cout << "Enter student's GPA (0.0-4.0): ";
			cin >> gpa;
		}
		cout << "Enter student's ID: ";
		cin >> id;
		students.push_back(Student(first_name, last_name, gpa, id));
		cout << "Add another student to database (Y/N)? ";
		cin >> repeat;
	}while (repeat == 'Y' || repeat == 'y');

	cout << endl << "All students:" << endl;
	print_students(students);

	cout << endl << "Failing students:";
	vector<Student> failing_students = find_failing_students(students);
	if(failing_students.empty())
		cout << " None" << endl;
	else{
		cout << "\n";
		print_students(failing_students);
	}
	
	return 0;
}