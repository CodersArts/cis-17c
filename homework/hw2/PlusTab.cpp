/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PlusTab.cpp
 * Author: michael
 * 
 * Created on March 2, 2016, 2:03 PM
 */

#include "PlusTab.h"

PlusTab PlusTab::operator +(const PlusTab& right){
	PlusTab res( this->szRow, this->szCol );
	for( int i = 0; i < this->szRow; i++ ){
		for( int j = 0; j < this->szCol; j++ ){
			res.setData( i, j, ( this->getData( i, j ) + right.getData( i, j ) ) );
		}
	}
	return res;
}

