/*
* Name: Brandon Xu
* Project: AttendanceTracker
* File: data.hpp
* Date: 4/3/23
* Description: Source file for the data class containing implementation details. Data objects
*			   will hold the student data (basic info, # of absences, and a stack containing
*			   dates of absences)
*/

#include "data.hpp"

// Setter functions
void Data::setRecordNum(int recordNum) {
	_recordNum = recordNum;
}

void Data::setID(int ID) {
	_ID = ID;
}

void Data::setName(std::string name) {
	_name = name;
}

void Data::setEmail(std::string email) {
	_email = email;
}

void Data::setUnits(std::string units) {
	_units = units;
}

void Data::setProgram(std::string program) {
	_program = program;
}

void Data::setLevel(std::string level) {
	_level = level;
}

// Increment _numAbsences by 1
void Data::incrementNumAbsences() {
	_numAbsences++;
}

// Decrement _numAbsences by 1
void Data::decrementNumAbsences() {
	_numAbsences--;
}

// Getter functions
int Data::getRecordNum() const {
	return _recordNum;
}

int Data::getID() const {
	return _ID;
}

std::string Data::getName() const {
	return _name;
}

std::string Data::getEmail() const {
	return _email;
}

std::string Data::getUnits() const {
	return _units;
}

std::string Data::getProgram() const {
	return _program;
}

std::string Data::getLevel() const {
	return _level;
}

int Data::getNumAbsences() const {
	return _numAbsences;
}

Stack& Data::getAbsenceStack() {
	return _absenceStack;
}

std::ostream& operator<<(std::ostream& os, const Data& data) {
	os << std::setw(18) << std::left << "Record Number:" << std::setw(3) << data.getRecordNum() << std::endl;
	os << std::setw(18) << std::left << "ID:" << std::setw(9) << data.getID() << std::endl;
	os << std::setw(18) << std::left << "Name:" << data.getName() << std::endl;
	os << std::setw(18) << std::left << "Email:" << data.getEmail() << std::endl;
	os << std::setw(18) << std::left << "Units:" << data.getUnits() << std::endl;
	os << std::setw(18) << std::left << "Program:" << data.getProgram() << std::endl;
	os << std::setw(18) << std::left << "Level:" << data.getLevel() << std::endl;
	os << std::setw(18) << std::left << "Num of Absences:" << std::setw(2) << data.getNumAbsences() << std::endl;
	return os;
}

