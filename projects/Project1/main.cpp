/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: michael
 *
 * Created on April 26, 2016, 6:10 PM
 */



#include <cstdlib>
#include <iostream>
#include <cstdio>

#include "Game.h"

using namespace std;

void runGame();
void printRings();
int main( int argc, char** argv ) {
	runGame();
	return 0;
}

void runGame(){
	bool isRunning = true;
	//init the rings
	int inInt = 3;
//	printf( "Enter number of disks: " );
//	cin >> inInt;
	Game game( inInt );
	char inChar;
	printf( "Follow along mode? (y or n): ");
	cin.get( inChar );
	if( inChar == 'y' ){
		game.setGuided( true );
	}
	while( isRunning ){
		game.print();
		printf( "Enter the letters of the poles you want to move.\n");
		printf( "Source ( char ): " );
		cin.ignore();
		cin.get( inChar );
		printf( "Destination ( char ): " );
		char temp;
		cin.ignore();
		cin.get( temp );
		if( !game.move( inChar, temp ) ){
			//invalid move
			cout << "Can not move that disk\n";
			isRunning = false;
		}
//		cout << inChar << ", " << temp;	
	}
	game.solution();

}

void printRings(){

}


