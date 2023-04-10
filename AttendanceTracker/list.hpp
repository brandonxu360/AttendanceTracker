/*
* Name: Brandon Xu
* Project: AttendanceTracker
* File: list.hpp
* Date: 4/3/23
* Description: Header file for the List class, a template container class to represent the master
*			   list, which is a singly linked list. Uses the Node class for the individual nodes.
*/

#include "node.hpp"

template <class T>
class List {

public:

	List(); // Default constructor

	bool insertAtEnd(T* newData); // Insert a new node containing newData input

	// Getter functions
	Node<T>* getPHead() const;

private:

	Node<T>* _pHead; // Pointer to head of list

};

// Default constructor
template <class T>
List<T>::List() {

	// Initialize empty list
	_pHead = nullptr;

}

// Insert a new node containing newData input
template <class T>
bool List<T>::insertAtEnd(T* newData) {

	Node<T>* newNode = new Node<T>(newData); // Create new node containing newData

	if (newNode == nullptr) return false; // Check if newNode was successfully created

	if (_pHead == nullptr) _pHead = newNode; // If list is empty, set head to newNode

	else {
		Node<T>* currNode = _pHead; // Create an interator node and set to head

		// Iterate through list until arriving at last node
		while (currNode->getPNext() != nullptr) currNode = currNode->getPNext();

		currNode->setPNext(newNode); // Set next node to the newNode
	}
	return true;
}

// Getter functions
template<class T> 
Node<T>* List<T>::getPHead() const{
	return _pHead;
}

// Overloaded << operator to print the list to console
template<class T>
std::ostream& operator<<(std::ostream& os, const List<T>& list) {

	// Print header line
	os << std::setw(10) << "Record #" << std::setw(15) << "ID" << std::setw(25) << "Name" << std::setw(30) 
		<< "Email" << std::setw(15) << "Units" << std::setw(20) << "Program" << std::setw(15) << "Level" 
		<< std::setw(15) << "Absences" << std::endl;

	// Iterate through each node in the list and print its Data object's fields in a table format
	for (Node<T>* current = list.getPHead(); current != nullptr; current = current->getPNext()) {
		T* data = current->getData();
		os << std::setw(10) << data->getRecordNum() << std::setw(15) << data->getID() << std::setw(25) << data->getName() 
			<< std::setw(30) << data->getEmail() << std::setw(15) << data->getUnits() << std::setw(20) << data->getProgram() 
			<< std::setw(15) << data->getLevel() << std::setw(15) << data->getNumAbsences() << std::endl;
	}

	return os;
}

template<class T>
std::ofstream& operator<<(std::ofstream& ofs, const List<T>& list) {
	// Print header line
	ofs << ",ID,Name,Email,Units,Program,Level" << std::endl;

	// Iterate through each node in the list and print its Data object's fields separated by commas
	for (Node<T>* current = list.getPHead(); current != nullptr; current = current->getPNext()) {
		T* data = current->getData();
		std::string name = data->getName();
		std::replace(name.begin(), name.end(), ' ', ','); // Replace space with comma

		ofs << data->getRecordNum() << ",";
		ofs << data->getID() << ",";
		ofs << "\"" << name << "\"" << ",";
		ofs << data->getEmail() << ",";
		ofs << data->getUnits() << ",";
		ofs << data->getProgram() << ",";
		ofs << data->getLevel() << ",";
		ofs << "\"" << data->getAbsenceStack() << "\"" << std::endl;
	}

	return ofs;
}

