/*
* Name: Brandon Xu
* Project: AttendanceTracker
* File: data.hpp
* Date: 4/3/23
* Description: Header file for the Data class, which will hold the student data (basic info, # of absences,
*			   and a stack containing dates of absences)
*/

#include "header.hpp"
#include "stack.hpp"

class Data {

public:

	// Setter functions
	void setRecordNum(int recordNum);
	void setID(int ID);
	void setName(std::string name);
	void setEmail(std::string email);
	void setUnits(std::string units);
	void setProgram(std::string program);
	void setLevel(std::string level);
	void incrementNumAbsences(); // Increment _numAbsences by 1
	void decrementNumAbsences(); // Decrement _numAbsences by 1

	// Getter functions
	int getRecordNum() const;
	int getID() const;
	std::string getName() const;
	std::string getEmail() const;
	std::string getUnits() const;
	std::string getProgram() const;
	std::string getLevel() const;
	int getNumAbsences() const;
	Stack& getAbsenceStack();

private:

	// General information fields
	int _recordNum; // Max 3 digits
	int _ID; // Max 9 digits
	std::string _name; // Last, first
	std::string _email; // Email
	std::string _units; // Credits
	std::string _program; // Major
	std::string _level; // Freshman, sophmore, junior, senior, graduate

	int _numAbsences; // Number of absences

	Stack _absenceStack;
};

std::ostream& operator<<(std::ostream& os, const Data& data);

