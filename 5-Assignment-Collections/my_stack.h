/* 
 * File:   my_stack.h
 * Author: aotian
 *
 * Stack implementation with array
 */

#ifndef MY_STACK_H
#define	MY_STACK_H

#define MAX_SIZE 10

using namespace std;

template <typename T>

class MyStack {
private:
    int count; //index element
    int capacity; //capacity of the stack
    T *array;
public:
    MyStack(int = MAX_SIZE);
    MyStack(const MyStack<T> &);
    ~MyStack();
    void push(const T&);
    void pop();
    T& top();
    bool empty();
    int size();
};

/*Constructor*/
template <typename T>
MyStack<T>::MyStack(int size){
    if(size <=0){
        cout << "Error [size]. Use positive size of the stack." << endl;
        exit(1);
    }
    array = new T[size];
    capacity = size;
    count = -1;
}

/*Copy constructor*/
template <typename T>
MyStack<T>::MyStack(const MyStack<T>& otherStack){
    capacity = otherStack.capacity;
    array = new T[capacity];
    count = otherStack.count;
    for(int i = 0; i < capacity; i++){
        array[i] = otherStack.array[i];
    }
}

/*Destructor*/
template <typename T>
MyStack<T>::~MyStack(){
    delete []array;
}

/*Add element to the top of stack*/
template <typename T>
void MyStack<T>::push(const T& element){
    if(count >= capacity - 1){
        cout << "Error [push]. Stack is overflow." << endl;
        exit(1);
    }
    array[++count] = element;
}

/*delete top element from the stack*/
template <typename T>
void MyStack<T>::pop(){
    if(count == -1){
        cout << "Error [pop]. Stack is empty." << endl;
        exit(1);
    }
    count--;
}

/*Top element of the stack*/
template <typename T>
T& MyStack<T>::top(){
    if(count == -1){
        cout << "Error [top]. Stack is empty." <<endl;
        exit(1);
    }
    return array[count];
}

/*Check the stack is empty*/
template <typename T>
bool MyStack<T>::empty(){
    return count < 0;
}

/*The number of elements in the stack*/
template <typename T>
int MyStack<T>::size(){
    return count + 1;
}

#endif	/* MY_STACK_H */

