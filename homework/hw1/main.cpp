/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: michael
 *
 * Created on February 17, 2016, 9:08 PM
 */

#include <iostream>
#include <cmath>
#include <ctime>
#include <stdlib.h>

#include "Array.h"
#include "Table.h"
using namespace std;

int main(int argc, char** argv) {
	srand( time( 0 ) );
	Table arr( 6,3 );
	arr.print();
	return 0;
}

/*
 * class rowarry
 *		number of rows
 *		dynamically create, random 2 digit numbers
 * 
 * class table
 *		*rowarray
 *		number of rows, and columns
 */
