/*
 * File: SierpinskiTriangle.cpp
 * ----------------------------
 * Name: aotian
 * Section: shpp
 */

#include <iostream>
#include "gwindow.h"
#include <cmath>
using namespace std;

const double SIZE = 600; // the start size of the triangle side
const int ORDER = 8; // order of the fractal triangle


void drawTriangle (GWindow & gw, GPoint pt, double size, int order){
    double height = sqrt(3.0) * size / 2;
    double ptX = pt.getX ();
    double ptY = pt.getY ();

    //get other two points
    GPoint ptLeft(ptX - height / 2, ptY + height);
    GPoint ptRight(ptX + height / 2, ptY + height);

    //draw triangle
    gw.drawLine (pt, ptLeft);
    gw.drawLine (ptLeft, ptRight);
    gw.drawLine (ptRight, pt);

    if(order != 0){
        GPoint ptLeft(ptX - height / 4, ptY + height/2);
        GPoint ptRight(ptX + height / 4, ptY + height/2);
        drawTriangle (gw, pt, size / 2, order - 1);
        drawTriangle (gw, ptLeft, size / 2, order - 1);
        drawTriangle (gw, ptRight, size / 2, order - 1);
    }
}

int main() {
    GWindow gw (800, 600);

    //the x and y coordinates of the center of the canvas
    double px = gw.getWidth()/2;
    double py = gw.getHeight ()/2;

    //the height of the triangle
    double height = sqrt(3.0) * SIZE / 4;

    GPoint pt(px, py - height);
    drawTriangle (gw, pt, SIZE, ORDER);
    return 0;
}


