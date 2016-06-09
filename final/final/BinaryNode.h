/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinaryNode.h
 * Author: michael
 *
 * Created on June 8, 2016, 12:53 PM
 */

#ifndef BINARYNODE_H
#define BINARYNODE_H

#include <cstdlib>

using namespace std;

template <class T>
class BinaryNode {
private:
	BinaryNode *left;
	BinaryNode *right;
	T data;
public:
	BinaryNode( T data ){
		this->data = data;
		left = NULL;
		right = NULL;
	}
	virtual ~BinaryNode(){
		delete left;
		delete right;
	}

    void SetData(T data) {
    	this->data = data;
    }

    T GetData() const {
    	return data;
    }

    void SetRight(BinaryNode* right) {
    	this->right = right;
    }

    BinaryNode* GetRight() const {
    	return right;
    }

    void SetLeft(BinaryNode* left) {
    	this->left = left;
    }

    BinaryNode* GetLeft() const {
    	return left;
    }
	

};

#endif /* BINARYNODE_H */

