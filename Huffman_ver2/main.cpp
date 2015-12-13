/* 
 * File:   main.cpp
 * Author: aotyan
 *
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <clocale>
#include <vector>
#include <queue>
#include <string>
#include <map>

using namespace std;

/*The struct of data for huffman tree*/
struct Node {
    char ch;
    double weight;
    int index;
    int parent;
    int left;
    int right;
};

/*The functor for the priority queue*/
class CompareNode {
public:

    bool operator()(Node left, Node right) {
        return left.weight > right.weight;
    }
};

/*Function prototypes*/
void enterDataFromConsole(void);
void compress(string inputFile, string outputFile);
void decompress(string inputFIle, string outputFile);
vector<int> readFileAndCreateFrequencyTable(string inputFile);
vector<Node> createHuffmanTree(vector<int> frequency);
void fillTreeAndQueue(vector<int> &frequency, vector<Node> &tree,
        priority_queue<Node, vector<Node>, CompareNode> &queue);
void buildHuffmanTree(vector<Node> &tree,
        priority_queue<Node, vector<Node>, CompareNode> &q);
void createHuffmanTable(map<char, vector<bool> > &huffmanTable,
        vector<Node> huffmanTree);
void buildHuffmanTable(Node &n, vector<Node> tree, vector<bool> &encode,
        map<char, vector<bool> > &huffmanTable);
vector<bool> encodeInputFile(map<char, vector<bool> > huffmanTable,
        string inputFile);
void saveEncodeData(vector<Node> huffmanTree, vector<bool> code,
        string outputFile);
void readHuffmanTreeAndEncodeDataFromInputFile(vector<Node> &huffmanTree,
        vector<bool> &decode, string inputFile);
void saveDecodeData(vector<Node> huffmanTree, vector<bool> decode,
        string outputFile);

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Russian");
    if (argc > 1) {
        if (argv[1][0] == 'c') {
            compress(argv[2], argv[3]);
        } else if (argv[1][0] == 'd') {
            decompress(argv[2], argv[3]);
        } else {
            cout << "Invalid command..." << endl;
        }
    } else {
        enterDataFromConsole();
    }
    return 0;
}

/**
 * If the program started without any arguments,
 * user would enter the data himself with console
 */
void enterDataFromConsole(void) {
    while (true) {
        string answer, inputFile, outputFile;
        cout << "Do you want to compress or decompress file?"
                "(QUIT for exit) : ";
        getline(cin, answer);
        if (answer == "QUIT") {
            break;
        }
        cout << "Enter the name of the input file: ";
        getline(cin, inputFile);
        cout << "Enter the name of the output file: ";
        getline(cin, outputFile);
        if (answer == "compress") {
            compress(inputFile, outputFile);
        } else if (answer == "decompress") {
            decompress(inputFile, outputFile);
        } else {
            cout << "Invalid command. Enter \"compress\" or "
                    "\"decompress\"..." << endl;
        }
    }
}

/**
 * Compress input file with Huffman algorithm. Create the frequency table,
 * huffman tree, huffman table, encode input data, save encode data to new file.
 */
void compress(string inputFile, string outputFile) {
    vector<int> frequency = readFileAndCreateFrequencyTable(inputFile);
    vector<Node> huffmanTree = createHuffmanTree(frequency);
    map<char, vector<bool> > huffmanTable;
    createHuffmanTable(huffmanTable, huffmanTree);
    vector<bool> code = encodeInputFile(huffmanTable, inputFile);
    saveEncodeData(huffmanTree, code, outputFile);
}

/**
 * Decompress the input file with Huffman algorithm. Read the Huffman tree and
 * encode data. Decode it and save to new file.
 */
void decompress(string inputFile, string outputFile) {
    vector<Node> huffmanTree;
    vector<bool> decode;
    readHuffmanTreeAndEncodeDataFromInputFile(huffmanTree, decode, inputFile);
    saveDecodeData(huffmanTree, decode, outputFile);
}

/**
 * Read input file for compress, create the frequency table of the characters and
 * the number of thier occurences in the file.
 * Return the frequency table.
 */
vector<int> readFileAndCreateFrequencyTable(string inputFile) {
    vector<int> result(256, 0);
    ifstream file(inputFile.c_str(), ios::binary);
    if (file.is_open()) {
        while (!file.eof()) {
            unsigned char c;
            file.read((char*) &c, sizeof (c));
            if (file.eof()) {
                break;
            }
            result[c]++;
        }
    }
    file.close();
    return result;
}

/**
 * Create the Huffmane tree with Huffman algorithm. Use the frequency table.
 * Return the tree.
 */
vector<Node> createHuffmanTree(vector<int> frequency) {
    vector<Node> tree;
    priority_queue<Node, vector<Node>, CompareNode> queue;
    fillTreeAndQueue(frequency, tree, queue);
    buildHuffmanTree(tree, queue);
    return tree;
}

/**
 * Fill Huffman tree and priority queue with initial nodes.
 */
void fillTreeAndQueue(vector<int> &frequency, vector<Node> &tree,
        priority_queue<Node, vector<Node>, CompareNode> &queue) {
    for (int i = 0; i < frequency.size(); i++) {
        if (frequency[i] != 0) {
            Node n;
            n.ch = (char) i;
            n.weight = frequency[i];
            n.index = tree.size();
            n.parent = n.left = n.right = -1;
            tree.push_back(n);
            queue.push(n);
        }
    }
}

