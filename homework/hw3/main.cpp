/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: michael
 *
 * Created on March 2, 2016, 1:59 PM
 */

#include <cstdlib>

using namespace std;

//User Libraries
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
using namespace std;

//User Libraries
#include "PlusTab.h"
#include "SimpleVector.h"

//Global Constants

//Function Prototype
template <class T>
void prntTab( const Table<T> & );
template <class T>
void prntRow(T *a,int perLine);

//Execution Begins Here!

int main( int argc, char** argv ) {
	//Initialize the random seed
   srand(static_cast<unsigned int>(time(0)));
   
   //simple vector
   SimpleVector<int> vec;
   vec.push_back( 1 );
   vec.push_back( 2 );
   vec.push_back( 3 );
   vec.push_back( 4 );
   vec.push_back( 5 );
   vec.pop_back();
   vec.push_back( 6 );
   
   for( int i = 0; i < vec.allocated(); i++ ){
	   cout << vec[i] << endl;
   }
   
   //Declare Variables
   int rows=3,cols=4;
   
   //Test out the Row with integers and floats
   RowAray<int> a(3);RowAray<float> b(4);
   cout<<"Test the Integer Row "<<endl;
   prntRow(&a,3);
   cout<<"Test the Float Row "<<endl;
   prntRow(&b,4);
   
   //Test out the Table with a float
   PlusTab<float> tab1(rows,cols);
   PlusTab<float> tab2(tab1);
   PlusTab<float> tab3=tab1+tab2;
   
   cout<<"Float Table 3 size is [row,col] = Table 1 + Table 2 ["
           <<rows<<","<<cols<<"]";
   prntTab(tab3);
   
   //Exit Stage Right
   return 0;
}

template<class T>
void prntRow(T *a,int perLine){
    cout<<fixed<<setprecision(1)<<showpoint<<endl;
    for(int i=0;i<a->getSize();i++){
        cout<<a->getData(i)<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}

template <class T>
void prntTab( const Table<T> &a ) {
	cout << endl;
	for ( int row = 0; row < a.getSzRow( ); row++ ) {
		for ( int col = 0; col < a.getSzCol( ); col++ ) {
			cout << fixed << showpoint << setprecision( 2 ) << a.getData( row, col ) << " ";
		}
		cout << endl;
	}
	cout << endl;
}

