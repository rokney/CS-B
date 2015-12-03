/* 
 * File:   my_binary_search_tree.h
 * Author: aotian
 *
 */

#ifndef MY_BINARY_SEARCH_TREE_H
#define	MY_BINARY_SEARCH_TREE_H

#define INFIX_TRAVERSE      1
#define PREFIX_TRAVERSE     2
#define POSTFIX_TRAVERSE    3

using namespace std;

template <typename K, typename V>
class BST {
private:

    struct Node {
        K key;
        V value;
        Node* left;
        Node* right;
        int height;
    };
    Node* root;

    void deleteBST(Node*);
    Node* deleteNode(Node*, const K&);
    Node* deleteMinNode(Node*);
    Node* insertNode(Node*, const K&, const V&);
    Node* findNode(Node*, const K&);
    Node* findMinNode(Node*);
    void infixTreverse(Node*);
    void prefixTreverse(Node*);
    void postfixTreverse(Node*);
    int findHeight(Node*);
    int bFactor(Node*);
    void fixHeight(Node*);
    Node* balanceAVL(Node*);
    Node* rotateLeft(Node*);
    Node* rotateRight(Node*);

    template<typename T1, typename T2>
    friend T1& getRootKey(BST<T1, T2>&);

public:
    BST();
    ~BST();
    void add(const K&, const V&);
    V& getValue(const K&);
    void clear();
    void traverseBST(const K& key, int);
    void removeKey(const K&);
    Node* getRoot();
    K& findMax(Node*);
    K& findMin(Node*);
    bool empty();
};

template <typename K, typename V>
BST<K, V>::BST() {
    root = NULL;
}

template <typename K, typename V>
BST<K, V>::~BST() {
    clear();
}

template <typename K, typename V>
void BST<K, V>::add(const K& key, const V& value) {
    root = insertNode(root, key, value);
}

