/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: michael
 *
 * Created on March 16, 2016, 8:48 PM
 */

#include <cstdlib>
#include <iostream>

#include "SimpleVector.h"

using namespace std;

int main( int argc, char** argv ) {
	SimpleVector<int> vec;
	vec.push_back( 1 );
	vec.push_back( 3 );
	
	cout << vec[1];
	
	return 0;
}

