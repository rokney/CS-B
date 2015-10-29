/* 
 * File:   main.cpp
 * Author: aotian
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iterator>
#include <vector>
#include "node.h"
#include "compareNode.h"
#include <queue>

using namespace std;

string fileName;

void openFile(ifstream &file) {
    while (true) {
        cout << "Enter valid file name for encoding: ";
        getline(cin, fileName);
        file.open(fileName.c_str());
        if (file.fail()) {
            cout << "Error...Not valid file name. Try again..." << endl;
        } else {
            break;
        }
    }
}

map<char, double> getFrequencyTable() {
    ifstream file;
    openFile(file);
    map<char, double> result;
    cout << "Reading file..." << endl;
    while (!file.eof()) {
        char c;
        file.read((char*) &c, sizeof (c));
        if (file.eof()) break;
        if (result.find(c) != result.end()) {
            result.find(c)->second++;
        } else {
            result.insert(make_pair(c, 1));
        }
    }
    cout << "Created frequency table." << endl;
    file.close();
    return result;
}

void fillQueueAndTreeByNodes(map<char, double> &frequencies, vector<Node> &tree,
        priority_queue<Node, vector<Node>, CompareNode> &q) {

    for (map<char, double>::iterator it = frequencies.begin();
            it != frequencies.end(); it++) {
        int index = tree.size();
        Node n(it->first, it->second, index);
        tree.push_back(n);
        q.push(n);
    }
}

void buildHuffmanTree(priority_queue<Node, vector<Node>, CompareNode> &q,
        vector<Node> &tree) {

    while (q.size() > 1) {
        //get first element of the tree with the smallest weight
        Node currentNode = q.top();
        double weightFirst = currentNode.getWeight();
        int indexFirst = currentNode.getIndex();
        q.pop();
        //get other first element of the tree with the smallest weight
        currentNode = q.top();
        double weigthSecond = currentNode.getWeight();
        int indexSecond = currentNode.getIndex();
        q.pop();
        int newIndex = tree.size();
        //put back the new element, which weight is sum of first two elements
        tree.push_back(Node('\0', (weightFirst + weigthSecond), newIndex));
        q.push(Node('\0', (weightFirst + weigthSecond), newIndex));
        //change the parameters of the spacified elements
        tree[indexFirst].setParent(newIndex);
        tree[indexFirst].setBranch(false);
        tree[indexSecond].setParent(newIndex);
        tree[indexSecond].setBranch(true);
    }
}

vector<bool> convertChar(vector<Node> &tree) {
    vector<bool> result;
    ifstream file(fileName.c_str());
    while (!file.eof()) {
        char c;
        file.read((char*) &c, sizeof (c));
        if (file.eof()) break;
        Node currentNode;
        for (int i = 0; i < tree.size(); i++) {
            /*Find the node contains current character*/
            if (tree[i].getChar() == c) {
                currentNode = tree[i];
            }
        }
        vector<bool> temp;
        while (currentNode.getParent() != -1) {
            temp.push_back(currentNode.getBranch());
            currentNode = tree[currentNode.getParent()];
        }
        /*keep the received code in the reserve order */
        result.insert(result.end(), temp.rbegin(), temp.rend());
    }
    file.close();
    return result;
}

void saveEncodeFile(vector<bool> &encode, vector<Node> &tree) {
    cout << "Enter the file name to save compressed file: ";
    getline(cin, fileName);
    ofstream file(fileName.c_str(), ios::binary);
    //write to the file tree's size for future read tree from file
    unsigned int treeSize = tree.size();
    file.write((char*) &treeSize, sizeof (treeSize));
    //write to the file the tree
    for (int i = 0; i < treeSize; i++) {
        file.write((char*) &tree[i], sizeof (tree[i]));
    }
    //write bits (bytes) of our encode vector to the file
    unsigned int encodeSize = encode.size();
    file.write((char*) &encodeSize, sizeof (encodeSize));
    for (int i = 0; i <= encode.size() / 8; i++) {
        char ch = 0;
        for (int j = 0; j < 8; j++) {
            if (encode[i * 8 + j]) {
                ch |= (1 << j);
            }
        }
        file.write((char *) &ch, sizeof (ch));
    }
    file.close();

    cout << "Compression completed successfully." << endl;
}

