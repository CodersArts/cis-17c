/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SimpleVector.h
 * Author: michael
 *
 * Created on April 17, 2016, 1:45 PM
 */

#ifndef VECTORS_H
#define VECTORS_H

#include <iostream>
#include <new>       // Needed for bad_alloc exception
#include <cstdlib>
#include "Analize.h"

using namespace std;

template <class T>
class SimpleVector {
private:
	T *aptr; // To point to the allocated array
	int arraySize; // Number of elements in the array
	int usedSize; // used size
public:

	SimpleVector() {
		aptr = 0;
		arraySize = 0;
		usedSize = 0;
	}

	SimpleVector(int s) {
		arraySize = s;
		usedSize = 0;
		// Allocate memory for the array.
		try {
			aptr = new T [s];
		} catch ( bad_alloc ) {
			cout << "ERROR:Cannot allocate memory.\n";
			exit( EXIT_FAILURE );
		}

		// Initialize the array.
		for ( int count = 0; count < arraySize; count++ )
			*( aptr + count ) = 0;
	}

	~SimpleVector() {
		if ( arraySize > 0 )
			delete [] aptr;
	}

	void display() {
		for ( int i = 0; i < usedSize; i++ ) {
			cout << aptr[i] << ", ";
		}
	}

	void pushBack(T item, Analize* an) {
		an->ccmp++;
		if ( usedSize != arraySize ) {
			an->ceq++; an->cinc++;
			aptr[usedSize++] = item;
		}
	}

	void pushFront(T item, Analize* an) {
		an->ccmp++;
		if ( usedSize != arraySize ) {
			an->ceq++;
			for ( int i = usedSize - 1; i >= 0; i-- ) {
				an->cinc++; an->ccmp++; an->ceq++;
				aptr[ i + 1 ] = aptr[i];
			}
			an->ceq++;
			aptr[0] = item;
			an->cinc++;
			usedSize++;
		}
	}

	void pushSort(T item, Analize* an ) {
		an->ccmp++;
		if ( usedSize != arraySize ) { 
			insert( item, 0, usedSize - 1, an );
		}
	}

	void insert(T item, int start, int end, Analize*  an) {
		an->ceq++;
		int mid = start + ( ( end - start ) / 2 );
		an->ccmp++;
		if ( usedSize == 0 ) {
			an->ceq++; an->cinc++;
			aptr[0] = item;
			usedSize++;
			return;
		}
		an->ccmp++;
		if ( item > aptr[end] ) {
			an->ceq++;
			for ( int i = usedSize - 1; i >= end + 1; i-- ) {
				an->ccmp++;an->cinc++;an->ceq++;
				aptr[ i + 1] = aptr[i];
			}
			an->ceq++;an->cinc++;
			aptr[ end + 1] = item;
			usedSize++;
			return;
		} else if ( item <= aptr[start] ) {//put it at the front
			an->ceq++;
			for ( int i = usedSize - 1; i >= start; i-- ) {
				an->ccmp++;an->cinc++;an->ceq++;
				aptr[ i + 1] = aptr[i];
			}
			an->ceq++;an->cinc++;
			aptr[ start ] = item;
			usedSize++;
			return;
		}
		if ( start >= end ) {
			an->ccmp++;
			//exit case
			return;
		}
		if ( item < aptr[mid] ) {
			an->ccmp++;
			insert( item, start, mid - 1, an );
		} else if ( item >= aptr[ mid ] ) {
			an->ccmp++;
			insert( item, mid + 1, end, an );
		}
	}
};

template<class T>
class Vector {
private:
	int usedSize;
	int arraySize;
	T* aptr;
public:

	Vector() {
		arraySize = 10;
		usedSize = 0;
		aptr = new T[arraySize];
	}

	~Vector() {
		if ( arraySize > 0 )
			delete [] aptr;
	}

	void display() {
		for ( int i = 0; i < usedSize; i++ )
			cout << aptr[i] << ", ";
	}

	void pushBack(T item, Analize* an ) {
		an->ccmp++;
		if ( usedSize >= arraySize ) {
			an->ceq+=3;
			T* temp = new T[ ( arraySize == 0 ? 1 : arraySize * 2 ) ];
			arraySize = ( arraySize == 0 ? 1 : arraySize * 2 );
			for ( int i = 0; i < usedSize; i++ ) {
				an->cinc++;an->ccmp++;an->ceq++;
				temp[i] = aptr[i];
			}
			delete [] aptr;
			an->ceq+=2;
			temp[usedSize++] = item;
			aptr = temp;
		} else {
			an->ceq++;
			aptr[usedSize++] = item;
		}
	}

	void pushFront(T item, Analize* an ) {
		an->ccmp++;
		if ( usedSize >= arraySize ) {
			an->ceq+=2;
			T* temp = new T[ arraySize *2 ];
			for ( int i = 0; i < usedSize; i++ ) {
				an->cinc++;an->ccmp++;an->ceq++;
				temp[i + 1] = aptr[i];
			}
			an->cinc++;
			arraySize *= 2;
			delete [] aptr;
			an->cinc++; an->ceq+=2;
			temp[0] = item;
			usedSize++;
			aptr = temp;
		} else {
			an->ceq++;
			for ( int i = usedSize - 1; i >= 0; i-- ) {
				an->cinc++;an->ceq++;an->ccmp++;
				aptr[ i + 1 ] = aptr[i];
			}
			an->ceq++; an->cinc++;
			aptr[0] = item;
			usedSize++;
		}
	}
	
