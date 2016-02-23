/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Table.cpp
 * Author: michael
 * 
 * Created on February 17, 2016, 9:26 PM
 */

#include "Table.h"
#include <iostream>

Table::Table( int columns, int rows ) {
	arrays = new Array[rows];
	for( int i = 0; i < rows; i++ ){
		arrays[i].fill( columns );
	}
	this->columns = columns;
	this->rows = rows;
}

Table::Table(const Table& orig) {
}

Table::~Table() {
	delete [] arrays;
}

void Table::print(){
	for( int i = 0; i < rows; i++ ){
		arrays[i].print();
		cout << endl;
	}
}