void encodeFile(vector<Node> &tree) {
    vector<bool> encode = convertChar(tree);

    /*
     * Print encode bits
     * 
    cout << "Encode bites ";
    for (int i = 0; i < encode.size(); i++) {
        if (i % 4 == 0 && i != 0) {
            cout << " ";
        }
        cout << encode[i];
    }
    cout << endl;
     */

    saveEncodeFile(encode, tree);
}

void compressFile(void) {
    map<char, double> frequencies = getFrequencyTable();
    vector<Node> tree;
    priority_queue<Node, vector<Node>, CompareNode> q;
    fillQueueAndTreeByNodes(frequencies, tree, q);
    buildHuffmanTree(q, tree);
    encodeFile(tree);
}

void readTreeAndEncodeDataFromFile(string &fileName, vector<Node> &tree,
        vector<bool> &decode) {

    ifstream fin(fileName.c_str(), ios::binary);

    unsigned int treeSize; //the size of our Huffman tree
    fin.read((char*) &treeSize, sizeof (treeSize));
    /**
     * Read nodes and push back to the tree
     */
    for (int i = 0; i < treeSize; i++) {
        Node n;
        fin.read((char*) &n, sizeof (n));
        tree.push_back(n);
    }

    unsigned int decodeSize; //the number of encode bits
    fin.read((char*) &decodeSize, sizeof (decodeSize));

    int count = 0; //respond for the number of read bits

    while (!fin.eof()) {
        char ch;
        fin.read((char*) &ch, sizeof (ch));
        if (fin.eof()) break;
        for (int i = 0; i < 8; i++) {
            decode.push_back((ch & (1 << i)) != 0);
            count++;
            if (count == decodeSize) break;
        }
    }
    /*
     * Print decode bits (for check wirh encode)
     * 
    cout << "Decode bites ";
    for (int i = 0; i < encode.size(); i++) {
        if (i % 4 == 0 && i != 0) {
            cout << " ";
        }
        cout << data[i];
    }
    cout << endl;
     */
    fin.close();
}

void decodeFileAndDisplay(vector<Node> &tree, vector<bool> &decode) {
    int indexRoot = tree.size() - 1; //the index of the root of our Huffman tree
    Node currentNode = tree[indexRoot]; //start decode from the root of the tree
    for (int i = 0; i < decode.size(); i++) {
        for (int j = 0; j < tree.size(); j++) {
            /**
             * Check the node with current branch and parent
             */
            if (tree[j].getParent() == currentNode.getIndex()
                    && tree[j].getBranch() == decode[i]) {
                currentNode = tree[j];
            }
        }
        /*If current node contains the character*/
        if (currentNode.getChar() != '\0') {
            cout << currentNode.getChar();
            //return to the root of the tree
            currentNode = tree[indexRoot];
        }
    }
    cout << endl;
}

void decompressFile(void) {
    cout << "Enter file name for decompress: ";
    getline(cin, fileName);

    vector<Node> tree;
    vector<bool> decode;

    readTreeAndEncodeDataFromFile(fileName, tree, decode);

    decodeFileAndDisplay(tree, decode);
}

int main() {
    cout << "Hello! Welcome to the Huffman program encoding.." << endl;
    string answer;
    while (true) {
        cout << "Do you want to compress or decompress file?(QUIT for exit) : ";
        getline(cin, answer);
        if (answer == "compress") {
            compressFile();
        } else if (answer == "decompress") {
            decompressFile();
        } else if (answer == "QUIT") {
            break;
        } else {
            cout << "Invalid command. Enter \"compress\" or \"decompress\"..." << endl;
        }
    }
    return 0;
}


