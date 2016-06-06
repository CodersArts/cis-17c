/* 
 * File:   main.cpp
 * Author: michael
 *
 * Created on June 5, 2016, 5:37 PM
 */

#include <cstdlib>
//#include <vector>
#include <iostream>
//#include <iomanip>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstdio>

#include "Stack.h"
#include "sorting.h"

using namespace std;

void Menu();
int getN();
void def(int);
void p2();
float h(float, Stack<char> *);
float g(float, Stack<char> *);
void p4();
short* fill(int);

int main(int argc, char** argv) {
    srand(time(0));
    int inN;
    do {
        Menu();
        inN = getN();
        switch (inN) {
                //            case 1: p1();
                //                break;
            case 2: p2();
                break;
                //            case 3: p3();
                //                break;
            case 4: p4();
                break;
                //            case 5: p5();
                //                break;
                //            case 6: p6();
                //                break;
            default:;
        };
    } while (false && inN < 7);
    return 0;
    return 0;
}

void Menu() {
    cout << "Type 1 for problem 1" << endl;
    cout << "Type 2 for problem 2" << endl;
    cout << "Type 3 for problem 3" << endl;
    cout << "Type 4 for problem 4" << endl;
    cout << "Type 5 for problem 5" << endl;
    cout << "Type 6 for problem 6" << endl;
    cout << "Type 7 to exit \n" << endl;
}

int getN() {
    int inN;
    cin>>inN;
    cin.ignore();
    return inN;
}

//p2 fns

void p2() {
    Stack<char> *stack = new Stack<char>;
    printf("true value | our value\n");
    printf("rad\tcosh\tsinh\tsin val\t\tcos val\n");
    for (float rad = -1; rad <= 1.1; rad += .1) {
        float angRad = rad;
        float sval = h(angRad, stack);
        float cval = g(angRad, stack);
        //    cout << "Angle = " << angDeg << " sinh = " << sinh(angRad) << " our h = " << h(angRad, stack ) << endl;
        //    cout << "Angle = " << angDeg << " cosh = " << cosh(angRad) << " our g = " << g(angRad, stack ) << endl;
        int len = stack->getSize();
        int cc = 0, sc = 0;
        for (int i = 0; i < len; i++) {
            if (stack->pop() == 'c') {
                cc++;
            } else {
                sc++;
            }
        }
        printf("%3.2f\t%d\t%d\t%6.4f|%6.4f\t%6.4f|%6.4f\n", angRad, cc, sc, sinh(angRad), sval, cosh(angRad), cval);
    }
    //    printf( "%d\t%d", cc, sc );
    delete stack;
}

float h(float angR, Stack<char> *stack) { //sinh
    stack->push('s');
    float tol = 1e-6;
    if (angR>-tol && angR < tol)return angR + angR * angR * angR / 6;
    return 2 * h(angR / 2, stack) * g(angR / 2, stack);
}

float g(float angR, Stack<char> *stack) { //cosh
    stack->push('c');
    float tol = 1e-6;
    if (angR>-tol && angR < tol)return 1 + angR * angR / 2;
    float b = h(angR / 2, stack);
    return 1 + 2 * b*b;
}

//end p2

//p4 fns

void p4() {
    short *arr = fill( 10 );
    int size = 10;
    print( arr, 10 );
    mt::uint count = 0;
//    bubbleSort( arr, size, count );
    cout << "bubble operations: " << count << endl;
    
    count = 0;
//    quickSort( arr, size, count );
    cout << "quick operations: " << count << endl;
    
    count = 0;
//    mergeSort( arr, size, count );
    cout << "merge operations: " << count << endl;
    
    count = 0;
    heapSort( arr, size, count );
    cout << "heap operations: " << count << endl;
    print( arr, 10 );
    delete [] arr;
}

short* fill(int size) {
    short *t = new short[size];
    for (int i = 0; i < size; i++) {
        t[i] = rand() % size;
    }
    return t;
}
//end p4