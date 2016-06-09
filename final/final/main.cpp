/* 
 * File:   main.cpp
 * Author: michael
 *
 * Created on June 5, 2016, 5:37 PM
 */

#include <cstdlib>
//#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <string>
#include <sstream>
#include <map>
#include <queue>

#include "Stack.h"
#include "sorting.h"
#include "BinaryTree.h"
#include "Graph.h"

using namespace std;

void Menu( );
int getN( );
void def( int );
void p1( );
int pHash( string );
void p2( );
float h( float, Stack<char> * );
float g( float, Stack<char> * );
void p3( );
void p4( );
void p5( );
void p6( );
short* fill( int );
short* copyArr( short *, int );

int main( int argc, char** argv ) {
	srand( time( 0 ) );
	int inN;
	do {
		Menu( );
		inN = getN( );
		switch ( inN ) {
			case 1: p1( );
				break;
			case 2: p2( );
				break;
			case 3: p3( );
               break;
			case 4: p4( );
				break;
			case 5: p5( );
				break;
			case 6: p6( );
				break;
			default:;
		};
	} while ( inN < 7 );
	return 0;
	return 0;
}

void Menu( ) {
	cout << "\nType 1 for problem 1" << endl;
	cout << "Type 2 for problem 2" << endl;
	cout << "Type 3 for problem 3" << endl;
	cout << "Type 4 for problem 4" << endl;
	cout << "Type 5 for problem 5" << endl;
	cout << "Type 6 for problem 6" << endl;
	cout << "Type 7 to exit \n" << endl;
}

int getN( ) {
	int inN;
	cin>>inN;
	cin.ignore( );
	return inN;
}

//p1 fns

void p1( ) {
	int size = 500;
	string str = "   ";
	fstream file;
	file.open( "p1.dat", ios::out );
	map<int, int> stats;
	int bitvec[size];
	for ( int i = 0; i < size; i++ ) {
		bitvec[i] = 0;
	}

	for ( int i = 0; i < size; i++ ) {
		str[0] = (char) ( rand( ) % 26 + 65 );
		str[1] = (char) ( rand( ) % 26 + 65 );
		str[2] = (char) ( rand( ) % 26 + 65 );
		int hash = pHash( str );
		file << str << " " << hash << endl;
		bitvec[hash % size]++;
	}

	file << "collision array\n";
	for ( int i = 0; i < size; i++ ) {
		if ( stats.count( bitvec[i] ) <= 0 ) {
			stats[ bitvec[i] ] = 1;
		} else {
			stats[ bitvec[i] ]++;
		}
		file << setw( 2 ) << bitvec[i] << " ";
		if ( ( i + 1 ) % 25 == 0 ) {
			file << endl;
		}
	}

	int total = 0;
	for ( map<int, int>::iterator it = stats.begin( ); it != stats.end( ); it++ ) {
		if ( it->first != 0 ) {
			total += it->second;
		}
		cout << it->first << " collisions occurred #" << it->second << endl;
		file << it->first << " collisions occurred #" << it->second << endl;
	}

	cout << "Max number of collisions is: " << ( --stats.end( ) )->first << endl;
	file << "Max number of collisions is: " << ( --stats.end( ) )->first << endl;
	cout << "Total collisions: " << total << endl;
	file << "Total collisions: " << total << endl;
	float avg = (float) size / total;
	cout << "average search: " << avg << endl;
	file << "average search: " << avg << endl;
	file.close( );

}

/*
 * 2=abc, 3=def, 4=ghi, 5=jkl, 6=mno, 7=pqrs, 8=tuv, 9=wxyz
 */
int pHash( string str ) {
	stringstream ss;
	for ( int i = 0; i < 3; i++ ) {
		int j = 0;
		char c = str[i];
		if ( c >= 65 && c <= 67 ) {
			j = 2;
		} else if ( c >= 68 && c <= 70 ) {
			j = 3;
		} else if ( c >= 71 && c <= 73 ) {
			j = 4;
		} else if ( c >= 74 && c <= 76 ) {
			j = 5;
		} else if ( c >= 77 && c <= 79 ) {
			j = 6;
		} else if ( c >= 80 && c <= 83 ) {
			j = 7;
		} else if ( c >= 84 && c <= 86 ) {
			j = 8;
		} else if ( c >= 85 && c <= 90 ) {
			j = 9;
		}
		ss << "" << j;
	}
	return atoi( ss.str( ).c_str( ) );

}
//end p1

//p2 fns

void p2( ) {
	Stack<char> *stack = new Stack<char>;
	printf( "true value | our value\n" );
	printf( "rad\tcosh\tsinh\tsin val\t\tcos val\n" );
	for ( float rad = -1; rad <= 1.1; rad += .1 ) {
		float angRad = rad;
		float sval = h( angRad, stack );
		float cval = g( angRad, stack );
		//    cout << "Angle = " << angDeg << " sinh = " << sinh(angRad) << " our h = " << h(angRad, stack ) << endl;
		//    cout << "Angle = " << angDeg << " cosh = " << cosh(angRad) << " our g = " << g(angRad, stack ) << endl;
		int len = stack->getSize( );
		int cc = 0, sc = 0;
		for ( int i = 0; i < len; i++ ) {
			if ( stack->pop( ) == 'c' ) {
				cc++;
			} else {
				sc++;
			}
		}
		printf( "%3.2f\t%d\t%d\t%6.4f|%6.4f\t%6.4f|%6.4f\n", angRad, cc, sc, sinh( angRad ), sval, cosh( angRad ), cval );
	}
	//    printf( "%d\t%d", cc, sc );
	delete stack;
}

