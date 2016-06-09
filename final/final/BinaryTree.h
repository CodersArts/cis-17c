/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinaryTree.h
 * Author: michael
 *
 * Created on June 8, 2016, 12:52 PM
 */

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <cstdlib>
#include <iostream>

#include "BinaryNode.h"

using namespace std;

template <class T>
class BinaryTree {
private:
	BinaryNode<T> *root;
	void rInOrder( BinaryNode<T> *node ){
		if( node ){
			rInOrder( node->GetLeft() );
			cout << node->GetData() << ", ";
			rInOrder( node->GetRight() );
		}
	}
	void rPostOrder( BinaryNode<T> *node ){
		if( node ){
			rPostOrder( node->GetLeft() );
			rPostOrder( node->GetRight() );
			cout << node->GetData() << ", ";
		}
	}
	void rPreOrder( BinaryNode<T> *node ){
		if( node ){
			cout << node->GetData() << ", ";
			rPreOrder( node->GetLeft() );
			rPreOrder( node->GetRight() );
		}
	}
	void insertNode( T data, BinaryNode<T> *node ){
		if( data <= node->GetData() ){
			if( node->GetLeft() ){
				insertNode( data, node->GetLeft() );
			} else {
				cout << node->GetData() << " - L" << endl;
				BinaryNode<T> *tempNode = new BinaryNode<T>( data );
				node->SetLeft( tempNode );
			}
		} else {
			if( node->GetRight() ){
				insertNode( data, node->GetRight() );
			} else {
				BinaryNode<T> *tempNode = new BinaryNode<T>( data );
				cout << node->GetData() << " - R" << endl;
				node->SetRight( tempNode );
			}
		}
		
	}
	
	bool rFind( T data, BinaryNode<T> *node, int &count  ){
		if( node ){
			if( data < node->GetData() ){
				return rFind( data, node->GetLeft(), ++count );
			} else if( data > node->GetData() ){
				return rFind( data, node->GetRight(), ++count );
			} else {
				cout << data << " == " << node->GetData() << endl;
				return true;
			}
		}
		return false;
	}
public:
	BinaryTree(){
		root = NULL;
	}
	virtual ~BinaryTree(){
		delete root;
	}
	void inOrder(){
		rInOrder( root );
		cout << endl;
	}
	void postOrder(){
		rPostOrder( root );
		cout << endl;
	}
	void preOrder(){
		rPreOrder( root );
		cout << endl;
	}
	
	void insert( T data ){
		if( root ){
			insertNode( data, root );
		} else {
			BinaryNode<T> *tempNode = new BinaryNode<T>( data );
			root = tempNode;
		}
	}
	
	void find( T data ){
		int count = 0;
		if( rFind( data, root, count ) ){
			cout << "found after " << count << " times\n";
		} else {
			cout << "searched " << count << " times without finding";
		}
	}
};

#endif /* BINARYTREE_H */

