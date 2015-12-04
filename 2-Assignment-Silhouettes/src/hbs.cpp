#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
//#include "vector.h"  // for Vector
#include "gobjects.h"
#include "gbufferedimage.h"
//#include "queue.h"
#include "my_vector.h"
#include "my_queue.h"

using namespace std;

/*The minimum number of pixels need to check the silhouette*/
const int MIN_SILHOUETTE_SIZE = 100;

/*The int value of the Black color tint*/
const int BLACK_TINT = 14145495;

struct Loc{
    int row;
    int column;
};

Loc makeLoc(int row, int column){
    Loc result = {row, column};
    return result;
}

/*Fill the grid with booleans values: 1 - black pixel; 0 - white pixel;*/
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

/*Load the input file (image) and add to the window*/
void loadImage(GWindow &gw, GBufferedImage &buff){
    buff.load ("images/12.png");
    double width = buff.getWidth ();
    double height = buff.getHeight ();
    gw.setCanvasSize (width, height);
    gw.add(&buff);
}

/*Create the grid-copy of the input image*/
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

/*Fill our vector with all neigbours black points*/
void fillSpot(Grid<bool> &world, MyVector<Loc> &spot, MyQueue<Loc> queue){
    while(!queue.empty ()){
        //get the Loc from the queue
        Loc currLoc = queue.front ();
        queue.pop ();
        //check the neighbours pixel for color
        for(int row = currLoc.row - 1; row <= currLoc.row + 1; row++){
            for(int column = currLoc.column - 1; column <= currLoc.column + 1; column++){
                //if neighbour pixel is black add it to the queue and spot
                if(world.inBounds (row, column) && world.get (row, column)){
                    Loc neighbour = makeLoc (row, column);
                    queue.push (neighbour);
                    spot.push_back (neighbour);
                    world.set (row, column, false);
                }
            }
        }
    }
}

/*Find all simple silhouettes on the upload image. Print result*/
void findSilhouettes(Grid<bool> &world){
    MyVector<MyVector<Loc>> objects;
    MyQueue<Loc> queue;

    int rows = world.numRows ();
    int columns = world.numCols ();

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            if(world.get (i, j) == true){
                MyVector<Loc> spot;
                Loc newLoc = makeLoc (i, j);
                spot.push_back (newLoc);
                queue.push (newLoc);
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
