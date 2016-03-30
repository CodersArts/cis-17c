/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SimpleVector.h
 * Author: michael
 *
 * Created on March 22, 2016, 6:33 PM
 */

#ifndef SIMPLEVECTOR_H
#define SIMPLEVECTOR_H

#include <cstdlib>

using namespace std;

template <class T>
class SimpleVector {
	public:
		SimpleVector();
		SimpleVector(const SimpleVector& orig); //TODO
		virtual ~SimpleVector();
		void push_back( T data );
		bool pop_back();
		T at( int index );
		T operator[]( int index );
	private:
		struct Node{
			T data;
			Node *link;
		};
		Node *head;
		Node *tail;
		int size;
		void memError();
		void subError();

};

template <class T>
SimpleVector<T>::SimpleVector(){
	head = NULL;
	tail = NULL;
	size = 0;
}

template <class T>
SimpleVector<T>::~SimpleVector(){
	if ( head ) { //if head is set
		do {
			tail = head; //set head to tail
			head = head->link; //set the head to be the old head link
			delete tail; //delete tail
		} while ( head );
	}
}

template <class T>
void SimpleVector<T>::push_back( T data ) {
	if( !this->head ){
		try {
			Node *temp = new Node;
			temp->data = data;
			temp->link = NULL;
			head = temp;
			tail = head;
			size++;
		} catch( bad_alloc ){
			this->memError();
		}
	} else {
		try{
			Node *temp = new Node;
			temp->data = data;
			temp->link = NULL;
			tail->link = temp;
			tail = temp;
			size++;
		} catch( bad_alloc ) {
			this->memError();
		}
	}
}

template <class T>
bool SimpleVector<T>::pop_back(){
	if( head ){
		Node *current = head;
		do{
			if( current->link == NULL ){
				break;
			}
			current = current->link;
		} while( true );
		current->link = NULL;
		delete tail;
		tail = current;
	}
}

template <class T>
T SimpleVector<T>::at( int index ){
	if( index < 0 || index < size ){
		Node *temp = head;
		for( int i = 0; i < index; i++ ){
			temp = temp->link;
		}
		return temp->data;
	}
	return 0;
}

template <class T>
T SimpleVector<T>::operator []( int index ) {
	return at( index );
}

//*******************************************************
// memError function. Displays an error message and     *
// terminates the program when memory allocation fails. *
//*******************************************************

template <class T>
void SimpleVector<T>::memError()
{
   cout << "ERROR:Cannot allocate memory.\n";
   exit(EXIT_FAILURE);
}

//***********************************************************
// subError function. Displays an error message and         *
// terminates the program when a subscript is out of range. *
//***********************************************************

template <class T>
void SimpleVector<T>::subError()
{
   cout << "ERROR: Subscript out of range.\n";
   exit(EXIT_FAILURE);
}

#endif /* SIMPLEVECTOR_H */

