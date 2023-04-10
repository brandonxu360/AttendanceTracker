/*
* Name: Brandon Xu
* Project: AttendanceTracker
* File: attendanceappwrapper.hpp
* Date: 4/3/23
* Description: Header file for the AttendanceAppWrapper class, which encapuslates the entire
*			   project's functionality
*/

#include "list.hpp"
#include "data.hpp"

class AttendanceAppWrapper {

public:

	void runApp(); // Runs app - main executable logic

	bool loadRecords(std::fstream& fileStream); // Populate _masterList with data from inputted filestream
	bool storeRecords(std::ofstream& fileStream); // Writes data from _masterList into inputted filestream
	int getMenuChoice(); // Prints menu and returns user choice
	void markAbsences(); // Traverses the master list and allows user to add absences to absence stack
	bool isAbsent(Data& student); // Prompts user for absence status of singular student and returns bool
	void editAbsences();
	void generateReportByAbsences(bool promptUser); // Generate report for students with absences that match or exceed a specified number
private:

	List<Data> _masterList; // Master list of student records

	// File streams
	std::fstream _readClassListF;
	std::fstream _readMasterF;
	std::ofstream _writeMasterF;
	

};