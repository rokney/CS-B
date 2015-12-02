/* 
 * File:   MyQueue.h
 * Author: aotian
 *
 * Queue implementation with vector
 */

#ifndef MYQUEUE_H
#define	MYQUEUE_H

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

template <typename T>

class MyQueue {
private:
    int sizeQueue; // the size of the queue (number of elements)
    int begin, end; // the point of the begin and the end of the queue
    vector<T> elements;
public:
    MyQueue(int = 10); // default size of the queue = 10
    MyQueue(const MyQueue<T> &); // copy constructor
    ~MyQueue();
    void push_back(T);
    void pop();
    T &front();
    T &back();
    void print(string = "Queue: ");
    void clear();
    int size();
    bool isEmpty();
    void operator=(const MyQueue<T> &);
};

template <typename T>
MyQueue<T>::MyQueue(int s) {
    sizeQueue = s;
    begin = 0;
    end = 0;
    elements.reserve(sizeQueue);
}

template <typename T>
MyQueue<T>::MyQueue(const MyQueue<T>& otherMyQueue) {
    sizeQueue = otherMyQueue.sizeQueue;
    begin = otherMyQueue.begin;
    end = otherMyQueue.end;
    //copy elements from current queue to other
    elements.reserve(sizeQueue);
    for (int i = 0; i < sizeQueue; i++) {
        elements.push_back(otherMyQueue.elements[i]);
    }
}

template <typename T>
MyQueue<T>::~MyQueue() {
}

template <typename T>
void MyQueue<T>::push_back(T element) {
    elements.push_back(element);
    end++;
    sizeQueue = elements.size();
}

template <typename T>
void MyQueue<T>::pop() {
    //check the number of elements
    if (sizeQueue > 0) {
        //delete first element
        elements.erase(elements.begin());
        end--;
        sizeQueue = elements.size();
    }
}

template <typename T>
T &MyQueue<T>::front() {
    T *frontElement;
    if (sizeQueue > 0) {
        frontElement = &elements[begin];
    }
    return *frontElement;
}

template <typename T>
T &MyQueue<T>::back() {
    T *backElement;
    if (sizeQueue > 0) {
        backElement = &elements[end - 1];
    }
    return *backElement;
}

template <typename T>
void MyQueue<T>::print(string str) {
    cout << str << endl;
    if (elements.size() == 0) {
        cout << "Queue is empty." << endl;
    } else {
        cout << "[ ";
        for (int i = begin; i < end; i++) {
            if (i < end - 1) {
                cout << elements[i] << ", ";
            } else {
                cout << elements[i];
            }
        }
        cout << " ]" << endl;
    }
}

template <typename T>
void MyQueue<T>::clear() {
    if (elements.size() > 0) {
        //change all parameters to deafult (zero);
        begin = 0;
        end = 0;
        sizeQueue = 0;
        elements.clear();
    }
}

template <typename T>
int MyQueue<T>::size() {
    return sizeQueue;
}

template <typename T>
bool MyQueue<T>::isEmpty() {
    return sizeQueue == 0;
}
#endif	/* MYQUEUE_H */

