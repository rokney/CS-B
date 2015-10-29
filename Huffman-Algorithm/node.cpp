/* 
 * File:   node.cpp
 * Author: rokne
 * 
 * Created on 13 октября 2015 г., 10:42
 */

#include "node.h"
using namespace std;

Node::Node() {
    ch = '\0';
    weight = 0;
    index = 0;
    parent = -1;
    branch = -1;
}

Node::Node(char c, double w, int n) {
    ch = c;
    weight = w;
    index = n;
    parent = -1;
    branch = -1;
}

void Node::setChar(char c) {
    ch = c;
}

void Node::setWeight(double w) {
    weight = w;
}

void Node::setIndex(int n) {
    index = n;
}

void Node::setParent(int p) {
    parent = p;
}

void Node::setBranch(bool b) {
    branch = b;
}

char Node::getChar() {
    return ch;
}

double Node::getWeight() {
    return weight;
}

int Node::getIndex() {
    return index;
}

int Node::getParent() {
    return parent;
}

bool Node::getBranch() {
    return branch;
}

Node::~Node() {
}

