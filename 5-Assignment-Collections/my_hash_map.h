/* 
 * File:   my_hash_map.h
 * Author: aotian
 *
 * The hashmap implementation using Stanfords's origin StringMap
 */

#ifndef MY_HASH_MAP_H
#define	MY_HASH_MAP_H

using namespace std;

template <typename K>
class MyHashTable {
private:
    /*Constant definitions*/
    static const int HASH_SEED = 5381; //starting point for first cycle
    static const int HASH_MULTIPLIER = 33; //multiplier for each cycle  
    static const int HASH_MASK = unsigned(-1) >> 1; //All 1 bits except the sign
public:
    int hashCode(const K&);
};

template <typename K>
int MyHashTable<K>::hashCode(const K &elem) {
    if (elem % 10 == 0) {
        return elem;
    } else {
        return elem % 10 + hashCode(elem / 10);
    }
}

template<>
int MyHashTable<string>::hashCode(const string &elem) {
    unsigned hash = HASH_SEED;
    for (int i = 0; i < elem.length(); i++) {
        hash = HASH_MULTIPLIER * hash + elem[i];
    }
    return (int) (hash & HASH_MASK);
}

template <typename K, typename V>
class MyHashMap : MyHashTable<K> {
private:

    struct Node {
        K key;
        V value;
        Node *link; //link for the next Node
    };

    /*Constant definition*/
    static const size_t BUCKET_COUNT = 13;

    Node **buckets; //array of the pointers of Nodes
    int nBuckets; //the number of buckets in the array
    size_t count; //counter of the elements

    Node* findNode(int, const K&);
public:
    MyHashMap(size_t = 0);
    ~MyHashMap();
    void insert(const K &, const V &);
    V& get(const K&);
    size_t size();
    bool empty();
    void clear();
    void erase(const K&);
};

template <typename K, typename V>
MyHashMap<K, V>::MyHashMap(size_t size) {
    nBuckets = (size == 0) ? BUCKET_COUNT : size;
    count = 0;
    buckets = new Node*[nBuckets];
    for (int i = 0; i < nBuckets; i++) {
        buckets[i] = NULL;
    }
}

template <typename K, typename V>
MyHashMap<K, V>::~MyHashMap() {
    for (int i = 0; i < nBuckets; i++) {
        Node *n = buckets[i];
        while (n != NULL) {
            Node *temp = n;
            n = n->link;
            delete temp;
        }
    }
}

template <typename K, typename V>
void MyHashMap<K, V>::insert(const K& key, const V& value) {
    int bucket = this->hashCode(key) % nBuckets;
    Node *n = findNode(bucket, key);
    if (n == NULL) {
        n = new Node;
        n->key = key;
        n->value = value;
        n->link = buckets[bucket];
        buckets[bucket] = n;
        count++;
    }
}

template <typename K, typename V>
V& MyHashMap<K, V>::get(const K& key) {
    int bucket = this->hashCode(key) % nBuckets;
    Node *n = findNode(bucket, key);
    if (n != NULL) {
        return n->value;
    } else {
        cout << "Error. No find key" << endl;
        exit(0);
    }
}

template <typename K, typename V>
typename MyHashMap<K, V>::Node* MyHashMap<K, V>::findNode(int bucket, const K& key) {
    Node *n = buckets[bucket];
    while (n != NULL && n->key != key) {
        n = n->link;
    }
    return n;
}

template <typename K, typename V>
size_t MyHashMap<K, V>::size() {
    return count;
}

template <typename K, typename V>
bool MyHashMap<K, V>::empty() {
    return count == 0;
}

template <typename K, typename V>
void MyHashMap<K, V>::clear(void) {
    if (!empty()) {
        for (int i = 0; i < nBuckets; i++) {
            Node *n = buckets[i];
            while (n != NULL) {
                Node *temp = n;
                n = n->link;
                delete temp;
            }
        }
    }
    count = 0;
}

template <typename K, typename V>
void MyHashMap<K, V>::erase(const K& key) {
    int bucket = this->hashCode(key) % nBuckets;
    Node *n = findNode(bucket, key);
    if (n != NULL) {
        Node *temp = buckets[bucket];
        while (temp->link != n) {
            temp = temp->link;
        }
        temp->link = n->link;
        delete n;
        count--;
    }
}
#endif	/* MY_HASH_MAP_H */

