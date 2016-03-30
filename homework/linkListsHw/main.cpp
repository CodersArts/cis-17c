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
int main( int argc, char** argv ) {
	/*
	DoubleLink<int> dblVec;
	dblVec.push_back( 5 );
	dblVec.push_back( 2 );
	dblVec.push_back( 3 );
	
	cout << dblVec[2];
	dblVec.pop_back();
	cout << dblVec[2];
	*/
	
	/*
	Stack<int> stack;
	stack.push( 5 );
	stack.push( 2 );
	stack.push( 3 );
	
	cout << stack[2];
	stack.pop();
	cout << stack[2];
	*/
	
	CircleLink<int> circle;
	circle.push( 1 );
	circle.push( 2 );
	circle.push( 3 );
	
	circle.display();
	circle.pop();
	circle.display();
	
}

