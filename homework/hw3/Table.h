/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Table.h
 * Author: michael
 *
 * Created on March 2, 2016, 2:02 PM
 */

#ifndef TABLE_H
#define TABLE_H

#include "AbsTabl.h"

template <class T>
class Table : public AbsTabl<T>{
    public:
        Table(unsigned int,unsigned int);
        Table(const Table &);
        virtual ~Table();
        int getSzRow()const { return this->szRow; }
        int getSzCol()const { return this->szCol; }
        T getData( int, int ) const;
        void setData( int, int, T );
};

template <class T>
Table<T>::Table( unsigned int rows, unsigned int cols ) {
	this->szCol = cols;
	this->szRow = rows;
	this->columns = new RowAray<T>*[rows];
	for( int i = 0; i < rows; i++ ){
		this->columns[i] = new RowAray<T>( cols );
	}
}

template <class T>
Table<T>::Table( const Table& orig ) {
	this->szCol = orig.getSzCol();
	this->szRow = orig.getSzRow();
	this->columns = new RowAray<T>*[this->szRow];
	for( int i = 0; i < this->szRow; i++ ){
		this->columns[i] = new RowAray<T>( this->szCol );
	}
	
	for( int i = 0; i < this->szRow; i++ ){
		for( int j = 0; j < this->szCol; j++ ){
			setData( i, j, orig.getData( i, j ) );
		}
	}
}

template <class T>
Table<T>::~Table( ) {
	delete [] this->columns;
}

template <class T>
T Table<T>::getData(int row, int col ) const {
	if( row > this->szRow && col > this->szCol ) { return -1; }
	return this->columns[row]->getData( col );
}

template <class T>
void Table<T>::setData(int i, int j, T data ){
	this->columns[i]->setData( j, data );
}

#endif /* TABLE_H */

