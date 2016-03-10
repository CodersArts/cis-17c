/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RowAray.h
 * Author: michael
 *
 * Created on March 2, 2016, 2:01 PM
 */

#ifndef ROWARAY_H
#define ROWARAY_H

#include "AbsRow.h"

template <class T>
class RowAray: public AbsRow<T>{
    public:
        RowAray(unsigned int);
        virtual ~RowAray();
        int getSize()const{ return this->size;}
        T getData(int i)const{
            if( i >= 0 && i < this->size ) return this->rowData[i];
            else return 0;
		}
        void setData( int,T );
};

template <class T>
RowAray<T>::RowAray( unsigned int cols ) {
	this->size = cols;
	this->rowData = new T[this->size];
	for( int j = 0; j < cols; j++ ){
			this->setData( j, ( rand() % 90 ) + 10);
		}
}

template <class T>
void RowAray<T>::setData( int index, T data ){
	this->rowData[ index ] = data;
}

template <class T>
RowAray<T>::~RowAray( ) {
	delete [] this->rowData;
}



#endif /* ROWARAY_H */

