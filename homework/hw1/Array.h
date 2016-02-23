/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Array.h
 * Author: michael
 *
 * Created on February 17, 2016, 9:08 PM
 */

#ifndef ARRAY_H
#define ARRAY_H

using namespace std;

class Array {
public:
	Array();
	Array(const Array& orig);
	virtual ~Array();
	void print();
	void fill( int size );
	int at( int i ){ return array[i]; }
private:
	int size;
	int* array;
};

#endif /* ARRAY_H */

