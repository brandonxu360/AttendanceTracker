/*
* Name: Brandon Xu
* Project: AttendanceTracker
* File: stack.cpp
* Date: 4/3/23
* Description: Source file for a stack implementation using vector.
*			   This stack will be used to store the dates of absences.
*/

#include "stack.hpp"

// Stack operations
bool Stack::isEmpty() {

	if (_absenceVector.size() == 0) return true;
	else return false;

}

void Stack::push(std::string newDate) {

	_absenceVector.push_back(newDate); // Use vector method to push to back

}

bool Stack::pop() {

	if (isEmpty()) return false; // Check if the vector is empty (avoid undefined behavior)

	_absenceVector.pop_back(); // Use vector method to pop from back
	return true;

}

bool Stack::peek(std::string &top) {

	if (isEmpty()) return false; // Check if vector is empty (avoid undefined behavior)

	top = _absenceVector.back(); // Indirectly return back value through top reference
	return true;

}

// Overload the ostream operator
std::ostream& operator<<(std::ostream& os, Stack& stack) {

	if (stack.isEmpty()) {
		os << "";
		return os;
	}

	for (int i = stack._absenceVector.size() - 1; i >= 0; i--) {
		os << stack._absenceVector[i];
	}

	return os;

}


