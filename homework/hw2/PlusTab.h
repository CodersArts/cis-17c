/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PlusTab.h
 * Author: michael
 *
 * Created on March 2, 2016, 2:03 PM
 */

#ifndef PLUSTAB_H
#define PLUSTAB_H

#include "Table.h"

class PlusTab : public Table {
public:

	PlusTab(unsigned int r, unsigned int c) : Table(r, c) {};
	PlusTab operator+(const PlusTab &);
};
#endif /* PLUSTAB_H */

