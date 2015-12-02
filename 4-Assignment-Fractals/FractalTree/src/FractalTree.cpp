/*
 * File: FractalTree.cpp
 * ----------------------------
 * Name: aotian
 * Section: shpp
 */

#include <iostream>
#include "gwindow.h"
#include "random.h"
#include "cmath"

using namespace std;

const double SIZE = 200; // the start size of the tree branch
const int ORDER = 9; // order of the fractal tree

GPoint drawFractalTree(GWindow & gw, GPoint pt, double size, double theta, int order){
    GPoint ptMid = gw.drawPolarLine (pt, size, theta);
    if(order == 0){
        return gw.drawPolarLine (pt, size, theta);
    }else{
        double angle = 20;
        //double angle = randomReal (10,60); // use it for more fun

        drawFractalTree (gw, ptMid, size * 0.7, theta - angle, order - 1);
        drawFractalTree (gw, ptMid, size * 0.7, theta + angle, order - 1);
        return drawFractalTree (gw, pt, size, theta, order - 1 );
    }
}

int main() {
    GWindow gw (1400, 900);

    //the x and y coordinate of the bottom center of the canvas
    double px = gw.getWidth() / 2;
    double py = gw.getHeight();

    //create the point with coordinates in the bottom center of the canvas
    GPoint pt(px,py);
    pt = drawFractalTree (gw, pt, SIZE, +90, ORDER);
    return 0;
}