	void pushSort( T item, Analize* an ){
		an->ccmp++;
		if( usedSize >= arraySize ){
			an->ceq+=2;
			T* temp = new T[ arraySize * 2];
			for( int i = 0; i < arraySize; i++ ){
				an->cinc++;an->ccmp++;an->ceq++;
				temp[i] = aptr[i];
			}
			an->cinc++;
			arraySize *= 2;
			delete [] aptr;
			an->ceq++;
			aptr = temp;
			insert( item, 0, usedSize - 1, an );
		} else{
			insert( item, 0, usedSize - 1, an );
		}
	}
	
	void insert(T item, int start, int end, Analize*  an) {
		an->ceq++;
		int mid = start + ( ( end - start ) / 2 );
		an->ccmp++;
		if ( usedSize == 0 ) {
			an->ceq++; an->cinc++;
			aptr[0] = item;
			usedSize++;
			return;
		}
		an->ccmp++;
		if ( item > aptr[end] ) {
			an->ceq++;
			for ( int i = usedSize - 1; i >= end + 1; i-- ) {
				an->ccmp++;an->cinc++;an->ceq++;
				aptr[ i + 1] = aptr[i];
			}
			an->ceq++;an->cinc++;
			aptr[ end + 1] = item;
			usedSize++;
			return;
		} else if ( item <= aptr[start] ) {//put it at the front
			an->ceq++;
			for ( int i = usedSize - 1; i >= start; i-- ) {
				an->ccmp++;an->cinc++;an->ceq++;
				aptr[ i + 1] = aptr[i];
			}
			an->ceq++;an->cinc++;
			aptr[ start ] = item;
			usedSize++;
			return;
		}
		if ( start >= end ) {
			an->ccmp++;
			//exit case
			return;
		}
		if ( item < aptr[mid] ) {
			an->ccmp++;
			insert( item, start, mid - 1, an );
		} else if ( item >= aptr[ mid ] ) {
			an->ccmp++;
			insert( item, mid + 1, end, an );
		}
	}
};

template<class T>
class LinkList {
private:

	struct Node {
		T data;
		Node *next;
		Node *prev;
	};
	Node *head;
	Node *tail;
	int size;
public:

	LinkList() {
		head = NULL;
		tail = NULL;
		size = 0;
	}

	~LinkList() {
		if ( head ) { //if head is set
			do {
				tail = head; //set head to tail
				head = head->next; //set the head to be the old head link
				delete tail; //delete tail
			} while ( head );
		}
	}

	void memError() {
		cout << "ERROR:Cannot allocate memory.\n";
		exit( EXIT_FAILURE );
	}

	void display() {
		Node* current = head;
		for ( int i = 0; i < size; i++ ) {
			cout << current->data << ", ";
			current = current->next;
		}
	}

	void pushBack(T data, Analize* an ) {
		an->ccmp++;
		if ( !this->head ) {
			try {
				an->ceq+=6; an->cinc++;
				Node *temp = new Node;
				temp->data = data;
				temp->next = NULL;
				temp->prev = NULL;
				head = temp;
				tail = head;
				size++;
			} catch ( bad_alloc ) {
				this->memError( );
			}
		} else {
			try {
				an->ceq+=6; an->cinc++;
				Node *temp = new Node;
				temp->data = data;
				temp->next = NULL;
				temp->prev = tail;
				tail->next = temp;
				tail = temp;
				size++;
			} catch ( bad_alloc ) {
				this->memError( );
			}
		}
	}

	void pushFront(T data, Analize* an) {
		an->ccmp++;
		if ( !this->head ) {
			try {
				an->ceq+=6; an->cinc++;
				Node* temp = new Node;
				temp->data = data;
				temp->next = NULL;
				temp->prev = NULL;
				head = temp;
				tail = head;
				size++;
			} catch ( bad_alloc ) {
				this->memError( );
			}
		} else {
			try {
				an->ceq+=6; an->cinc++;
				Node* temp = new Node;
				temp->data = data;
				temp->next = head;
				temp->prev = NULL;
				head->prev = temp;
				head = temp;
				size++;
			} catch ( bad_alloc ) {
				this->memError( );
			}
		}
	}

	void pushSort(T data, Analize* an) {
		an->ccmp++;
		if ( !head ) {
			try {
				an->ceq+=6; an->cinc++;
				Node *node = new Node;
				node->data = data;
				node->next = NULL;
				node->prev = NULL;
				head = node;
				tail = head;
				size++;
			} catch ( bad_alloc ) {
				memError( );
			}
		} else {
			an->ceq+=6;
			Node *working = head;
			Node *node = new Node;
			node->data = data;
			node->next = NULL;
			node->prev = NULL;
			bool inserted = false;
			do {
				an->ccmp++;
				if ( working->data > node->data ) { //so put node in front
					an->ceq+=2;
					node->prev = working->prev;
					node->next = working;
					an->ccmp++;
					if ( working == head ) {
						an->ceq++;
						head = node;
					} else {
						an->ceq++;
						( working->prev )->next = node;
					}
					an->ceq+=2;
					working->prev = node;
					inserted = true;
					break;
				} else if ( working->next == NULL ) { //then it is the biggest element add to rear
					an->ceq+=3;
					node->prev = working;
					working->next = node;
					inserted = true;
					break;
				}
				an->ceq;
			} while ( ( working = working->next ) );
			if ( inserted ) {
				size++;an->cinc++;
			} else {
				cout << "Failed to insert element: " << data << endl;
			}
		}
	}
};

#endif /* VECTORS_H */

