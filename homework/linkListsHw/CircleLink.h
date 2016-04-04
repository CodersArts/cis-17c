/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DoubleLink.h
 * Author: michael
 *
 * Created on March 28, 2016, 10:17 AM
 */

#ifndef CIRCLELINK_H
#define CIRCLELINK_H

#include <new>
#include <cstdlib>

using namespace std;

template <class T>
class CircleLink {
	private:
		struct Node{
			T data;
			Node *next;
		};
		Node *head;
		Node *tail;
		int size;
		void memError();
		void subError();
	public:
		CircleLink();
		virtual ~CircleLink();
		void push( T data );
		bool pop();
		T at( int index );
		T operator[]( int index );
		void display();
		bool find( T data );
};

template <class T>
CircleLink<T>::CircleLink(){
	head = NULL;
	tail = NULL;
	size = 0;
}

template <class T>
CircleLink<T>::~CircleLink(){
	if( head ){
		tail->next = NULL; //break the circle then delete like a plain link list
		do {
			tail = head;
			head = head->next;
			delete tail;
		} while( head );
		delete head;
	}
}

template <class T>
void CircleLink<T>::push( T data ){
	if( head == NULL ){
		Node *node = new Node;
		node->data = data;
		node->next = node;
		head = node;
		tail = head;
		size++;
	} else {
		Node *node = new Node;
		node->data = data;
		node->next = head;
		tail->next = node;
		tail = node;
		size++;
	}
}

template <class T>
bool CircleLink<T>::pop(){
	if( head ){
		Node *newTail = head;
		do{
			if( newTail->next == tail  ){
				break;
			}
			newTail = newTail->next;
		} while( true );
		newTail->next = head;
		delete tail;
		tail = newTail;
		size--;
	}
}

template <class T>
T CircleLink<T>::at( int index ){
	if( index < 0 || index < size ){
		Node *temp = head;
		for( int i = 0; i < index; i++ ){
			temp = temp->next;
		}
		return temp->data;
	} else {
		subError();
	}
}

template <class T>
T CircleLink<T>::operator []( int index ) {
	return at( index );
}

template <class T>
void CircleLink<T>::memError() {
   cout << "ERROR:Cannot allocate memory.\n";
   exit(EXIT_FAILURE);
}

template <class T>
void CircleLink<T>::subError() {
   cout << "ERROR: Subscript out of range.\n";
   exit(EXIT_FAILURE);
}

template <class T>
void CircleLink<T>::display(){
	Node *current = head;
	do{
		cout << current->data << ", ";
		if( current == tail ){
			break;
		}
		current = current->next;
	} while( true );
	cout << endl;
}

template <class T>
bool CircleLink<T>::find(T data) {
	Node *current = head;
	do{
		if( current->data == data ){
			return true;
		}
		if( current == tail ){
			return false;
		}
		current = current->next;
	} while( true );
	cout << endl;
}
#endif /* DOUBLELINK_H */

