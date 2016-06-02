/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: michael
 *
 * Created on May 24, 2016, 5:15 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>

#include "ExpressionTree.h"
#include "PostFix.h"
#include "HashTable.h"


using namespace std;

int main( int argc, char** argv ) {
	ExpressionTree tree;
	tree.create( "2+2" );
	tree.evaluate();
	tree.create( "2 2 +", true );
	tree.evaluate();
//	tree.inOrder( );
//	tree.postOrder( );
//	tree.preOrder( );
//	tree.evaluate( );

//	cout << convert( "2+2" ) << endl;;
//	cout << convert( "3 * ( 4 + 5 )" )<< endl;;
//	cout << convert( "2 * ( ( 3 + 5 ) * ( 3 + 2 ) )" )<< endl;;
//	cout << convert( "6 * (3+(7*8)*(5+2))" )<< endl;

//	HashTable test( 100000 ); // .1% error for 100 elements
//	test.put( "hello", "test" );
//	cout << test.exists( "hello" );

	/*TODO
	 create hash table 
	 store the completed solutions in the hash table
	 check the hash table before making tree
	 */

	return 0;
}

