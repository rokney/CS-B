/* 
 * File:   main.cpp
 * Author: aotian
 *
 * Simple implementation of the insertion sort, quick sort, selection sort.
 */

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

const int RANDOM_VALUE = 10;
using namespace std;

void quickSort(vector<int> &array, int begin, int end) {
    int left = begin;
    int right = end;
    int base = array[(begin + end) / 2];
    while (left <= right) {
        while (array[left] < base) {
            left++;
        }
        while (array[right] > base) {
            right--;
        }
        if (left <= right) {
            swap(array[left++], array[right--]);
        }
        if (begin < right) {
            quickSort(array, begin, right);
        }
        if (end > left) {
            quickSort(array, left, end);
        }
    }
}

void selectionSort(vector<int> &array) {
    for (int i = 0; i < array.size() - 1; i++) {
        int min = array[i];
        for (int j = i + 1; j < array.size(); j++) {
            if (array[j] < min) {
                min = array[j];
                swap(array[i], array[j]);
            }

        }
    }
}

void insertionSort(vector<int> &array) {
    for (int i = 0; i < array.size(); i++) {
        for (int j = i; j > 0 && array[j - 1] > array[j]; j--) {
            swap(array[j - 1], array[j]);
        }
    }
}

void fillArrayAndPrint(vector<int> &array) {
    srand(RANDOM_VALUE);
    cout << "The vector with random elements. Size = " << array.size() << ": " << endl;
    for (int i = 0; i < array.size(); i++) {
        array[i] = rand() % 100 + 1;
        cout << "[" << array[i] << "] ";
    }
    cout << endl;
}

void printSortArray(vector<int> array, string & info) {
    cout << info << endl;
    for (int i = 0; i < array.size(); i++) {
        cout << "[" << array[i] << "] ";
    }
    cout << endl;
}

void selectSortMethodAndSortArray(vector<int> array) {
    int numSort;
    cout << "Check the sort method: 1 - QuickSort; 2 - SelectionSort; 3 - InsertionSort; " << endl;
    cin >> numSort;
    string info;
    switch (numSort) {
        case 1:
            quickSort(array, 0, array.size() - 1);
            info = "The quick sort result: ";
            printSortArray(array, info);
            break;
        case 2:
            selectionSort(array);
            info = "The selection sort result: ";
            printSortArray(array, info);
            break;
        case 3:
            insertionSort(array);
            info = "The insertion sort result: ";
            printSortArray(array, info);
            break;
    }
}

int main(int argc, char** argv) {

    int size;
    cout << "Enter the size of vector : ";
    cin >> size;

    vector<int> array(size);
    fillArrayAndPrint(array);
    selectSortMethodAndSortArray(array);
}


