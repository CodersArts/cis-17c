/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: michael
 *
 * Created on April 14, 2016, 5:13 PM
 */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <new>
#include <sys/time.h>
#include <cmath>
#include "preciseClock.h"
#include "vectors.h"
#include "Analize.h"

using namespace std;


void p1( );
float p1G( float x, Analize* );
void p2( );
void p3( );
int power( int, unsigned int );
float p3G( float, Analize* );
float p3H( float, Analize* );
void p5( );
int *fillArray( int );
int *fillArray( int, bool );
bool linear( int find, int* arr, int size, Analize* an );
bool binary( int find, int* arr, Analize* an, int start, int end );
void p6( );
void markSort( int *a, int size, Analize* an );
void print( int *a, int n );
void p7( );
int getRand( int );

int main( int argc, char** argv ) {
	srand( time( 0 ) );

//	p1( );
//	p2();
//	p3();
//	p5();
//	p6();
	p7();
	return 0;
}
void p1( ) {
	int size = 8e6;
	Analize* an = new Analize;
	int cbeg = time( 0 );
	for ( int i = 0; i < size; i++ ) {
		p1G( .1, an );
	}
	int cend = time( 0 );
	cout << "Total time = " << cend - cbeg << "(secs) with n = " << size << endl;
	an->print( );
	delete an;
	//	cout << p1G( .1) <<  endl;;
}

float p1G( float x, Analize* an ) {
	an->ccmp++;
	if ( abs( x ) < 10e-6 ) {
		return x + ( ( x * x * x ) / 6 );
	}
	an->ceq++;
	float y = p1G( x / 2, an );
	return ( 2 * y ) / ( 1 + ( y * y ) );
}

void p2( ) {
	cout << power( -2, 2 ) << endl;
}

int power( int x, unsigned int y ) {
	if ( y == 0 ) {
		return 1;
	}
	int temp = power( x, y / 2 );
	if ( y % 2 == 0 ) {
		return temp * temp;
	} else {
		return x * temp * temp;
	}
}

void p3( ) {
	int size = 8000;
	Analize* an = new Analize;
	int cbeg = time( 0 );
	for( int i = 0; i < size; i++ ){
		p3G( .1, an );
	}
	int cend = time( 0 );
	cout << "Total time = " << cend - cbeg << "(secs) with n = " << size << endl;
	an->print( );
	delete an;
	
}

float p3G( float x, Analize* an ) {
	an->ccmp++;
	if ( abs( x ) < 10e-6 ) {
		return x + ( ( x * x * x ) / 2 );
	}
	an->ceq+=2;
	float y = p3G( x / 2, an );
	float z = p3H( x / 2, an );
	return 2 * y * z;
}

float p3H( float x, Analize* an ) {
	an->ccmp++;
	if ( abs( x ) < 10e-6 ) {
		return 1 + ( ( x * x ) / 2 );
	}
	an->ceq+=2;
	float y = p3G( x / 2, an );
	float z = p3H( x / 2, an );
	return ( z * z ) + ( y * y );
}

void p5( ) {
	int size = 100;
	int times = 8e6;
	int* array = fillArray( size, true );
	uint64 start, end;
	
	Analize* linearAn = new Analize;
	int find = array[size - 1];
	start = GetTimeMs64( );
	for( int i = 0; i < times; i++ ){
		linear( find, array, size, linearAn);
	}
	end = GetTimeMs64( );
	cout << "linear find : " << find << endl;
	linearAn->print( );
	long derp = ( end - start ); //because doing it a cout wont give me the time
	cout << "Total time = " << derp << "(ms) with n = " << times << endl;
	delete [] array;
	delete linearAn;

	cout << "\n\n";

	array = fillArray( size, true );
	Analize* binaryAn = new Analize;
	start = GetTimeMs64( );
	for( int i = 0; i < times; i++ ){
		binary( find, array, binaryAn, 0, size - 1 );
	}
	end = GetTimeMs64( );
	cout << "binary find : " << find << endl;
	binaryAn->print( );
	derp = ( end - start ); //because doing it a cout wont give me the time
	cout << "Total time = " << derp << "(ms) with n = " << times << endl;
	delete [] array;
	delete binaryAn;
}

