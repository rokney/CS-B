/* 
 * File:   MyPriorityQueue.h
 * Author: aotian
 */

#ifndef MYPRIORITYQUEUE_H
#define	MYPRIORITYQUEUE_H

using namespace std;

template <typename T>

class MyPriorityQueue {
private:

    struct Node {
        T data;
        int priority;
        Node *forward;
        Node *backward;
    };
    int count;
    Node *head;
    Node *tail;
public:
    MyPriorityQueue<T>();
    MyPriorityQueue<T>(const MyPriorityQueue<T> &);
    ~MyPriorityQueue<T>();
    T dequeue();
    void push_back(const T&, int);
    void clear();
    bool isEmpty();
    int size();
    T& front();
    T& back();
    void pop_back();
};

template <typename T>
MyPriorityQueue<T>::MyPriorityQueue() {
    head = tail = NULL;
    count = 0;
}

template <typename T>
MyPriorityQueue<T>::MyPriorityQueue(const MyPriorityQueue<T> & otherQueue) {
    head = tail = NULL;
    count = 0;
    for(Node *n = otherQueue.head; n != NULL; n = n->forward){
        push_back(n->data, n->priority);
    }
}

template <typename T>
MyPriorityQueue<T>::~MyPriorityQueue() {
    clear();
}

template <typename T>
int MyPriorityQueue<T>::size() {
    return count;
}

template <typename T>
bool MyPriorityQueue<T>::isEmpty() {
    return count == 0;
}

template <typename T>
void MyPriorityQueue<T>::clear() {
    while (count > 0) {
        dequeue();
    }
}

template <typename T>
void MyPriorityQueue<T>::push_back(const T& value, int weight) {
    Node *n = new Node;
    n->data = value;
    n->priority = weight;
    n->forward = NULL;
    n->backward = NULL;
    if (head == NULL) {
        head = n;
        tail = n;
    } else if (tail->priority <= n->priority) {
        tail->forward = n;
        n->backward = tail;
        tail = n;
    } else if (head->priority > n->priority) {
        n->forward = head;
        head->backward = n;
        head = n;
    } else {
        Node *temp = new Node;
        temp = tail->backward;
        while (temp->priority > n->priority) {
            temp = temp->backward;
        }
        n->forward = temp->forward;
        temp->forward = n;
        n->backward = temp;
    }
    count++;
}

template <typename T>
T MyPriorityQueue<T>::dequeue() {
    if (isEmpty()) {
        cout << "Error [dequeue]. The queue is empty." << endl;
        exit(0);
    }
    Node *n = head;
    T result = n->data;
    head = n->forward;
    if (head == NULL) tail = NULL;
    delete n;
    count--;
    return result;
}

template <typename T>
T& MyPriorityQueue<T>::front() {
    if (isEmpty()) {
        cout << "Error [front]. The queue is empty." << endl;
        exit(0);
    }
    return head->data;
}

template <typename T>
T& MyPriorityQueue<T>::back() {
    if (isEmpty()) {
        cout << "Error [back]. The queue is empty." << endl;
        exit(0);
    }
    return tail->data;
}

template <typename T>
void MyPriorityQueue<T>::pop_back() {
    if (isEmpty()) {
        cout << "Error [pop_back]. The queue is empty." << endl;
        exit(0);
    }
    tail = tail->backward;
    tail->forward = NULL;
    count--;
}


#endif	/* MYPRIORITYQUEUE_H */

