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


using namespace std;

const int RANDOM_VALUE = 100; //seed of the random generator

/*Sort the vector with the quick sort algorithm*/
void quickSort(vector<int> &array, int begin, int end) {
    int left = begin;
    int right = end;
    int base = array[(begin + end) / 2];
    while (left <= right) {
        /*Check the left element less then base*/
        while (array[left] < base) {
            left++;
        }
        /*Check the right element bigger then base*/
        while (array[right] > base) {
            right--;
        }
        /*If still left element less then the right*/
        if (left <= right) {
            swap(array[left++], array[right--]);
        }
        /*Sort both parts of the vectors while the size of the sort-part bigger 1*/
        if (begin < right) {
            quickSort(array, begin, right);
        }
        if (end > left) {
            quickSort(array, left, end);
        }
    }
}

/*Sort the vector with the selection sort algorithm*/
void selectionSort(vector<int> &array) {
    for (int i = 0; i < array.size() - 1; i++) {
        int min = i;
        for (int j = i + 1; j < array.size(); j++) {
            if (array[j] < array[min]) {
                min = j;
            }
        }
        swap(array[i], array[min]);
    }
}

/*Sort the vector with the insertion sort algorithm*/
void insertionSort(vector<int> &array) {
    for (int i = 0; i < array.size(); i++) {
        for (int j = i; j > 0 && array[j - 1] > array[j]; j--) {
            swap(array[j - 1], array[j]);
        }
    }
}

/*Merge the two halves of the vector in one*/
void merge(vector<int> &array, int left, int split, int right) {
    int leftPos = left; //start position in the left-half vector
    int rightPos = split + 1; //statrt position in the right-half vector
    vector<int> temp; //temporary vector
    /*Compare the elements of the left- and right-halves of the vectors*/
    while (leftPos <= split && rightPos <= right) {
        if (array[leftPos] < array[rightPos]) {
            temp.push_back(array[leftPos++]);
        } else {
            temp.push_back(array[rightPos++]);
        }
    }
    /*If the any half of the vector has some more elements*/
    while (rightPos <= right) {
        temp.push_back(array[rightPos++]);
    }
    while (leftPos <= split) {
        temp.push_back(array[leftPos++]);
    }
    /*Copy elements from the temporary vector to the main*/
    for (int i = 0; i < temp.size(); i++) {
        array[left + i] = temp[i];
    }
}

/*Sort the vector with the merge sort algorithm*/
void mergeSort(vector<int> &array, int left, int right) {
    int split;
    if (left < right) {
        split = (left + right) / 2;
        mergeSort(array, left, split);
        mergeSort(array, split + 1, right);
        merge(array, left, split, right);
    }
}

/*Fill vector with random elements from 1 to 100*/
void fillArrayAndPrint(vector<int> &array) {
    srand(RANDOM_VALUE);
    cout << "The vector with random elements. Size = " << array.size() << ": " << endl;
    for (int i = 0; i < array.size(); i++) {
        array[i] = rand() % 100 + 1;
        cout << "[" << array[i] << "] ";
    }
    cout << endl;
}

/*Display the result of the sort*/
void printSortArray(vector<int> array, string & info) {
    cout << info << endl;
    for (int i = 0; i < array.size(); i++) {
        cout << "[" << array[i] << "] ";
    }
    cout << endl;
}

void selectSortMethodAndSortArray(vector<int> &array) {
    int numSort;
    cout << "Check the sort method (1 - QuickSort; 2 - SelectionSort;"
            " 3 - InsertionSort; 4 - MergeSort) : ";
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
        case 4:
            mergeSort(array, 0, array.size() - 1);
            info = "The merge sort result: ";
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


