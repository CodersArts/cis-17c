/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PostFix.h
 * Author: michael
 *
 * Created on May 31, 2016, 5:13 PM
 */

#ifndef POSTFIX_H
#define POSTFIX_H



#include "Tokenizer.h"

using namespace std;

bool isOperator(char test, bool parenthesise);

bool isOperator(char test);
bool isOperator(string test);

bool isNumber(char test);

int pemdas(char op);

bool isSolvable(string infix);

string convert(string infix);
/*
public static String convertToPostFix( String infix ) {
		if ( !isSolvable( infix ) ) {
			IO.printlnErr( infix + " Is Not Solvable!" );
			return "";
		}

		//remove all the spaces
		infix = infix.replaceAll( " ", "" );

		Tokenizer token = new Tokenizer( infix ); //create token
		StringBuilder postfix = new StringBuilder();
		Stack<Character> ops = new Stack<>();
		CharPattern nums = new CharPattern( "[0-9\\.]" );//DONE allow decimals


		for ( int i = 0; i < infix.length(); i++ ) {
			if ( isOperator( token.get() ) ) {
				if ( ops.size() == 0 ) { //if empty stack just add it
					if ( token.get() == '-' ) {
						if ( token.behind() == 0 ) {//it is the first char so its negative
							postfix.append( token.get() );
							token.next();
							continue;
						} else if ( isOperator( token.behind(), false ) ) {
							postfix.append( token.get() );
							token.next();
							continue;
						} else{
							ops.push( token.get() );
						}
					} else if ( token.get() == '!' ) { //if there is a factorial put it in now
						postfix.append( token.get() ).append( " " );
						token.next();
						continue;
					} else
						ops.push( token.get() );
				} else if ( token.get() == ')' ) { //if we are closing the parenthesise
					//pop off whatever is there until we hit the open parenthesise
					while ( ops.size() > 0 && ops.peek() != '(' ) {
						postfix.append( ops.pop() ).append( " " );
					}
					//remove the opening paren
					ops.pop();
				} else {
					if ( token.get() == '-' ) {
						if ( token.behind() == 0 ) {//it is the first char so its negative
							postfix.append( token.get() );
							token.next();
							continue;
						} else if ( isOperator( token.behind(), false ) ) {
							postfix.append( token.get() );
							token.next();
							continue;
						}
					}
					if ( token.get() == '!' ) { //if there is a factorial put it in now
						postfix.append( token.get() ).append( " " );
						token.next();
						continue;
					}

					if ( ( token.get() == '(' && ops.peek().equals( '(' ) ) ||
							( pemdas( ops.peek() ) >= pemdas( token.get() ) ) ) { //if not an open paren and the stack is of higher or equal order pop into final
						while ( ops.size() > 0 && !ops.peek().equals( '(' ) && pemdas( ops.peek() ) >= pemdas( token.get() ) ) {
							postfix.append( ops.pop() ).append( " " );
						}
						ops.push( token.get() );
					} else {
						ops.push( token.get() );
					}
				}
			} else if ( nums.matches( token.get() ) ) {
				//DONE look for whole numbers, decimals, negatives
				if ( nums.matches( token.forward() ) || token.forward() == '!' ) {
					//if the next char is a number or factorial put it in without space
					postfix.append( token.get() );
				} else {
					postfix.append( token.get() ).append( " " );
				}
			}

			token.next();
		}

		//pop whatever is left in the stack off be atleast 1
		while ( ops.size() > 0 ) {
			postfix.append( ops.pop() ).append( " " );
		}

		return ( postfix.toString() );
	}
 */
#endif /* POSTFIX_H */

