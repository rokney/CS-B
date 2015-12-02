/* 
 * File:   compareNode.h
 * Author: rokne
 *
 * Created on 13 октября 2015 г., 12:00
 */

#ifndef COMPARENODE_H
#define	COMPARENODE_H
#include "node.h"

class CompareNode {
public:
    ~CompareNode();
    bool operator()(Node &n1, Node &n2) {
        return n1.getWeight() > n2.getWeight();
    }
};

#endif	/* COMPARENODE_H */