bool linear( int find, int* arr, int size, Analize* an ) {
	an->ceq++;
	for ( int i = 0; i < size; i++ ) {
		an->ccmp++;
		an->cinc++;
		an->ccmp++;
		if ( arr[i] == find ) {
			return true;
		}
	}
	return false;
}

bool binary( int find, int* arr, Analize* an, int start, int end ) {
	an->ccmp++;
	if ( start > end ) return false;
	an->ceq++;
	int mid = ( start + end ) / 2;

	if ( find == arr[mid] ) {
		an->ccmp++;
		return true;
	} else if ( arr[ mid ] > find ) {
		an->ccmp += 2;
		binary( find, arr, an, start, mid - 1 );
	} else {
		an->ccmp += 3;
		binary( find, arr, an, mid + 1, end );
	}
}

int *fillArray( int size ) {
	return fillArray( size, false );
}

int *fillArray( int size, bool sorted ) {
	try {
		int* arr = new int[size];
		for ( int i = 0; i < size; i++ ) {
			arr[i] = sorted ? i : rand( ) % size;
		}
		return arr;
	} catch ( bad_alloc& ba ) {
		cerr << "bad_alloc caught: " << ba.what( ) << endl;
	}
}

void p6( ) {
	int size = 1000;
	int times = 80000;
	int* array = fillArray( size );
	uint64 start, end;
	//	print( array, size );
	cout << endl;
	Analize* an = new Analize;

	int offset = 0; //time offset
	start = GetTimeMs64( );
	for( int i = 0; i < times; i++ ){
		markSort( array, size, an );
		int os = GetTimeMs64();
		delete [] array;
		array = fillArray( size );
		int oe = GetTimeMs64();
		offset += ( oe - os );
	}
	end = GetTimeMs64( );
	an->print( );
	long derp = ( end - start ) - offset; //because doing it a cout wont give me the time
	cout << "Total time = " << derp << "(ms) with n = " << times << " and only sorting " << ( size * 0.01 ) << endl;
	//	print( array, size );
	cout << endl;
	delete [] array;
	delete an;

}

void markSort( int *a, int size, Analize* an ) {
	//Declare variables
	int cswap = 0;
	an->ceq++;
	int stop = size * 0.01;
	for ( int pos = 0; pos < stop; pos++ ) {
		an->ccmp++;
		an->cinc++;
		an->ceq++;
		for ( int row = pos + 1; row < size; row++ ) {
			an->ccmp++;
			an->cinc++;
			if ( *( a + pos ) > *( a + row ) ) {
				int temp = *( a + row );
				a[row] = a[pos];
				*( a + pos ) = temp;
				an->ceq+=3;
			}
			an->ccmp++;
		}
	}
//	cout << "swaps: " << cswap << endl;
}

void print( int *a, int n ) {
	for ( int i = 0; i < n; i++ ) {
		cout << a[i] << ", ";
	}
	cout << endl;
}

void p7( ) {
	int size = 4000;
	int start = 0, end = 0;
//	SimpleVector<int> vec( size );
//	Analize* simpleAn = new Analize;
//	start = GetTimeMs64();
//	for( int i = 0; i < size; i++ ){
//		vec.pushSort( getRand( size ), simpleAn );
//	}
//	end = GetTimeMs64();
//	simpleAn->print();
//	cout << "Total time = " << ( end - start ) << "(ms) with n = " << size << endl;
//	delete simpleAn;
	
//	Vector<int> vec;
//	Analize* vecAn = new Analize;
//	start = GetTimeMs64();
//	for( int i = 0; i < size; i++ ){
//		vec.pushSort( getRand( size ), vecAn );
//	}
//	end = GetTimeMs64();
//	vecAn->print();
//	cout << "Total time = " << ( end - start ) << "(ms) with n = " << size << endl;
//	delete vecAn;
	
	LinkList<int> ll;
	Analize* llAn = new Analize;
	start = GetTimeMs64();
	for ( int i = 0; i < size; i++ ) {
		ll.pushSort( getRand( size ), llAn );
	}
	end = GetTimeMs64();
	llAn->print( );
	cout << "Total time = " << ( end - start ) << "(ms) with n = " << size << endl;
	delete llAn;
}

int getRand( int size ) {
	return rand( ) % size;
}