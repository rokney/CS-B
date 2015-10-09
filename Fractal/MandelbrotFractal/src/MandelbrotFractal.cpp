#include <iostream>
#include "console.h"
#include "gwindow.h"
#include "gobjects.h"

using namespace std;

//the count of the iteration
const int MAX_ITERATIONS = 40000;

// min and max values of the real numbers
const double MIN_REAL = -2.0;
const double MAX_REAL = 0.5;

// min and max values of the imaginary numbers
const double MIN_IMAGINARY = -1.25;
const double MAX_IMAGINARY = 1.25;

void drawMondelbrotFractal(GWindow &gw, double real, double imag){
    int i = 0; // iterations
    double x, y; // x and y coordinate of the points to draw on canvas
    double cr = real, ci = imag;
    double zr = 0.0, zi = 0.0;
    //double arg = zr * zr + zi * zi;
    while (zr * zr + zi * zi < 4 && i < MAX_ITERATIONS)
    {
        zr = (cr * cr) - (ci * ci) + real;
        zi = (2 * cr * ci) + imag;
        cr = zr;
        ci = zi;
        //arg = zr * zr + zi * zi;
        //convert to x and y coordinate of the canvas
        x = gw.getWidth ()*(zr - MIN_REAL) / (MAX_REAL - MIN_REAL);
        y = gw.getHeight ()*(1 - (zi - MIN_IMAGINARY) / (MAX_IMAGINARY - MIN_IMAGINARY));
        i++;
    }
    if(i == MAX_ITERATIONS){
        gw.drawOval (x, y, 1, 1);
    }
}

double getStep(GWindow &gw){
    double step = 0.0;
    double width = gw.getWidth ();

    //calculate the value of step by the axises
    if(MIN_REAL >= 0 && MAX_REAL >= 0){
        step = (MIN_REAL+MAX_REAL)/width;
    }else if(MIN_REAL < 0 && MAX_REAL >= 0){
        step = (MAX_REAL-MIN_REAL)/width;
    }else{
        step = (-MIN_REAL + MAX_REAL)/width;
    }
    return step;
}

int main(){
    GWindow gw(1000, 1000);
    gw.setRepaintImmediately (false);

    double step = getStep(gw);

    for (double imaginary = MAX_IMAGINARY; imaginary >= MIN_IMAGINARY; imaginary -= step)
    {
        for (double real = MIN_REAL; real <= MAX_REAL; real += step)
        {
            drawMondelbrotFractal(gw, real, imaginary);
        }
    }

    gw.repaint ();
    return 0;
}
