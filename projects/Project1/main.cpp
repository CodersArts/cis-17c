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
#include <string.h>
#include<limits>

#include "Game.h"

using namespace std;

void runGame( Game* game );
void won( Game* );
void clear();

int main( int argc, char** argv ) {
	cout << "\033[41m" << "~~ For best results run in external terminal ~~" << "\033[49m \n\n";
	int inInt = 2;
	printf( "Enter number of disks: " );
	cin >> inInt;
	cin.ignore();
	Game *game = new Game( inInt );
	runGame( game );
	delete game;
	return 0;
}

void runGame( Game* game ){
	bool isRunning = true;
	char inChar;
	string inStr;
	do {
		printf( "Follow along mode? (y or n): ");
		getline( cin, inStr );
	} while( inStr.compare( "y" ) != 0 && inStr.compare( "n" ) != 0 );
	if( inStr.compare( "y" ) == 0 ){
		game->setGuided( true );
	}
	clear();
	while( isRunning ){
		game->print();
		cout << endl;
		if( game->isGuided() ){
			pair<char, char> move = game->pop();
			cout << "Perfect move is " << move.first << " to " << move.second << endl;
		}
		printf( "Enter the letters of the poles you want to move.\n");
		printf( "Source ( char ): " );
		getline( cin, inStr );
//		cin.get( inChar );
		printf( "Destination ( char ): " );
		string temp;
//		cin.ignore();
		getline( cin, temp );
//		cin.get( temp );
		if( !game->move( inStr[0], temp[0] ) ){
			//invalid move
			cout << "Can not move that disk\n";
			if( temp[0] == 'z' ){
				isRunning = false;
			}
		} 
		clear();
		//check if we won
		if( game->won() ){
			game->print();
			cout << "\nYou won!\nIn " << game->getMoves() << " moves.\n";
			isRunning = false;
			if( !game->isGuided() ){
				game->save();
				game->displayScores();				
			}
			won( game );
		}
		
//		cout << inChar << ", " << temp;	
	}
	//game->solution();

}

void won( Game *game ) {
	char inChar;
	do {
		cout << "play again? (y or n): ";
		cin >> inChar;
	} while ( inChar != 'n' && inChar != 'y' );
	if ( inChar == 'y' ) {
		game->reset( );
		system( "cls" );
		cin.ignore( );
		runGame( game );
	}
}

void clear(){
	//clear the terminal

	#ifdef _WIN32
//	system( "CLS" ); //this breaks stuff in netbeans
	for( int i = 0; i < 50; i++ ){
		cout <<endl;
	}
	#else
	system( "clear" );
	#endif

	
}

/*
 for the cis18c final there is
 * 6 true/false questions
 * 8 short answer
 * 6 multiple choice
 * 
 * for chapter 19-22 he only put hashing in the final
 * 
 * you can use the notes the night of the review on the final
 * if you want to want to add something to the notes after the review you can
 * each page of you will be in order by chapter
 */


