//User Libraries
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
using namespace std;

void markSort( int *, int );

int main( int argc, char* argv[] ){
	srand( time( 0 ));
	int tStart = time(0);
	int i =1;
//	for( i = 1; i <= 4; i++ ){
		int s = 160000;
		int* array = new int[ s ];
		for( int i = 0; i < s; i++) {
			array[i] = rand(); //( rand() % 90 ) + 10;
		}
		markSort( array, s );
		delete [] array;
//	}
	int tEnd = time(0);
	cout<< "time : " << tEnd - tStart;
	return 0;
}
void markSort( int *a, int n ){
	//declare vars
//	int ceq = 0, clt = 0, cinc = 0, cswap = 0;
//	ceq++;
	for( int i =0; i < n-1; i++){
//		clt++; cinc++;
//		ceq++;
		for(int j = i+1; j < n; j++ ){
//			clt++; cinc++;
			if( a[i] > a[j] ){
//				cswap++;
				int temp = a[j];
				a[j] = a[i];
				a[i] = temp;
			}
//			clt++;
		}
	}
	
//	cout << "size of the sorted array = " << n <?
//	cout << n << "," << ceq << ","<< cinc<<","<<clt<<","<<cswap<<endl;;
}