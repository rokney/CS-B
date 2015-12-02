/* 
 * File:   my_list.h
 * Author: aotian
 *
 * Doubly linked list implementation
 */

#ifndef MY_LIST_H
#define	MY_LIST_H
using namespace std;

typedef size_t size_type;

template <typename T>

class MyList {
private:

    struct Node {
        T data;
        Node *next;
        Node *prev;
    };
    size_type count;
    Node *head;
    Node *tail;
public:
    MyList();
    MyList(const MyList<T>& otherList);
    virtual ~MyList();
    void push_front(const T&);
    void push_back(const T&);
    void pop_front();
    void pop_back();
    bool empty();
    size_type size();
    T& front();
    T& back();
    void clear();

    typedef Node* iterator;
    iterator begin();
    iterator end();
    void insert(iterator, const T&);
    void erase(iterator);
};

/*Constructor*/
template <typename T>
MyList<T>::MyList() {
    head = tail = NULL;
    count = 0;
}

/*Copy-constructor*/
template <typename T>
MyList<T>::MyList(const MyList<T>& otherList) {
    if (!otherList.empty()) {
        head = tail = 0;
        count = 0;
        for (Node *n = otherList.head; n != NULL; n = n->next) {
            push_back(n->data);
        }
    } else {
        cerr << "Error [copy constructor]. Try to copy empty list..." << endl;
        exit(0);
    }
}

/*Destructor*/
template <typename T>
MyList<T>::~MyList() {
    clear();
}

/*Add element to the start of list*/
template <typename T>
void MyList<T>::push_front(const T& value) {
    Node *n = new Node;
    n->data = value;
    n->next = NULL;
    n->prev = NULL;
    if (head == NULL) {
        head = n;
        tail = n;
    } else {
        n->next = head;
        head->prev = n;
        head = n;
    }
    count++;
}

/*Add element to the end of list*/
template <typename T>
void MyList<T>::push_back(const T& value) {
    Node *n = new Node;
    n->data = value;
    n->next = NULL;
    n->prev = NULL;
    if (head == NULL) {
        head = n;
        tail = n;
    } else {
        n->prev = tail;
        tail->next = n;
        tail = n;
    }
    count++;
}

/*Delete the first element from the list*/
template <typename T>
void MyList<T>::pop_front() {
    if (empty()) {
        cerr << "Error [pop_front]. The list is emprty." << endl;
        exit(0);
    }
    head = head->next;
    if (head == NULL) {
        tail = NULL;
    } else {
        head->prev = NULL;
        count--;
    }
}

/*Delete the last element from the list*/
template <typename T>
void MyList<T>::pop_back() {
    if (empty()) {
        cerr << "Error [pop_back]. The list is emprty." << endl;
        exit(0);
    }
    tail = tail->prev;
    if (tail == NULL) {
        head = NULL;
    } else {
        tail->next = NULL;
        count--;
    }
}

/*Check the list is empty*/
template <typename T>
bool MyList<T>::empty() {
    return count == 0;
}

/*Number of elements of the list*/
template <typename T>
size_type MyList<T>::size() {
    return count;
}

/*The first element in the list*/
template <typename T>
T& MyList<T>::front() {
    if (empty()) {
        cerr << "Error [front]. The list is empty." << endl;
        exit(0);
    }
    return head->data;
}

/*The last element in the list*/
template <typename T>
T& MyList<T>::back() {
    if (empty()) {
        cerr << "Error [back]. The list is empty." << endl;
        exit(0);
    }
    return tail->data;
}

/*Pointer to the start of the list*/
template <typename T>
typename MyList<T>::iterator MyList<T>::begin() {
    return head;
}

/*Pointer to the end of the list*/
template <typename T>
typename MyList<T>::iterator MyList<T>::end() {
    return tail;
}

/*Delete all elements of the list*/
template <typename T>
void MyList<T>::clear() {
    while (head) {
        head->prev = NULL;
        head = head->next;
    }
    count = 0;
}

/*Insert element to the list in current position*/
template <typename T>
void MyList<T>::insert(iterator it, const T& value) {
    if (empty()) {
        cerr << "Error [insert]. The list is empty." << endl;
        exit(0);
    }
    if (it == begin()) {
        push_front(value);
    } else if (it == end()) {
        push_back(value);
    } else if (it != NULL) {
        Node *n = new Node;
        n->data = value;
        n->next = it;
        n->prev = it->prev;
        it->prev->next = n;
        it->prev = n;
        count++;
    } else {
        cerr << "Error [insert]. Iterator is out of range." << endl;
        exit(0);
    }
}

/*Delete element from the list from the current position*/
template <typename T>
void MyList<T>::erase(iterator it) {
    if (empty()) {
        cerr << "Error [erase]. The list is empty." << endl;
        exit(0);
    }
    if (it == begin()) {
        pop_front();
    } else if (it == end()) {
        pop_back();
    } else if (it != NULL) {
        Node *n = it->prev;
        Node *m = it->next;
        it = it->next;
        n->next = m;
        m->prev = n;
        count--;
    } else {
        cerr << "Error [erase]. Iterator is out of range." << endl;
        exit(0);
    }
}

#endif	/* MY_LIST_H */

