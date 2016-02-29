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
#include "RowAray.h"
#include <iostream>

Table::Table( int rows, int cols ) {
	this->szCol = cols;
	this->szRow = rows;
	this->columns = new RowAray*[rows];
	for( int i = 0; i < rows; i++ ){
		this->columns[i] = new RowAray( cols );
	}

}


Table::~Table() {
	delete [] this->columns;
}


int Table::getData(int row, int col ){
	if( row > szRow && col > szCol ) { return -1; }
	columns[row]->getData( col );
}

