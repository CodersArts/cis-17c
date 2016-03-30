/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: michael
 *
 * Created on March 16, 2016, 2:27 PM
 */

#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

void bubble( int*, int);
void print( int*, int );

int main( int argc, char** argv ) {
	srand( time( 0 ) );
	int size = 100;
	int* arr = new int[ size ];
	for( int i = 0; i < size; i++ ){
		arr[i] = ( rand() % 90 ) + 10;
	}
//	print( arr, size );
	bubble( arr, size );
//	print( arr, size );
	return 0;
}

void bubble( int* array, int size ){
	int ceq = 0, cinc = 0, ccmp = 0, cswap = 0;
	ceq++;
	bool swaped = false;
	ceq++;
	int len = size - 1;
	do{
		ceq++;
		swaped = false;
		ceq++; ccmp++; cinc++;
		for ( int i = 0; i < len; i++ ) {
			ccmp++;
			if ( array[i] > array[i+1] ) {
				cswap++;
				swap( array[i], array[i+1] );
				ceq++;
				swaped = true;
			}
		}
		cinc++;
		len--;
	}
	while( swaped );
	
	cout << "equations: " << ceq << endl;
	cout << "increments: " << cinc << endl;
	cout << "comparisons: " << ccmp << endl;
	cout << "swaps: " << cswap << endl;
}

void print( int* arr, int size ){
	for( int i = 0; i < size; i++ ){
		cout << arr[i] << ", ";
	}
	cout << endl;
}