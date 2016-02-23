/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Table.h
 * Author: michael
 *
 * Created on February 17, 2016, 9:26 PM
 */

#ifndef TABLE_H
#define TABLE_H

#include "Array.h"
class Table {
public:
	Table( int columns, int rows );
	Table(const Table& orig);
	virtual ~Table();
	void print();
private:
	Array* arrays;
	int columns;
	int rows;

};

#endif /* TABLE_H */

