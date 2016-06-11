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

struct Clerk {
	bool busy;
	int startTime;
	int served;
};

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

void p3( ) {
	queue<int> customers;
	vector< Clerk > clerks; //status, secs with customer

	for ( int i = 0; i < 3; i++ ) {
		Clerk clerk;
		clerk.busy = false;
		clerk.startTime = 0;
		clerk.served = 0;
		clerks.push_back( clerk );
	}
	int wait = 0;
	bool waiting = true;
	int runTime = 60 * 60;
	int clerktimes[] = {60, 120, 80};
	int totalCust = 0;
	cout << "how many hours do you want to run: ";
	cin >> runTime;
	runTime*= 60*60;

	//run the time
	for ( int sec = 0; sec <= runTime; sec += 5 ) { //increment by 5 seconds
		bool free = false;

		//check if clerks are done
		for ( int i = 0; i < clerks.size( ); i++ ) {
			int delta = ( i > 2 ? 60 : clerktimes[i] );
			if ( clerks[i].busy ) { //if clerk is busy
				if ( clerks[i].startTime + delta == sec ) {
					//if the time they started and the time it takes them to finish 1 person is == sec they are done
					clerks[i].busy = false;
					clerks[i].startTime = 0;
					clerks[i].served++;
					free = true;
				}
			}
		}

		if ( sec % 20 == 0 ) {
			customers.push( 1 ); //add customer every 20 secs
			totalCust++;
		}

		waiting = true;
		if ( customers.size( ) > 0 ) {
			//check for open clerk
			for ( int i = 0; i < clerks.size( ); i++ ) {
				if ( !( clerks[i].busy ) && customers.size( ) > 0 ) { //have to recheck size so dont add same guy to 3 tellers
					waiting = false;
					clerks[i].busy = true;
					clerks[i].startTime = sec; //set the time with the customer
					//derp remove customer
					customers.pop( );
				}
			}
			//if all clerks taken add time to wait for all the customers
			wait += ( waiting ? 5 * customers.size( ) : 0 );
		}
		
		//print status
		if( sec % 10 == 0 && false ){
			for ( int i = 0; i < clerks.size( ); ++i ) {
				cout << setw(6) << sec << setw( 3 ) << i+1 << setw( 3 ) << ( clerks[i].busy ? "T" : "F" ) << endl;
			}
		}
		//send more money we will send more stuff
		if ( customers.size( ) > 5 && !free ) {
			Clerk clerk;
			clerk.busy = false;
			clerk.startTime = 0;
			clerk.served = 0;
			clerks.push_back( clerk );
		}
		
		if( customers.size() == 0 && clerks.size() > 3 ){
			clerks.pop_back();
		}
	}

	cout << "the number of customers is " << totalCust << endl;
	for( int i = 0; i < clerks.size(); i++ ){
		cout << "clerk " << i + 1 << " served " << clerks[i].served << endl;
		
	}
	//cout << "wait time " << waiting << endl;
	cout << "average wait is " << ( wait / 60.0f ) / totalCust<< " minutes" << endl;
}
//end p3

//p4 fns

