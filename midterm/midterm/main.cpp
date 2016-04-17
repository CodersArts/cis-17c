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
#include "preciseClock.h"

using namespace std;
struct Analize{
	int ceq;
	int ccmp;
	int cinc;
	Analize() : ceq(0), ccmp(0), cinc(0) {};
	int total(){
		return ceq + ccmp + cinc;
	};
	void print(){ 
		cout << "C Equals: " << ceq << endl;
		cout << "C Compares: " << ccmp << endl;
		cout << "C Increments: " << cinc << endl;
		cout << "C Total: " << total() << endl;
	};
};

void p1();
void p2();
float p1G( float x );
void p5();
int *fillArray( int );
int *fillArray( int, bool );
bool linear( int find, int* arr, int size, Analize* an );
bool binary( int find, int* arr, Analize* an, int start, int end );

int main( int argc, char** argv ) {
	srand( time( 0 ) );
	
	p5();
	return 0;
}

void p1(){
	float x = 0; //idk
//	if( abs( x ) < 0.000001 ){ //return?? }
	float ret =  ( 2 * p1G( x / 2 ) ) / ( 1 + p1G( x / 2 ) * p1G( x / 2 )  );
}

float p1G( float x ){
	return x + ( x * x * x ) / 6;
}

void p2(){
	//what the literal fuck am i doing
}

void p5(){
	int size = 7500000;
	int* array = fillArray( size, true );
	uint64 start, end;
//	for( int i = 0; i < size; i++ ){
//		cout << array[i] << ", ";
//	}
//	cout << endl;
	Analize* linearAn = new Analize;
	int find = array[size-1];
	start = GetTimeMs64();
	cout << "found: " << ( linear( find, array, size, linearAn ) ? "t\n" : "f\n" );
	end = GetTimeMs64();
	cout << "linear find : " << find << endl;
	linearAn->print();
	long derp = ( end - start ); //because doing it a cout wont give me the time
	cout << "Total time = " << derp << "(ms) with n = " << size << endl;
	delete [] array;
	delete linearAn;
	
	cout<<"\n\n";
	
	array = fillArray( size, true );
//	for( int i = 0; i <= size - 1; i++ ){
//		cout << array[i] << ", ";
//	}
//	cout << endl;
	Analize* binaryAn = new Analize;
	start = GetTimeMs64();
	cout << "found: " << ( binary( find, array, binaryAn, 0, size - 1 ) ? "t\n" : "f\n" );
	end = GetTimeMs64();
	cout << "binary find : " << find << endl;
	binaryAn->print();
	derp = ( end - start ); //because doing it a cout wont give me the time
	cout << "Total time = " << derp << "(ms) with n = " << size << endl;
	delete [] array;
	delete binaryAn;
}

bool linear( int find, int* arr, int size, Analize* an ){
	an->ceq++; 
	for( int i = 0; i < size; i++ ){
		an->ccmp++; an->cinc++;
		an->ccmp++;
		if( arr[i] == find ){
			return true;
		}
	}
	return false;
}

bool binary( int find, int* arr, Analize* an, int start, int end ){
	an->ccmp++;
	if ( start > end ) return false; 
	an->ceq++;
	int mid = ( start + end ) / 2;
	
	if( find == arr[mid] ){
		an->ccmp++;
		return true;
	} else if( arr[ mid ] > find  ){
		an->ccmp+=2;
		binary( find, arr, an, start, mid - 1);
	} else {
		an->ccmp+=3;
		binary( find, arr, an, mid + 1, end );
	}
}

int *fillArray( int size ){
	return fillArray( size, false );
}

int *fillArray( int size, bool sorted ){
	try{
		int* arr = new int[size];
		for( int i = 0; i < size; i++ ){
			arr[i] = sorted ? i : rand() % size;
		}
		return arr;
	} catch( bad_alloc& ba ){
		 cerr << "bad_alloc caught: " << ba.what() << endl;
	}
}
