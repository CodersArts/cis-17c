/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: michael
 *
 * Created on March 28, 2016, 10:12 AM
 */

#include <cstdlib>
#include <iostream>

using namespace std;

#include "DoubleLink.h"
#include "Stack.h"
#include "CircleLink.h"
#include "SortedList.h"
#include "PriorityList.h"
#include "Queue.h"

int main( int argc, char** argv ) {
	cout << "\n Double link list\n";
	DoubleLink<int> dblVec;
	dblVec.push( 3 );
	dblVec.push( 1 );
	dblVec.push( 10 );
	dblVec.push( 15 );
	dblVec.push( 8 );
	dblVec.display();
	dblVec.pop();
	dblVec.display();
	
	
	cout << "\n Stack list\n";
	Stack<int> stack;
	stack.push( 3 );
	stack.push( 1 );
	stack.push( 10 );
	stack.push( 15 );
	stack.push( 8 );
	stack.display();
	stack.pop();
	stack.display();
//	cout << stack.find( 10 ) << endl;
	
	cout << "\n Queue list\n";
	Queue<int> queue;
	queue.push( 3 );
	queue.push( 1 );
	queue.push( 10 );
	queue.push( 15 );
	queue.push( 8 );
	queue.display();
	queue.pop();
	queue.display();
//	cout << queue.find( 10 ) << endl;
	
	
	cout << "\n Circle list\n";
	CircleLink<int> circle;
	circle.push( 3 );
	circle.push( 1 );
	circle.push( 10 );
	circle.push( 15 );
	circle.push( 8 );
	circle.display();
	circle.pop();
	circle.display();
//	cout << circle.find( 10 ) << endl;
	
	
	cout << "\n Sorted list\n";
	SortedList<int> sort;
	sort.push( 3 );
	sort.push( 1 );
	sort.push( 10 );
	sort.push( 15 );
	sort.push( 8 );
	sort.display();
	sort.pop();
	sort.display();
//	cout << sort.find( 10 ) << endl;
	
	cout << "\nPriority list\n";
	PriorityList<int> plist;
	plist.push( 3 );
	plist.push( 1 );
	plist.push( 10 );
	plist.push( 15 );
	plist.push( 8 );
	plist.display();
	plist.pop();
	plist.display();
	cout << plist.find( 10 ) << endl;
	plist.display();
	
}