/**
 * Build Huffman tree with priority queue. Create new nodes from initial,
 * add them to the tree, until the root node will be created.
 */
void buildHuffmanTree(vector<Node> &tree,
        priority_queue<Node, vector<Node>, CompareNode> &q) {
    while (q.size() > 1) {
        Node firstNode = q.top();
        q.pop();
        double weightFirst = firstNode.weight;
        int indexFirst = firstNode.index;
        Node secondNode = q.top();
        q.pop();
        double weightSecond = secondNode.weight;
        int indexSecond = secondNode.index;
        int newIndex = tree.size();
        Node newNode = {'\0', (weightFirst + weightSecond),
            newIndex, -1, indexFirst, indexSecond};
        tree.push_back(newNode);
        q.push(newNode);
        tree[indexFirst].parent = newIndex;
        tree[indexSecond].parent = newIndex;
    }
}

/**
 * Create Huffman table from the Huffman tree. This table contains the characters
 * and their binary code.
 */
void createHuffmanTable(map<char, vector<bool> > &huffmanTable,
        vector<Node> huffmanTree) {
    vector<bool> encode;
    Node root = huffmanTree[huffmanTree.size() - 1];
    buildHuffmanTable(root, huffmanTree, encode, huffmanTable);
}

/**
 * Recursively traverse the tree for create Huffman table.
 */
void buildHuffmanTable(Node &n, vector<Node> tree, vector<bool> &encode,
        map<char, vector<bool> > &table) {
    if (n.left != -1) {
        encode.push_back(0);
        buildHuffmanTable(tree[n.left], tree, encode, table);
    }
    if (n.right != -1) {
        encode.push_back(1);
        buildHuffmanTable(tree[n.right], tree, encode, table);
    }
    if (n.right == -1 && n.left == -1) {
        table[n.ch] = encode;
    }
    encode.pop_back();
}

/**
 * Encode input file with the Huffman table. Save new data to the vector of
 * booleans.
 * Return this vector.
 */
vector<bool> encodeInputFile(map<char, vector<bool> > huffmanTable,
        string inputFile) {
    vector<bool> result;
    ifstream file(inputFile.c_str(), ios::binary);
    while (!file.eof()) {
        char c;
        file.read(&c, sizeof (c));
        if (file.eof()) {
            break;
        }
        if (huffmanTable.find(c) != huffmanTable.end()) {
            result.insert(result.end(), huffmanTable[c].begin(),
                    huffmanTable[c].end());
        }
    }

    file.close();
    return result;
}

/**
 * Save the encode data. At first save the size of the Huffman tree, then save 
 * each node. After that, save the size of the encode vector, and each element.
 * Convert each 8 elements of the vector to 1 byte.
 */
void saveEncodeData(vector<Node> huffmanTree, vector<bool> code,
        string outputFile) {
    ofstream file(outputFile.c_str(), ios::binary);
    int treeSize = huffmanTree.size();
    file.write((char*) &treeSize, sizeof (treeSize));
    for (int i = 0; i < treeSize; i++) {
        file.write((char*) &huffmanTree[i], sizeof (huffmanTree[i]));
    }
    int codeSize = code.size();
    file.write((char*) &codeSize, sizeof (codeSize));
    for (int i = 0; i <= code.size() / 8; i++) {
        char ch = 0;
        for (int j = 0; j < 8; j++) {
            if (code[i * 8 + j]) {
                ch |= (1 << j);
            }
        }
        file.write(&ch, sizeof (ch));
    }
    file.close();
}

/**
 * Open the input file for decompress.
 * Read the size of the Huffman tree. Read each node. Add to the new Huffman tree.
 * Read encode data. Convert it and add to the decode vector of booleans
 */
void readHuffmanTreeAndEncodeDataFromInputFile(vector<Node> &huffmanTree,
        vector<bool> &decode, string inputFile) {
    ifstream file(inputFile.c_str(), ios::binary);
    int treeSize = 0;
    if (file.is_open()) {
        file.read((char*) &treeSize, sizeof (treeSize));
        for (int i = 0; i < treeSize; i++) {
            Node n;
            file.read((char*) &n, sizeof (n));
            huffmanTree.push_back(n);
        }
        int decodeSize = 0;
        file.read((char*) &decodeSize, sizeof (decodeSize));
        int count = 0;
        while (!file.eof()) {
            char ch;
            file.read(&ch, sizeof (ch));
            if (file.eof()) {
                break;
            }
            for (int i = 0; i < 8; i++) {
                decode.push_back((ch & (1 << i)) != 0);
                count++;
                if (count == decodeSize) {
                    break;
                }
            }
        }
    }
    file.close();
}

/**
 * Convert the decode data to the original data with Huffman tree.
 * Save new data to the new file.
 */
void saveDecodeData(vector<Node> huffmanTree, vector<bool> decode,
        string outputFile) {
    ofstream file(outputFile.c_str(), ios::binary);
    int rootIndex = huffmanTree.size() - 1;
    for (int i = 0; i < decode.size(); i++) {
        if (decode[i]) {
            rootIndex = huffmanTree[rootIndex].right;
        } else {
            rootIndex = huffmanTree[rootIndex].left;
        }
        if (huffmanTree[rootIndex].left == -1) {
            file << huffmanTree[rootIndex].ch;
            rootIndex = huffmanTree.size() - 1;
        }
    }
    file.close();
}