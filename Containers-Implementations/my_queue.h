/* 
 * File:   my_queue.h
 * Author: rokne
 *
 * FIFO queue implementation with singly linked list
 */

#ifndef MY_QUEUE_H
#define	MY_QUEUE_H

using namespace std;

template <typename T>

class MyQueue {
private:

    struct Node {
        T data;
        Node *forward;
    };
    int count;
    Node *head;
    Node *tail;
public:
    MyQueue();
    MyQueue(const MyQueue<T> &);
    ~MyQueue();
    void push(const T &);
    void pop();
    T& front();
    T& back();
    bool empty();
    int size();
    void clear();
};

/*Constructor*/
template <typename T>
MyQueue<T>::MyQueue() {
    head = tail = NULL;
    count = 0;
}

/*Copy constructor*/
template <typename T>
MyQueue<T>::MyQueue(const MyQueue<T>& otherQueue) {
    head = tail = NULL;
    count = 0;
    for (Node *n = otherQueue.head; n != NULL; n = n->forward) {
        push(n->data);
    }
}

/*Destructor*/
template <typename T>
MyQueue<T>::~MyQueue() {
    clear();
}

/*The number of elements in the queue*/
template <typename T>
int MyQueue<T>::size() {
    return count;
}

/*Check the queue is empty*/
template <typename T>
bool MyQueue<T>::empty() {
    return count == 0;
}

/*Delete all elements of the queue*/
template <typename T>
void MyQueue<T>::clear() {
    while (count > 0) {
        pop();
    }
}

/*Add element to the end of the queue*/
template <typename T>
void MyQueue<T>::push(const T& value) {
    Node *n = new Node;
    n->data = value;
    n->forward = NULL;
    if (head == NULL) {
        head = n;
        tail = n;
    } else {
        tail->forward = n;
        tail = n;
    }
    delete n;
    count++;
}

/*Delete the first element from the queue*/
template <typename T>
void MyQueue<T>::pop() {
    if (empty()) {
        cout << "Error [pop]. The queue is empty." << endl;
        exit(1);
    }
    Node *n = head;
    head = n->forward;
    if (head == NULL) {
        tail == NULL;
    }
    delete n;
    count--;
}

/*The first element from the queue*/
template <typename T>
T& MyQueue<T>::front() {
    if (empty()) {
        cout << "Error [front]. The queue is empty." << endl;
        exit(1);
    }
    return head->data;
}

/*The last element from the queue*/
template <typename T>
T& MyQueue<T>::back() {
    if (empty()) {
        cout << "Error [front]. The queue is empty." << endl;
        exit(1);
    }
    return tail->data;
}

#endif	/* MY_QUEUE_H */

