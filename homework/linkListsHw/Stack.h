/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Stack.h
 * Author: michael
 *
 * Created on March 28, 2016, 10:13 AM
 */

#ifndef STACK_H
#define STACK_H

#include <cstdlib>

using namespace std;

template <class T>
class Stack {
	private:
		struct Node{
			T data;
			Node *next;
		};
		Node *head;
		Node *worker;
		int size;
		void memError(){
			cout << "ERROR:Cannot allocate memory.\n";
			exit(EXIT_FAILURE);
		}
		void subError(){
			cout << "ERROR: Subscript out of range.\n";
			exit(EXIT_FAILURE);}
	public:
		Stack();
		virtual ~Stack();
		void push( T data );
		bool pop();
		T at( int index );
		T operator[]( int index );
		void display();
		bool find( T data );
};


template <class T>
Stack<T>::Stack(){
	head = NULL;
	worker = NULL;
	size = 0;
}

template <class T>
Stack<T>::~Stack(){
	if ( head ) { //if head is set
		do {
			worker = head; //set head to tail
			head = head->next; //set the head to be the old head link
			delete worker; //delete tail
		} while ( head );
	}
}

//push to the top like a stack of plates
template <class T>
void Stack<T>::push( T data ){
	if( !head ){
		try{
			Node *temp = new Node;
			temp->next = NULL;
			temp->data = data;
			head = temp;
			size++;
		} catch( bad_alloc ) {
			memError();
		}
	} else {
		try{ 
			Node *temp = new Node;
			temp->data = data;
			temp->next = head;
			head = temp;
			size++;
		} catch( bad_alloc ) {
			memError();
		}
	}
}

template <class T>
bool Stack<T>::pop(){
	if( head ){ 
		Node *newHead = head->next;
		head->next = NULL;
		delete head;
		head = newHead;
		return true;
	}
	return false;
}

template <class T>
T Stack<T>::at(int index) {
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
T Stack<T>::operator [](int index){
	return at( index );
}

template <class T>
void Stack<T>::display(){
	Node *current = head;
	do{
		cout << current->data << ", ";
	} while( ( current = current->next ) );
	cout << endl;
}

template <class T>
bool Stack<T>::find(T data){
	Node *current = head;
	do{
		if( current->data == data ) return true;
	} while( ( current = current->next ) );
	return false;
}

#endif /* STACK_H */

