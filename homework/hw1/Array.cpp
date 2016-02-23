/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Array.cpp
 * Author: michael
 * 
 * Created on February 17, 2016, 9:08 PM
 */

#include "Array.h"
#include <cmath>
#include <stdlib.h>
#include <iostream>

using namespace std;

Array::Array() {
	this->size = 0;
//	fill();
}

Array::Array( const Array& orig ) {
}

Array::~Array() {
	delete [] array;
}

void Array::fill( int size ){
	this->size = size;
	this->array = new int[ size ];
	for( int i = 0; i < size; i++ ){
		array[i] = ( rand() % 90 ) + 10;
	}
}

void Array::print(){
	for( int i = 0; i < size; i++ ){
		cout << array[i];
		if( i != size - 1){
			cout << " ";
		}
	}
}



