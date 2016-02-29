/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RowAray.cpp
 * Author: michael
 * 
 * Created on February 23, 2016, 10:49 AM
 */

#include "RowAray.h"
#include <cstdlib>

RowAray::RowAray( int cols ) {
	this->size = cols;
	this->rowData = new int[size];
	for( int i = 0; i < cols; i++ ){
		rowData[i] = ( rand() % 90 ) + 10;
	}
}

RowAray::~RowAray() {
	delete [] rowData;
}

