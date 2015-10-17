/* 
 * File:   MyStack.h
 * Author: aotian
 *
 */



#ifndef MYSTACK_H
#define	MYSTACK_H

#include <iostream>
#include <vector>

using namespace std;

template <typename T>

class MyStack {
private:
    vector<T> elements;
public:

    MyStack(int size = 0) {
        elements.reserve(size);
    }

    ~MyStack() {
        //cout << "Stack dead..." << endl;
    }

    MyStack(const MyStack<T> &);

    void push(T element) {
        elements.push_back(element);
    }

    void pop() {
        if (elements.size() > 0) {
            elements.pop_back();
        }
    }

    int size() {
        return elements.size();
    }

    T &top() {
        if (elements.size() > 0) {
            return elements.back();
        }
    }

    void clear() {
        if (elements.size() > 0) {
            elements.clear();
        }
    }

    bool isEmpty() {
        return elements.size() == 0 ? true : false;
    }

    void print() {
        for (int i = elements.size() - 1; i >= 0; i--) {
            cout << "[" << elements[i] << "]" << endl;
        }
    }
};

template <typename T>
MyStack<T>::MyStack(const MyStack<T> & otherStack) {
    int size= otherStack.elements.size();
    for (int i = 0; i < size; i++) {
        elements.push_back(otherStack.elements[i]);
    }
}


#endif	/* MYSTACK_H */

