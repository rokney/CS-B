#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "gobjects.h"
#include "gbufferedimage.h"
#include "set.h"
#include "queue.h"

using namespace std;

const int MIN_SILHOUETTE_SIZE = 100;
const int BLACK_TINT = 14145495;

struct Loc{
    int row;
    int column;
};

Loc makeLoc(int row, int column){
    Loc result = {row, column};
    return result;
}


void fillGrid(Grid<bool> &result, GBufferedImage &buff, double width, double height){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            //check the coloor of the pixels
            if(buff.getRGB (j, i) <= BLACK_TINT){
                //if it is black pixel - set true
                result.set (i, j, true);
            }else{
                //if it's white pixel - set false
                result.set(i, j, false);
            }
        }
    }
}

void loadImage(GWindow &gw, GBufferedImage &buff){
    buff.load ("images/12.png");
    double width = buff.getWidth ();
    double height = buff.getHeight ();
    gw.setCanvasSize (width, height);
    gw.add(&buff);
}

Grid<bool> createGrid(GWindow &gw){
    GBufferedImage buffImage;
    loadImage(gw, buffImage);

    //The width and height parameters of the upload image
    double width = buffImage.getWidth ();
    double height = buffImage.getHeight ();

    //create grid with height and width parameters of the upload image
    Grid<bool> result(height, width);
    fillGrid(result, buffImage, width, height);
    return result;

}

void fillSpot(Grid<bool> &world, Vector<Loc> &spot, Queue<Loc> queue){
    while(!queue.isEmpty ()){
        //get the Loc from the queue
        Loc currLoc = queue.dequeue ();
        //check the neighbours pixel for color
        for(int row = currLoc.row - 1; row <= currLoc.row + 1; row++){
            for(int column = currLoc.column - 1; column <= currLoc.column + 1; column++){
                //if neighbour pixel is black add it to the queue and spot
                if(world.inBounds (row, column) && world.get (row, column)){
                    Loc neighbour = makeLoc (row, column);
                    queue.add (neighbour);
                    spot.push_back (neighbour);
                    world.set (row, column, false);
                }
            }
        }
    }
}

void findSilhouettes(Grid<bool> &world){
    Vector<Vector<Loc>> objects;
    Queue<Loc> queue;

    int rows = world.numRows ();
    int columns = world.numCols ();

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            if(world.get (i, j) == true){
                Vector<Loc> spot;
                Loc newLoc = makeLoc (i, j);
                spot.push_back (newLoc);
                queue.enqueue (newLoc);
                fillSpot(world, spot, queue);
                //check the size of the new spot
                if(spot.size () >= MIN_SILHOUETTE_SIZE){
                    objects.push_back (spot);
                }
            }
        }
    }
    cout << "There are(is) " << objects.size () << " human silhouette(s) on this image." << endl;
}

int main() {
    GWindow gw;
    Grid<bool> world = createGrid(gw);
    findSilhouettes(world);
    return 0;
}
