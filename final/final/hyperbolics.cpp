/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on June 2, 2016, 8:11 PM
 *


#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
using namespace std;

float h(float);
float g(float);
int main(int argc, char** argv) {
    //Testing out recursive trig functions
    float angDeg=45;
    float angRad=angDeg*atan(1)/45;
    cout<<"Angle = "<<angDeg<<" sinh = "<<sinh(angRad)<<
            " our h = "<<h(angRad)<<endl;
    cout<<"Angle = "<<angDeg<<" cosh = "<<cosh(angRad)<<
            " our g = "<<g(angRad)<<endl;
    //Exit stage right
    return 0;
}

float h(float angR){
    float tol=1e-6;
    if(angR>-tol&&angR<tol)return angR+angR*angR*angR/6;
    return 2*h(angR/2)*g(angR/2);
}
float g(float angR){
    float tol=1e-6;
    if(angR>-tol&&angR<tol)return 1+angR*angR/2;
    float b=h(angR/2);
    return 1+2*b*b;
}
*/