#pragma once
#include <string>
#include "LinkedListInterface.h"
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;

template<typename T>
class LinkedList: public LinkedListInterface<T>
{
private:
	struct Node {
		T val;
		Node *next;
		Node(T value){
			val = value;
			next = NULL;
		}
	};

	Node *head;
	Node *tail;
	int numItems;

public:

	LinkedList(void) {
		numItems = 0;
		head = NULL;
		tail = NULL;
	}
	~LinkedList(void) {
		//cout << "in destructor" << endl;
		Node *current = head;
		while (current != NULL){
			delete current;
			current = current->next;
		}
	}

	/*
	insertHead

	A node with the given value should be inserted at the beginning of the list.

	Do not allow duplicate values in the list.
	*/
	void insertHead(T value) {
		//cout << "in insert head" << endl;
		if(!findValue(value)){
			if(numItems == 0){
				//cout << "first item check" << endl;
				Node *n = new Node(value);
				head = n;
				tail = n;
			}
			else { 
				Node *n = new Node(value);
				n -> next = head;
				head = n;
			}
			//cout << "head val: " << head-> val << "  head next: " << head->next << endl;
			numItems++;
			//cout << "number of Items = " << numItems << endl;
		}
		else {
			//cout << "item not added -- duplicate" << endl;
		}
	}

	bool findValue(T value){
		Node *fakeItr = head;
		while (fakeItr != NULL){
			if(fakeItr->val == value){
				return true;
			}
			fakeItr = fakeItr->next;
		}
		return false;
	}

	/*
	insertTail

	A node with the given value should be inserted at the end of the list.

	Do not allow duplicate values in the list.
	*/
	void insertTail(T value) {
		//cout << "in insert tail" << endl;
		if (!findValue(value)){
			if(numItems == 0){
				//cout << "first item check" << endl;
				Node *n = new Node(value);
				head = n;
				tail = n;
			}
			else {
				Node *n = new Node(value);
				tail -> next = n;
				tail = n;
			}
			//cout << "tail val: " << tail-> val << "  tail next: " << tail->next << endl;
			numItems++;
			//cout << "number of Items = " << numItems << endl;
		}
	}

	/*
	insertAfter

	A node with the given value should be inserted immediately after the
	node whose value is equal to insertionNode.

	A node should only be added if the node whose value is equal to
	insertionNode is in the list. Do not allow duplicate values in the list.
	*/
	void insertAfter(T value, T insertionNode) {
		//cout << "in insertAfter" << endl;
		if(findValue(insertionNode)){
			if(!findValue(value)){
				//cout << "inserting value " << value << " after value " << insertionNode << endl;
				Node *n = new Node(value);
				Node *fakeItr = head;
				while (fakeItr != NULL){
					if(fakeItr->val == insertionNode){
						if(fakeItr -> next != NULL){
							n->next = fakeItr->next;
						}
						if(fakeItr -> next == NULL){
							tail = n;
							//cout << "tail val: " << tail-> val << "  tail next: " << tail->next << endl;
						}
						fakeItr->next = n;
						numItems++;
						//cout << "number of Items = " << numItems << endl;
					}
					fakeItr = fakeItr -> next;
				}
			}
		}
		else {
			//cout << "no item addedAfter" << endl;
		}
	}

	/*
	remove

	The node with the given value should be removed from the list.

	The list may or may not include a node with the given value.
	*/
	void remove(T value) {
		//cout << "in remove function" << endl;
		if(findValue(value)){
			//cout << "found val to remove " << endl;
			if(head->val == value){
				Node *ptr = head;
				head = head->next;
				numItems --;
				delete ptr;
			}
			else if (tail->val == value){
				for(Node *fakeItr = head; fakeItr != NULL; fakeItr = fakeItr->next){
					if((fakeItr->next) == tail){
						Node *ptr = tail;
						fakeItr->next = NULL;
						tail = fakeItr;
						numItems --;
						delete ptr;
						break;
					}
				}
			}
			else {
				for (Node *fakeItr = head; fakeItr != NULL; fakeItr = fakeItr->next){
					Node *ptr = fakeItr->next;
					if((fakeItr->next)->val == value){
						Node *ptr = fakeItr->next;
						fakeItr->next = ptr->next;
						//cout << "now fakeItr points to " << ptr->next << endl;
						delete ptr;
						numItems --;
						break;
					}
				}
			}
		}
	}

	/*
	clear

	Remove all nodes from the list.
	*/
	void clear() {
		while (head != NULL){
			remove(head->val);
		}
	}

	/*
	at

	Returns the value of the node at the given index. The list begins at
	index 0.

	If the given index is out of range of the list, throw an out of range exception.
	*/
	T at(int index) {
		if ((index < 0) || (index >= size())) {
    	throw out_of_range("out of range");
		}
		else {
			Node *fakeItr = head;
			int count = 0;
			while(fakeItr != NULL){
				if(count == index){
					return fakeItr->val;
				}
				count ++;
				fakeItr = fakeItr->next;
			}
		}
	}

	/*
	size

	Returns the number of nodes in the list.
	*/
	int size() {
		return numItems;
	}

	/*
	toString
	
	Returns a string representation of the list, with the value of each node listed in order (Starting from the head) and separated by a single space
	There should be no trailing space at the end of the string

	For example, a LinkedList containing the value 1, 2, 3, 4, and 5 should return
	"1 2 3 4 5"
	*/
	string toString() {
		//cout << "in toString()" << endl;
		stringstream ss;
		for (Node *fakeItr = head; fakeItr != NULL; fakeItr = fakeItr->next){
			if(fakeItr->next == NULL){
				ss << fakeItr->val;
			}
			else {
				ss << fakeItr->val << " ";
			}
		}
		//cout << ss.str() << endl;
		return (ss.str());
	}

};