template <typename K, typename V>
typename BST<K, V>::Node* BST<K, V>::insertNode(Node* node, const K& key, const V& value) {
    if (node == NULL) {
        node = new Node;
        node->key = key;
        node->value = value;
        node->height = 1;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    if (key < node->key) {
        node->left = insertNode(node->left, key, value);
    } else if (key > node->key) {
        node->right = insertNode(node->right, key, value);
    } else {
        node->value = value;
    }
    return balanceAVL(node);
}

template <typename K, typename V>
void BST<K, V>::clear(void) {
    deleteBST(root);
    root = NULL;
}

template <typename K, typename V>
void BST<K, V>::deleteBST(Node* root) {
    if (root != NULL) {
        deleteBST(root->left);
        deleteBST(root->right);
        delete root;
    }
}

template <typename K, typename V>
V& BST<K, V>::getValue(const K& key) {
    Node* n = findNode(root, key);
    if (n != NULL) {
        return n->value;
    } else {
        cerr << "Error [getValue]. No matches found" << endl;
        exit(0);
    }
}

template <typename K, typename V>
typename BST<K, V>::Node* BST<K, V>::findNode(Node* node, const K& key) {
    if (node == NULL) {
        return NULL;
    }
    if (key == node->key) {
        return node;
    }
    if (key < node->key) {
        findNode(node->left, key);
    } else {
        findNode(node->right, key);
    }
}

template <typename K, typename V>
void BST<K, V>::traverseBST(const K& key, int num) {
    if (findNode(root, key) != NULL) {
        switch (num) {
            case 1:
                cout << "Infix Treverse Tree: " << endl;
                infixTreverse(findNode(root, key));
                break;
            case 2:
                cout << "Prefix Treverse Tree: " << endl;
                prefixTreverse(findNode(root, key));
                break;
            case 3:
                cout << "Postfix Treverse Tree: " << endl;
                postfixTreverse(findNode(root, key));
                break;
        }
    }else{
        cout << "Traverse the empty tree" << endl;
    }
}

template <typename K, typename V>
void BST<K, V>::infixTreverse(Node* node) {
    if (node != NULL) {
        infixTreverse(node->left);
        cout << node->key << " -> " << node->value << endl;
        infixTreverse(node->right);
    }
}

template <typename K, typename V>
void BST<K, V>::prefixTreverse(Node* node) {
    if (node != NULL) {
        cout << node->key << " -> " << node->value << endl;
        prefixTreverse(node->left);
        prefixTreverse(node->right);
    }
}

template <typename K, typename V>
void BST<K, V>::postfixTreverse(Node* node) {
    if (node != NULL) {
        postfixTreverse(node->left);
        postfixTreverse(node->right);
        cout << node->key << " -> " << node->value << endl;
    }
}

template <typename K, typename V>
typename BST<K, V>::Node* BST<K, V>::findMinNode(Node* node) {
    if (node->left == NULL) {
        return node;
    }
    findMinNode(node->left);
}

template <typename K, typename V>
void BST<K, V>::removeKey(const K& key) {
    root = deleteNode(root, key);
}

template <typename K, typename V>
typename BST<K, V>::Node* BST<K, V>::deleteNode(Node* node, const K& key) {
    if (node == NULL) {
        cerr << "Error. You are trying to remove a nonexistent key -> [" << key << "];" << endl;
        return NULL;
    }
    if (key < node->key) {
        node->left = deleteNode(node->left, key);
    } else if (key > node->key) {
        node->right = deleteNode(node->right, key);
    } else {
        if (!node->left) {
            return node->right;
        }
        if (!node->right) {
            return node->left;
        }
        Node *n = node;
        node = findMinNode(n->right);
        node->right = deleteNode(n->right, node->key);
        node->left = n->left;
        return balanceAVL(node);
    }
    return balanceAVL(node);
}

template <typename K, typename V>
typename BST<K, V>::Node* BST<K, V>::getRoot() {
    return root;
}

template <typename K, typename V>
K& BST<K, V>::findMax(Node *node) {
    while (node->right != NULL) {
        node = node->right;
    }
    return node->key;
}

template <typename K, typename V>
K& BST<K, V>::findMin(Node *node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node->key;
}

template <typename K, typename V>
K& getRootKey(BST<K, V>& tree) {
    if (!tree.empty()) {
        return tree.root->key;
    } else {
        cerr << "Error [getRootKey]. BST is empty" << endl;
        exit(0);
    }
}

template <typename K, typename V>
bool BST<K, V>::empty() {
    return root == NULL;
}

template <typename K, typename V>
int BST<K, V>::findHeight(Node* node) {
    return (node == NULL) ? 0 : node->height;
}

template <typename K, typename V>
int BST<K, V>::bFactor(Node* node) {
    return findHeight(node->right) - findHeight(node->left);
}

template <typename K, typename V>
void BST<K, V>::fixHeight(Node* node) {
    int heightLeft = findHeight(node->left);
    int heightRight = findHeight(node->right);
    node->height = ((heightLeft > heightRight) ? heightLeft : heightRight) + 1;
}

template <typename K, typename V>
typename BST<K, V>::Node* BST<K, V>::deleteMinNode(Node* node) {
    if (node->left == NULL) {
        return node->right;
    }
    node->left = deleteMinNode(node->left);
    return balanceAVL(node);
}

template <typename K, typename V>
typename BST<K, V>::Node* BST<K, V>::balanceAVL(Node* node) {
    fixHeight(node);
    if (bFactor(node) == 2) {
        if (bFactor(node->right) < 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    if (bFactor(node) == -2) {
        if (bFactor(node->left) > 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    return node;
}

template <typename K, typename V>
typename BST<K, V>::Node* BST<K, V>::rotateLeft(Node* node) {
    Node* rightNode = node->right;
    node->right = rightNode->left;
    rightNode->left = node;
    fixHeight(node);
    fixHeight(rightNode);
    return rightNode;
}

template <typename K, typename V>
typename BST<K, V>::Node* BST<K, V>::rotateRight(Node* node) {
    Node* leftNode = node->left;
    node->left = leftNode->right;
    leftNode->right = node;
    fixHeight(node);
    fixHeight(leftNode);
    return leftNode;
}
#endif	/* MY_BINARY_SEARCH_TREE_H */

