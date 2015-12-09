/* 
 * File:   node.h
 * Author: rokne
 *
 * Created on 13 октября 2015 г., 10:42
 */

#ifndef NODE_H
#define	NODE_H

class Node {
private:
    char ch;
    double weight;
    int index;
    int parent;
    bool branch;
public:
    Node();
    Node(char, double, int);
    virtual ~Node();
    void setChar(char);
    void setWeight(double);
    void setIndex(int);
    void setParent(int);
    void setBranch(bool);
    char getChar();
    double getWeight();
    int getIndex();
    int getParent();
    bool getBranch();
};



#endif	/* NODE_H */

