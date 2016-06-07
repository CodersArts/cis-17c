/* 
 * File:   sorting.h
 * Author: michael
 *
 * Created on June 5, 2016, 8:03 PM
 */

#ifndef SORTING_H
#define	SORTING_H

#include <iostream>

using namespace std;

namespace mt {
    typedef unsigned long long uint;
}

void bubbleSort(short *array, int size, mt::uint &count);
void quickSort(short *a, int size, mt::uint &count);
void pquickSort(short *a, int left, int right, mt::uint &count);
void mergeSort(short *a, int size, mt::uint &count);
void pmergeSort(short *a, short *temp, int left, int right, mt::uint &count);
void mergeCompare(short *a, short *temp, int left, int center, int right, mt::uint &count);
void heapSort(short * array, int size, mt::uint &count );
void pheapSort(short * array, int size, int &heapN, mt::uint &count );
void heapify(short * array, int size, int &heapN);
void maxHeap(short *array, int i, int &heapN);
void print(short *arr, int size);

void bubbleSort(short *array, int size, mt::uint &count) {
    bool swaped = false;
    int len = size - 1;
    count += 2;
    do {
        swaped = false;
        count += 2;
        for (int i = 0; i < len; i++) {
            count += 3;
            if (array[i] > array[i + 1]) {
                short temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                swaped = true;
                count += 4;
            }
        }
        len--;
        count++;
    } while (swaped);
}

void quickSort(short *a, int size, mt::uint &count) {
    pquickSort(a, 0, size - 1, count);
}

void pquickSort(short *a, int left, int right, mt::uint &count) {
    int leftI = left; // left scan index
    int rightI = right; //right scan index
    //		Random rand = new Random( );
    short pivot = a[left]; //using the leftmost as the pivot
	count+=3;
    while (leftI <= rightI) { //if we havent scanned the left side all the way through yet
		count++;
        while (a[leftI] < pivot) { //scan left side looking for index where larger than pivot
            leftI++;
			count+=2;
        }

        while (a[rightI] > pivot) { //scan right side looking for index where smaller than pivot
            rightI--;
			count+=2;
        }

		count++;
        if (leftI <= rightI) { //if the left index is smaller than we need to swap
            short temp = a[leftI];
            a[leftI] = a[rightI];
            a[rightI] = temp;
            leftI++;
            rightI--;
			count+=5;
        }
    }
    if (left < rightI) {
        pquickSort(a, left, rightI, count);
    }
    if (leftI < right) {
        pquickSort(a, leftI, right, count);
    }
	count+=2;
}

void mergeSort(short *a, int size, mt::uint &count) {
    short *temp = new short[ size ]; //make the temp array we can play wtih
	count++;
    pmergeSort(a, temp, 0, size - 1, count);
}

void pmergeSort(short *a, short *temp, int left, int right, mt::uint &count) {
	count++;
    if (left < right) { //if left is left than right to get down to 1 elem array
        int center = (left + right) / 2;
		count++;
        pmergeSort(a, temp, left, center, count);
        pmergeSort(a, temp, center + 1, right, count);
        mergeCompare(a, temp, left, center, right, count);
    }
}

void mergeCompare(short *a, short *temp, int left, int center, int right, mt::uint &count) {
    int leftBegin = left;
    int leftEnd = center;
    int rightBegin = center + 1;
    int rightEnd = right;
    int i = 0;
	count+=5;
	
    while ((leftBegin <= leftEnd) && (rightBegin <= rightEnd)) { //have we finished reading the half array
		count+=3;
        if (a[leftBegin] <= a[rightBegin]) {
            temp[i] = a[leftBegin];
            leftBegin++;
			count+=2;
        } else {
            temp[i] = a[rightBegin]; //take the the unsorted elem from right half
            rightBegin++;
			count+=2;
        }
        i++;
		count++;
    }

    while (leftBegin <= leftEnd) { //copy the missing elements from the a to temp
        temp[i] = a[leftBegin];
        i++;
        leftBegin++;
		count+=4;
    }

    while (rightBegin <= rightEnd) { //copy the missing elements from a to temp
        temp[i] = a[rightBegin];
        i++;
        rightBegin++;
		count+=4;
    }

    //copy from where left started to the
	count++;
    for (int j = left; j <= rightEnd; j++) {
        a[j] = temp[ j - left];
		count+=3;
    }
}

void heapSort(short * array, int size, mt::uint &count ){
    int heapN = 0;
    pheapSort( array, size, heapN, count );
}
void pheapSort(short * array, int size, int &heapN, mt::uint &count ) {
    //make the heap
    heapify(array, size, heapN);
    for (int i = heapN; i > 0; i--) {
        short temp = array[0];
        array[0] = array[i];
        array[i] = temp;
        heapN--;
        maxHeap(array, 0, heapN );
    }
}

void heapify(short *array, int size, int &heapN ) {
    heapN = size - 1;
    for (int i = heapN / 2; i >= 0; i--) {
        maxHeap(array, i, heapN );
    }
}

//swap the largest element in heap

void maxHeap(short * array, int i, int &heapN) {
    int left = 2 * i;
    int right = 2 * i + 1;
    int max = i;
    if (left <= heapN && array[left] > array[right]) {
        max = left;
    }
    if (right <= heapN && array[right] > array[max]) {
        max = right;
    }

    if (max != i) {
        short temp = array[i];
        array[i] = array[max];
        array[max] = temp;
        maxHeap(array, max, heapN );
    }
}

void print(short *arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ", ";
    }
    cout << endl;
}

#endif	/* SORTING_H */

