/*
* Name: Brandon Xu
* Project: AttendanceTracker
* File: node.hpp
* Date: 4/3/23
* Description: Header file for the Node class, a template class that will represent generic nodes in 
*			   the List class. Contains a generic data object and a pointer to the next node.
*/

#include "header.hpp"

template <class T>
class Node {

public:

	Node(); // Default constructor

	Node(T* newData); // Constructor that takes pointer to new data 

	// Getter functions
	Node<T>* getPNext();
	T* getData();

	// Setter functions
	void setPNext(Node<T>* node);
		
private:

	T* _data; // Data object
	Node<T>* _pNext; // Pointer to next node

};

// Default constructor
template <class T>
Node<T>::Node() {

	// Initialize empty node
	_data = nullptr;
	_pNext = nullptr;

}

// Constructor that takes pointer to new data 
template <class T>
Node<T>::Node(T* newData) {

	_data = newData;
	_pNext = nullptr;

}

// Getter functions
template <class T>
Node<T>* Node<T>::getPNext() {
	return _pNext;
}

template <class T>
T* Node<T>::getData() {
	return _data;
}

// Setter functions
template <class T>
void Node<T>::setPNext(Node<T>* node) {
	_pNext = node;
}