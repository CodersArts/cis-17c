/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Table.cpp
 * Author: michael
 * 
 * Created on March 2, 2016, 2:02 PM
 */

#include "Table.h"

Table::Table( unsigned int rows, unsigned int cols ) {
	this->szCol = cols;
	this->szRow = rows;
	this->columns = new RowAray*[rows];
	for( int i = 0; i < rows; i++ ){
		this->columns[i] = new RowAray( cols );
	}
}

Table::Table( const Table& orig ) {
	this->szCol = orig.getSzCol();
	this->szRow = orig.getSzRow();
	this->columns = new RowAray*[szRow];
	for( int i = 0; i < szRow; i++ ){
		this->columns[i] = new RowAray( szCol );
	}
	
	for( int i = 0; i < szRow; i++ ){
		for( int j = 0; j < szCol; j++ ){
			setData( i, j, orig.getData( i, j ) );
		}
	}
}

Table::~Table( ) {
	delete [] columns;
}

int Table::getData(int row, int col ) const {
	if( row > szRow && col > szCol ) { return -1; }
	columns[row]->getData( col );
}

void Table::setData(int i, int j, int data ){
	this->columns[i]->setData( j, data );
}
