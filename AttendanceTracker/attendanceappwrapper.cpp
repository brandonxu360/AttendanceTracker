/*
* Name: Brandon Xu
* Project: AttendanceTracker
* File: attendanceappwrapper.cpp
* Date: 4/3/23
* Description: Source file for the AttendanceAppWrapper class, which encapuslates the entire
*			   project's functionality
*/

#include "attendancappwrapper.hpp"

// Runs app - main executable logic
void AttendanceAppWrapper::runApp() {

	int menuChoice = -1;

	while (menuChoice != 7) { // Loop until user chooses to quit

		menuChoice = getMenuChoice(); // Print menu and get user choice

		switch (menuChoice) { // Main switch for menu actions based on user choice
		
		case 1: // Import couse list from classlist.csv file

			_readClassListF.open("classList.csv"); // Open classList.csv file stream for read

			loadRecords(_readClassListF);

			std::cout << _masterList;
			system("pause");

			_readClassListF.close(); // Close classList.csv file stream

			break;

		case 2: // Load master list from master.csv file

			_readMasterF.open("master.csv"); // Open master.csv file stream for read

			loadRecords(_readMasterF);

			std::cout << _masterList;
			system("pause");

			_readMasterF.close(); // Close master.csv file stream

			break;

		case 3: // Store master list to master.csv file

			_writeMasterF.open("master.csv"); // Open master.csv file stream for write

			_writeMasterF << _masterList;

			_writeMasterF;

			break;

		case 4: // Mark absences

			markAbsences();

			std::cout << _masterList;
			system("pause");

			break;

		case 5:

			editAbsences();

			break;

		case 6: // Generate reports

			int reportChoice = -1;

			// Print sub-menu options
			std::cout << "GENERATE REPORTS" << std::endl << std::endl;
			std::cout << "[1] Generate report for all students; showing only the most recent absence for each student." << std::endl;
			std::cout << "[2] Generate report for students with absences that match or exceed a specified number." << std::endl;
			std::cout << "[3] Return to main menu." << std::endl << std::endl;
			std::cout << "Input: ";
			std::cin >> reportChoice;

			while (reportChoice != 1 && reportChoice != 2 && reportChoice != 3) {
				std::cout << "Invalid user input try again" << std::endl << std::endl;
				std::cout << "Input: ";
				std::cin >> reportChoice;
			}

			switch (reportChoice) {
			case 1:
				generateReportByAbsences(false); // Default to 0 for absence floor so that every student is included
				break;
			case 2:
				generateReportByAbsences(true); // Allow user to choose absence floor
				break;
			case 3:
				break;
			}
			break;
		}
	}

	// Goodbye message
	system("cls");
	std::cout << "ATTENDANCE TRACKER" << std::endl << std::endl;
	std::cout << "Application terminated" << std::endl;

}

// Populates the member master list with the data from the inputted file
bool AttendanceAppWrapper::loadRecords(std::fstream& fileStream) {
	
	if (!fileStream.is_open()) return false; // Check that the filestream is open

	std::string token;
	std::string temp; // Temporary string to hold first half of name

	if (!fileStream.eof()) getline(fileStream, token); // Skip the first line

	while (!fileStream.eof()) { // Loop until the end of the file

		Data* newData = new Data; // Create a new Data object to store the information

		getline(fileStream, token, ','); // Get and set record number
		newData->setRecordNum(stoi(token));

		getline(fileStream, token, ','); // Get and set ID
		newData->setID(stoi(token));

		getline(fileStream, temp, ','); // Get first half of name
		getline(fileStream, token, ','); // Get last half of name
		temp += " ";
		temp += token; // Join them back together without the quotes
		temp.erase(std::remove(temp.begin(), temp.end(), '\"'), temp.end()); // Remove quotes
		newData->setName(temp);

		getline(fileStream, token, ','); // Get and set email
		newData->setEmail(token);

		getline(fileStream, token, ','); // Get and set units
		newData->setUnits(token);

		getline(fileStream, token, ','); // Get and set program
		newData->setProgram(token);

		getline(fileStream, token); // Get and set level
		newData->setLevel(token);

		_masterList.insertAtEnd(newData);
	}

	return true;
}

// Writes data from _masterList into inputted filestream
bool AttendanceAppWrapper::storeRecords(std::ofstream& fileStream) {

	if (!fileStream.is_open()) return false; // Check that the filestream is open

	fileStream << _masterList;

}

// Prints menu and returns user choice
int AttendanceAppWrapper::getMenuChoice() {

	int choice = 0, attempt = 0;

	do {

		system("cls");

		if (attempt != 0) { // Invalid error catch
			attempt--;
			std::cout << "ERROR: Invalid user input try again" << std::endl << std::endl;
		}

		// Print menu
		std::cout << "ATTENDANCE TRACKER" << std::endl << std::endl;
		std::cout << "[1] Import course list" << std::endl;
		std::cout << "[2] Load master list" << std::endl;
		std::cout << "[3] Store master list" << std::endl;
		std::cout << "[4] Mark absences" << std::endl;
		std::cout << "[5] Edit absences" << std::endl;
		std::cout << "[6] Generate report" << std::endl;
		std::cout << "[7] Exit" << std::endl << std::endl;
		std::cout << "Input: ";
		std::cin >> choice; // Get user choice

		attempt++;

	} while (choice < 1 || choice > 7); // Loop while invalid input is detected

	return choice;
}

