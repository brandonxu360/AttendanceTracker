/*
* Name: Brandon Xu
* Project: AttendanceTracker
* File: stack.hpp
* Date: 4/3/23
* Description: Header file for a stack implementation using vector. 
*			   This stack will be used to store the dates of absences.
*/

#include "header.hpp"

class Stack {

public:

	// Stack operations
	bool isEmpty();
	void push(std::string newDate); 
	bool pop(); 
	bool peek(std::string &top); // Indiretly return back value to top reference

	friend std::ostream& operator<<(std::ostream& os, Stack& stack); // Overload the ostream operator

private:

	std::vector<std::string> _absenceVector; // Vector containing absence dates

};

