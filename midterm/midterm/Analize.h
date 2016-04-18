/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Analize.h
 * Author: michael
 *
 * Created on April 17, 2016, 6:56 PM
 */

#ifndef ANALIZE_H
#define ANALIZE_H

#include <iostream>

using namespace std;

struct Analize{
	unsigned long ceq;
	unsigned long ccmp;
	unsigned long cinc;
	Analize() : ceq(0), ccmp(0), cinc(0) {};
	unsigned long total(){
		return ceq + ccmp + cinc;
	};
	void print(){ 
		cout << "C Equals: " << ceq << endl;
		cout << "C Compares: " << ccmp << endl;
		cout << "C Increments: " << cinc << endl;
		cout << "C Total: " << total() << endl;
	};
};

#endif /* ANALIZE_H */

