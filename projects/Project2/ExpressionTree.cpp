/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ExpressionTree.cpp
 * Author: michael
 * 
 * Created on May 31, 2016, 4:48 PM
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include "ExpressionTree.h"
#include "HashTable.h"
#include <stack>
#include "PostFix.h"

using namespace std;

//ExpressionTree::ExpressionTree( ) {
////	hashmap = HashTable( 100000 );
//	root = NULL;
//}

ExpressionTree::~ExpressionTree( ) {
	helper( root );
}

void ExpressionTree::helper( ExpressionNode* node ) {
	if ( !node ) {
		return;
	} else {
		helper( node->getLeft( ) );
		helper( node->getRight( ) );
		delete node;
	}
}

void ExpressionTree::create( string postfix ) {
	create( postfix, false );
}

void ExpressionTree::create( string postfix, bool isPostfix ) {
	if ( isPostfix ) {
		cout << "create: " << postfix << endl;
		equation = postfix;
		//if exists and has collisions or if it doesn't exist
		if ( hashmap.hasCollision( postfix ) || !hashmap.exists( postfix ) ) {
			stack<ExpressionNode *> tempStack;
			ExpressionNode *eq, *op1, *op2;
			stringstream ss( postfix );
			string current;
			while ( ss >> current ) {
				//if number push to stack
				if ( !isOperator( current[0] ) ) {
					eq = new ExpressionNode( current );
					tempStack.push( eq );
				} else {
					eq = new ExpressionNode( current );
					//pop numbers
					op1 = tempStack.top( );
					//				cout << "op1: " << op1->getData() << endl;
					tempStack.pop( );
					op2 = tempStack.top( );
					//				cout << "op2: " << op2->getData() << endl;
					tempStack.pop( );

					eq->setRight( op1 );
					eq->setLeft( op2 );
					//push equation to the stack
					tempStack.push( eq );
				}
			}

			root = tempStack.top( );
			tempStack.pop( );
		}
	} else {
		create( convert( postfix ), true );
	}
}

void ExpressionTree::rInOrder( ExpressionNode *node ) {
	if ( node ) {
		rInOrder( node->getLeft( ) );
		cout << node->getData( ) << " ";
		rInOrder( node->getRight( ) );
	}
}

void ExpressionTree::inOrder( ) {
	rInOrder( root );
	cout << endl;
}

void ExpressionTree::rPostOrder( ExpressionNode *node ) {
	if ( node ) {
		rPostOrder( node->getLeft( ) );
		rPostOrder( node->getRight( ) );
		cout << node->getData( ) << " ";
	}
}

void ExpressionTree::postOrder( ) {
	rPostOrder( root );
	cout << endl;
}

void ExpressionTree::rPreOrder( ExpressionNode *node ) {
	if ( node ) {
		cout << node->getData( ) << " ";
		rPreOrder( node->getLeft( ) );
		rPreOrder( node->getRight( ) );
	}
}

void ExpressionTree::preOrder( ) {
	rPreOrder( root );
	cout << endl;
}

void ExpressionTree::evaluate( ) {
	if ( !equation.empty( ) ) {
		if ( hashmap.exists( equation ) && !hashmap.hasCollision( equation ) ) {
			cout << hashmap.at( equation );
		} else if ( root ) {
			string val = recursionEval( root );
			cout << val << endl;

			//store in a hash map
			hashmap.put( equation, val );
		}
	}

}

string ExpressionTree::recursionEval( ExpressionNode* node ) {
	if ( !isOperator( node->getData( )[0] ) ) { //if it has a value that is not an operator
		return node->getData( );
	} else {
		string left = recursionEval( node->getLeft( ) );
		string right = recursionEval( node->getRight( ) );

		float op1 = atof( left.c_str( ) );
		float op2 = atof( right.c_str( ) );
		float result;

		if ( node->getData( )[0] == '+' ) {
			result = op1 + op2;
		} else if ( node->getData( )[0] == '-' ) {
			result = op1 - op2;
		} else if ( node->getData( )[0] == '*' ) {
			result = op1 * op2;
		} else if ( node->getData( )[0] == '/' ) {
			result = op1 / op2;
		} else if ( node->getData( )[0] == '-' ) {
			result = pow( op1, op2 );
		}

		stringstream ss;
		ss << result;

		node->setData( ss.str( ) );
		return ss.str( );
	}
}
