/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on February 18, 2016, 8:54 AM
 * Purpose:  Dynamic Object Arrays
 */

//User Libraries
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

//User Libraries
#include "Table.h"

//Global Constants

//Function Prototype
void prntRow(RowAray *,int);
void prntTab(Table *);

//Execution Begins Here!
int main(int argc, char** argv) {
   //Initialize the random seed
   srand(static_cast<unsigned int>(time(0)));
   
   //Declare Variables
   int rows=15,cols=8,perLine=5;
    
   //Test out the RowAray
   RowAray row(rows);
    
   //Print the RowAray
   cout<<"The Row Array size = "<<row.getSize()
           <<" printed "<<perLine<<" per Line";
   prntRow(&row,perLine);
   
   //Test out the Table
   Table tab(rows,cols);
   
   //Print the table
   cout<<"The table size is [row,col] = ["<<rows<<","<<cols<<"]";
   prntTab(&tab);

   //Exit Stage Right
   return 0;
}

void prntRow(RowAray *a,int perLine){
    cout<<endl;
    for(int i=0;i<a->getSize();i++){
        cout<<a->getData(i)<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}

void prntTab(Table *a){
    cout<<endl;
    for(int row=0;row<a->getSzRow();row++){
        for(int col=0;col<a->getSzCol();col++){
            cout<<a->getData(row,col)<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}