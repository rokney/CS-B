/* 
 * File:   my_vector.h
 * Author: aotian
 *
 * Vector implementation with array
 */

#ifndef MY_VECTOR_H
#define	MY_VECTOR_H


using namespace std;

typedef size_t size_type;

template <typename T>

class MyVector {
private:
    T *array;
    size_type sizeV;
    size_type capacityV;
public:
    typedef T* iterator;

    MyVector(size_type = 0);
    MyVector(const MyVector<T> &);
    MyVector(size_type, const T & = 0);
    ~MyVector();
    void push_back(const T &);
    void pop_back();
    void clear();
    T& operator[](size_type);
    void operator=(const MyVector<T> &);
    bool isEmplty();
    size_type size();
    size_type capacity();
    void reserve(size_type);
    void resize(size_type);
    iterator begin();
    iterator end();
    T& front();
    T& back();
    size_type max_size();
    T& at(size_type);
    void erase(iterator);
    void erase(size_type);
    void insert(size_type, const T &);
};

/*Constructor*/
template <typename T>
MyVector<T>::MyVector(size_type s) {
    sizeV = s;
    if (s != 0) {
        capacityV = s;
    } else {
        capacityV = 2;
    }
    array = new T[capacityV];
}

/*Copy constructor*/
template <typename T>
MyVector<T>::MyVector(const MyVector<T> & otherVector) {
    sizeV = otherVector.sizeV;
    capacityV = otherVector.capacityV;
    array = new T[capacityV];
    for (size_type i = 0; i < sizeV; i++) {
        array[i] = otherVector.array[i];
    }
}

/*Secondary consrtuctor*/
template <typename T>
MyVector<T>::MyVector(size_type newSize, const T& element) {
    sizeV = newSize;
    capacityV = newSize;
    array = new T[newSize];
    for (int i = 0; i < newSize; i++) {
        array[i] = element;
    }
}

/*Destructor*/
template <typename T>
MyVector<T>::~MyVector() {
    delete [] array;
}

/*Add element to the end of vector*/
template <typename T>
void MyVector<T>::push_back(const T &element) {
    if (sizeV >= capacityV) {
        capacityV *= 2;
        reserve(capacityV);
    }
    array[sizeV++] = element;
}

/*Delete the last element from the vector*/
template <typename T>
void MyVector<T>::pop_back() {
    sizeV--;
}

/*Delete all elements of the vector*/
template <typename T>
void MyVector<T>::clear() {
    sizeV = 0;
    capacityV = 0;
    array = 0;
}

/*Overload operator []*/
template <typename T>
T& MyVector<T>::operator[](size_type index) {
    try {
        if (index >= sizeV) {
            throw 1;
        }
        return array[index];
    } catch (int e) {
        cout << "Error index [" << index << "]. Out of range." << endl;
        exit(0);
    }
}

/*Overload operator=*/
template <typename T>
void MyVector<T>::operator=(const MyVector<T>& otherVector) {
    if (array != otherVector.array) {
        delete []array;
        sizeV = otherVector.sizeV;
        capacityV = otherVector.capacityV;
        array = new T[capacityV];
        for (size_type i = 0; i < sizeV; i++) {
            array[i] = otherVector.array[i];
        }
    }
}

/*Check the vector is empty*/
template <typename T>
bool MyVector<T>::isEmplty() {
    return sizeV == 0;
}

/*The number of elements in the vector*/
template <typename T>
size_t MyVector<T>::size() {
    return sizeV;
}

/*The capacity of the vector*/
template <typename T>
size_t MyVector<T>::capacity() {
    return capacityV;
}

/*Reserve needed memory for currrent vector*/
template <typename T>
void MyVector<T>::reserve(size_type newCapacity) {
    T * newArray;
    size_type newSize = newCapacity < sizeV ? newCapacity : sizeV;

    newArray = new T[capacityV];
    for (size_type i = 0; i < newSize; i++) {
        newArray[i] = array[i];
    }
    capacityV = newCapacity;
    delete [] array;
    array = newArray;
}

/*Change the size of the current vector*/
template <typename T>
void MyVector<T>::resize(size_type newSize) {
    reserve(newSize);
    sizeV = newSize;
}

/*The first element of the vector*/
template <typename T>
T& MyVector<T>::front() {
    try {
        if (sizeV == 0) {
            throw 2;
        }
        return array[0];
    } catch (int e) {
        cout << "Error [front]. Vector is empty." << endl;
        exit(0);
    }
}

/*The last element of the vector*/
template <typename T>
T& MyVector<T>::back() {
    try {
        if (sizeV == 0) {
            throw 2;
        }
        return array[sizeV - 1];
    } catch (int e) {
        cout << "Error [back]. Vector is empty." << endl;
        exit(0);
    }
}

/*Pointer to the start of the vector*/
template <typename T>
typename MyVector<T>::iterator MyVector<T>::begin() {
    return array;
}

/*Pointer to the end of the vector*/
template <typename T>
typename MyVector<T>::iterator MyVector<T>::end() {
    return array + sizeV;
}

/*The max possible size of the vector*/
template <typename T>
size_type MyVector<T>::max_size() {
    return (size_t) (-1) / sizeof (size_type);
}

/*Access element by index*/
template <typename T>
T& MyVector<T>::at(size_type index) {
    try {
        if (index >= sizeV) {
            throw 1;
        }
        return array[index];
    } catch (int e) {
        cout << "Error at(" << index << "). Out of range." << endl;
        exit(0);
    }
}

/*Delete element in current position with iterator*/
template <typename T>
void MyVector<T>::erase(iterator it) {
    if (it == end()) {
        pop_back();
    } else {
        for (iterator i = it; i < end(); i++) {
            *i = *(i + 1);
        }
        pop_back();
    }
}

/*Delete element in current position with index*/
template <typename T>
void MyVector<T>::erase(size_type index) {
    try {
        if (index < 0 || index >= sizeV) {
            throw 1;
        }
        for (size_type i = index; i < sizeV - 1; i++) {
            array[i] = array[i + 1];
        }
        sizeV--;
    } catch (int e) {
        cout << "Error erase (" << index << "). Out of range." << endl;
        exit(0);
    }
}

/*Insert element to the vector in curent position*/
template <typename T>
void MyVector<T>::insert(size_type index, const T &element) {
    if (index == capacityV) {
        resize(sizeV++);
    }
    try {
        if (index < 0 || index >= sizeV) {
            throw 1;
        }
        for (size_type i = sizeV; i > index; i--) {
            array[i] = array[i - 1];
        }
        array[index] = element;
        sizeV++;
    } catch (int e) {
        cout << "Error insert (" << index << "). Out of range." << endl;
        exit(0);
    }
}
#endif	/* MY_VECTOR_H */