void p4( ) {
	int size = 100000;
	short *master = fill( size );
	short *arr = copyArr( master, size );
	long s, e;
	//	print( arr, size );
	mt::uint count = 0;
	s = time( 0 );
	bubbleSort( arr, size, count );
	e = time( 0 );
	cout << "bubblesort operations: " << count << endl;
	cout << "bubblesort time: " << (e-s) << endl;
	delete [] arr;
	arr = copyArr( master, size );

	count = 0;
	s = time( 0 );
	quickSort( arr, size, count );
	e = time( 0 );
	cout << "quicksort operations: " << count << endl;
	cout << "quicksort time: " << (e-s) << endl;
	delete [] arr;
	arr = copyArr( master, size );

	count = 0;
	s = time( 0 );
	mergeSort( arr, size, count );
	e = time( 0 );
	cout << "merge sort operations: " << count << endl;
	cout << "merge sort time: " << (e-s) << endl;
	delete [] arr;
	arr = copyArr( master, size );

	count = 0;
	s = time( 0 );
	markSort( arr, size, count );
	e = time( 0 );
	cout << "marksort operations: " << count << endl;
	cout << "marksort time: " << (e-s) << endl;
	delete [] arr;
	arr = copyArr( master, size );

	cout << "the only viable option for partial sorts is the selection sort\nsince it compares 1 element with the entire array\n";

	count = 0;
	int in = 10;
	cout << "input partial sort stop: ";
	cin >> in;
	s = time( 0 );
	partialSort( arr, size, in, count );
	e = time( 0 );
	cout << "partial sort operations: " << count << endl;
	cout << "partial sort time: " << (e-s) << endl;
//	print( arr, size );

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
	cout << "Tree contains\n";
	string str = "   ";

	for ( int i = 0; i < size; i++ ) {
		str[0] = (char) ( rand( ) % 26 + 65 );
		str[1] = (char) ( rand( ) % 26 + 65 );
		str[2] = (char) ( rand( ) % 26 + 65 );
		tree->insert( str );
	}
/*
	string in;
	cout << "\n\nEnter a string to find: ";
	getline( cin, in );
	tree->find( in );
	*/
	cout << "\nAt most it will take " << ceil( log( size ) / log( 2 ) ) +1<< " times to find";


	delete tree;
}
//end p5

//p6 fns

void p6( ) {
	Graph g(7);
    vector<string> names;
    names.push_back("SFO");
    names.push_back("ORD");
    names.push_back("JFK");
    names.push_back("DFW");
    names.push_back("MIA");
    names.push_back("LAX");
    names.push_back("BOS");
    g.addNames(names);
    g.addEdge("SFO","BOS",2704);
    g.addEdge("SFO","ORD",1846);
    g.addEdge("ORD","BOS",867);
    g.addEdge("ORD","JFK",740);
    g.addEdge("JFK","BOS",187);
    g.addEdge("SFO","DFW",1464);
    g.addEdge("DFW","ORD",802);
    g.addEdge("DFW","MIA",1121);
    g.addEdge("MIA","JFK",1090);
    g.addEdge("MIA","BOS",1258);
    g.addEdge("SFO","LAX",337);
    g.addEdge("LAX","DFW",1235);
    g.addEdge("LAX","MIA",2342);
    g.krusMST();
    g.shortestPath("BOS","LAX");
	
	
	/*
	Graph graph; 
	graph.addVertex( "a" );
	graph.addVertex( "b" );
	graph.addVertex( "c" );
	graph.addVertex( "d" );
	graph.addVertex( "e" );
	graph.addVertex( "f" );
	graph.addVertex( "g" );
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
	graph.addEdge( "f", 4, "g" );
	//*/
	//graph.addEdge( "a", 4, "b");
	//graph.addEdge( "a", 4, "c");
	//graph.addEdge( "a", 6, "e");
	//graph.addEdge( "a", 6, "d");
	//graph.addEdge( "b", 2, "c");
	//graph.addEdge( "c", 8, "d");
	//graph.addEdge( "d", 9, "e");
	/*
	graph.addVertex( "SFO" );
	graph.addVertex( "ORD" );
	graph.addVertex( "JFK" );
	graph.addVertex( "DFW" );
	graph.addVertex( "MIA" );
	graph.addVertex( "LAX" );
	graph.addVertex( "BOS" );

	graph.addEdge( "SFO", 2704, "BOS" );
	graph.addEdge( "SFO", 1846, "ORD" );
	graph.addEdge( "ORD", 867, "BOS" );
	graph.addEdge( "ORD", 740, "JFK" );
	graph.addEdge( "JFK", 187, "BOS" );
	graph.addEdge( "SFO", 1464, "DFW" );
	graph.addEdge( "DFW", 802, "ORD" );
	graph.addEdge( "DFW", 1121, "MIA" );
	graph.addEdge( "MIA", 1090, "JFK" );
	graph.addEdge( "MIA", 1258, "BOS" );
	graph.addEdge( "SFO", 337, "LAX" );
	graph.addEdge( "LAX", 1235, "DFW" );
	graph.addEdge( "LAX", 2342, "MIA" );
	//*/
//	graph.minSpan( );
//	graph.shortestPath();

}