float h( float angR, Stack<char> *stack ) { //sinh
	stack->push( 's' );
	float tol = 1e-6;
	if ( angR>-tol && angR < tol )return angR + angR * angR * angR / 6;
	return 2 * h( angR / 2, stack ) * g( angR / 2, stack );
}

float g( float angR, Stack<char> *stack ) { //cosh
	stack->push( 'c' );
	float tol = 1e-6;
	if ( angR>-tol && angR < tol )return 1 + angR * angR / 2;
	float b = h( angR / 2, stack );
	return 1 + 2 * b*b;
}

//end p2

//p3 fns

void p3(){
//	queue<int>
}
//end p3

//p4 fns

void p4( ) {
	int size = 1000;
	short *master = fill( size );
	short *arr = copyArr( master, size );
	//	print( arr, size );
	mt::uint count = 0;
	bubbleSort( arr, size, count );
	cout << "bubblesort operations: " << count << endl;
	delete [] arr;
	arr = copyArr( master, size );

	count = 0;
	quickSort( arr, size, count );
	cout << "quicksort operations: " << count << endl;
	delete [] arr;
	arr = copyArr( master, size );

	count = 0;
	mergeSort( arr, size, count );
	cout << "merge sort operations: " << count << endl;
	delete [] arr;
	arr = copyArr( master, size );

	count = 0;
	markSort( arr, size, count );
	cout << "marksort operations: " << count << endl;
	delete [] arr;
	arr = copyArr( master, size );

	cout << "the only viable option for partial sorts is the selection sort\nsince it compares 1 element with the entire array ";

	count = 0;
	partialSort( arr, size, size * 0.10, count );
	cout << "partial sort operations: " << count << endl;
	print( arr, size );

	delete [] arr;
	delete [] master;
}

short* fill( int size ) {
	short *t = new short[size];
	for ( int i = 0; i < size; i++ ) {
		t[i] = rand( ) % size;
	}
	return t;
}

short* copyArr( short *arr, int size ) {
	short *temp = new short[size];
	for ( int i = 0; i < size; i++ ) {
		temp[i] = arr[i];
	}
	return temp;
}
//end p4


//p5 fns

void p5( ) {
	int size = 500;
	BinaryTree<string> *tree = new BinaryTree<string>;
	string str = "   ";

	for ( int i = 0; i < size; i++ ) {
		str[0] = (char) ( rand( ) % 26 + 65 );
		str[1] = (char) ( rand( ) % 26 + 65 );
		str[2] = (char) ( rand( ) % 26 + 65 );
		tree->insert( str );
	}
	
	string in;
	getline( cin, in );
	tree->find( in );


	delete tree;
}
//end p5

//p6 fns

void p6( ) {
	Graph graph;/*
	graph.addVertex( "a" );
	graph.addVertex( "b" );
	graph.addVertex( "c" );
	graph.addVertex( "d" );
	graph.addVertex( "e" );
	graph.addVertex( "f" );
	graph.addVertex( "f" );
	graph.addEdge( "a", 4, "b" );
	graph.addEdge( "a", 7, "d" );
	graph.addEdge( "a", 3, "c" );
	graph.addEdge( "b", 1, "d" );
	graph.addEdge( "b", 4, "f" );
	graph.addEdge( "c", 3, "d" );
	graph.addEdge( "c", 5, "e" );
	graph.addEdge( "d", 2, "f" );
	graph.addEdge( "d", 2, "e" );
	graph.addEdge( "d", 7, "g" );
	graph.addEdge( "e", 2, "g" );
	graph.addEdge( "f", 4, "g" );*/
	//graph.addEdge( "a", 4, "b");
	//graph.addEdge( "a", 4, "c");
	//graph.addEdge( "a", 6, "e");
	//graph.addEdge( "a", 6, "d");
	//graph.addEdge( "b", 2, "c");
	//graph.addEdge( "c", 8, "d");
	//graph.addEdge( "d", 9, "e");
	//*
	graph.addVertex("SFO");
	graph.addVertex("ORD");
	graph.addVertex("JFK");
	graph.addVertex("DFW");
	graph.addVertex("MIA");
	graph.addVertex("LAX");
	graph.addVertex("BOS");
	
	graph.addEdge( "SFO", 2704, "BOS" );
	graph.addEdge( "SFO", 1846, "ORD" );
	graph.addEdge( "ORD",  867, "BOS" );
	graph.addEdge( "ORD",  740, "JFK" );
	graph.addEdge( "JFK",  187, "BOS" );
	graph.addEdge( "SFO", 1464, "DFW" );
	graph.addEdge( "DFW",  802, "ORD" );
	graph.addEdge( "DFW", 1121, "MIA" );
	graph.addEdge( "MIA", 1090, "JFK" );
	graph.addEdge( "MIA", 1258, "BOS" );
	graph.addEdge( "SFO",  337, "LAX" );
	graph.addEdge( "LAX", 1235, "DFW" );
	graph.addEdge( "LAX", 2342, "MIA" );
	//*/
	graph.minSpan( );

}