// Traverses the master list and allows user to add absences to absence stack
void AttendanceAppWrapper::markAbsences() {
	for (Node<Data>* current = _masterList.getPHead(); current != nullptr; current = current->getPNext()) {
		system("cls");
		std::cout << "ATTENDANCE TRACKER" << std::endl << std::endl;

		bool absent = isAbsent(*(current->getData())); // Determine if student is absent

		if (absent) {
			current->getData()->incrementNumAbsences(); // Increment number of absences by 1

			// Get current date
			auto now = std::chrono::system_clock::now();
			std::time_t time_now = std::chrono::system_clock::to_time_t(now);

			// Format date string
			std::stringstream ss;
			ss << std::put_time(std::localtime(&time_now), "%m/%d/%y");
			std::string date_str = ss.str();

			// Push date string onto stack
			current->getData()->getAbsenceStack().push(date_str);
		}
	}
}



// Prompts user for absence status of singular student and returns bool
bool AttendanceAppWrapper::isAbsent(Data& student) {

	int choice = 0;

	std::cout << student << std::endl; // Display student in question

	std::cout << "Present - enter 1" << std::endl;
	std::cout << "Absent  - enter 0" << std::endl << std::endl;

	std::cout << "Input: ";
	std::cin >> choice; // Get user choice

	while (choice != 1 && choice != 0) { // Invalid input check
		std::cout << "ERROR: Invalid user input try again" << std::endl << std::endl;

		std::cout << "Input: ";
		std::cin >> choice; // Get user choice
	}

	if (choice == 0) return true; // Absent
	else return false; // Present
	
}

void AttendanceAppWrapper::editAbsences() {
	system("cls");
	std::cout << "EDIT ABSENCES" << std::endl << std::endl;

	std::string searchInput;
	int searchOption;
	bool found = false;

	std::cout << "Search for a student by:" << std::endl;
	std::cout << "1. ID" << std::endl;
	std::cout << "2. Name" << std::endl;
	std::cin >> searchOption;

	if (searchOption == 1) {
		std::cout << "Enter student ID: ";
		std::cin >> searchInput;
	}
	else if (searchOption == 2) {
		std::cout << "Enter student name: ";
		std::cin.ignore();
		std::getline(std::cin, searchInput);
	}
	else {
		std::cout << "Invalid input." << std::endl;
		return;
	}

	// Search for the student in the master list
	for (Node<Data>* current = _masterList.getPHead(); current != nullptr; current = current->getPNext()) {
		if ((searchOption == 1 && std::to_string(current->getData()->getID()) == searchInput) ||
			(searchOption == 2 && current->getData()->getName() == searchInput)) {
			found = true;

			std::cout << std::endl;
			std::cout << *current->getData() << std::endl; // Display the student's record

			std::cout << "Enter the date of the absence you want to remove (MM/DD/YY), or 0 to go back: ";
			std::string removeDate;
			std::cin >> removeDate;

			if (removeDate == "0") {
				return; // Go back to the main menu
			}
			else {
				bool foundDate = false;

				// Search for the absence with the specified date
				Stack& absenceStack = current->getData()->getAbsenceStack();
				while (!absenceStack.isEmpty()) {
					std::string topDate;
					absenceStack.peek(topDate);

					if (topDate == removeDate) {
						foundDate = true;
						absenceStack.pop(); // Remove the absence from the stack
						current->getData()->decrementNumAbsences(); // Decrement the number of absences by 1
						std::cout << "Absence for " << removeDate << " has been removed." << std::endl;
						break;
					}
					else {
						absenceStack.pop(); // Pop the absence from the stack and push it back if it's not the one to remove
						absenceStack.push(topDate);
					}
				}

				if (!foundDate) {
					std::cout << "No absence found for " << removeDate << "." << std::endl;
				}
			}

			break;
		}
	}

	if (!found) {
		std::cout << "Student not found." << std::endl;
	}

	system("pause");
}


// Generate report for students with absences that match or exceed a specified number
void AttendanceAppWrapper::generateReportByAbsences(bool promptUser) {

	int absenceNum = 0; // Be default, every student will be in the report

	if (promptUser) { // If the user is meant to pick the floor number
		std::cout << "Enter target absence floor number: ";
		std::cin >> absenceNum;

		system("cls");
	}

	std::cout << "ATTENDANCE TRACKER" << std::endl << std::endl;

	// Print header line
	std::cout << std::setw(15) << "ID" << std::setw(25) << "Name" << std::setw(20) << "Program"
		<< std::setw(20) << "Level" << std::setw(25) << "Most Recent Absence" << std::endl;

	// Iterate through each student in the list
	for (Node<Data>* current = _masterList.getPHead(); current != nullptr; current = current->getPNext()) {
		Data* student = current->getData();

		if (student->getNumAbsences() < absenceNum) continue; // Skip the inclusion of the student in the report if they do not meet the absence number

		// Get most recent absence
		std::string mostRecentAbsence = "No absences";
		if (!student->getAbsenceStack().isEmpty()) student->getAbsenceStack().peek(mostRecentAbsence);

		// Print the student's information and their most recent absence date
		std::cout << std::setw(15) << student->getID() << std::setw(25) << student->getName() << std::setw(20)
			<< student->getProgram() << std::setw(20) << student->getLevel() << std::setw(25) << mostRecentAbsence
			<< std::endl;
	}

	system("pause"); // Allow user to read report
}