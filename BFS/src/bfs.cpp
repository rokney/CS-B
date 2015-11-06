#include <iostream>
#include "console.h"
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "queue.h"
#include "random.h"
#include <algorithm>
using namespace std;



void calculatePath(Vector<int> &path, bool* visited){
    vector<int> result;
    int finishNode = getInteger ("Enter the finish node : ");
    if(!visited[finishNode]){
        cout << "No path.." << endl;
    }else{
        cout << "Calculate the smallest path from start to finish node..." << endl;
        while(finishNode != -1){
            result.push_back (finishNode);
            finishNode = path[finishNode];
        }
        reverse(result.begin (), result.end ());

        cout << "Start move frome the node [" << result[0] << "]. ";
        for(int i = 1; i < result.size (); i++){
            cout << "Go to node [" << result[i] << "]. ";
        }
        cout << "Finish." << endl;
    }
}

int main() {
    Queue<int> queue;
    int numNodes = randomInteger (5, 9);
    Vector<int> path(numNodes);
    bool nodes [numNodes][numNodes];
    bool visited[numNodes];

    //Create the random adjacency matrix
    for(int i = 0; i < numNodes; i++){
        cout << "Node [" << i << "] - > [";
        for(int j = 0; j < numNodes; j++){
            if(j == i){
                nodes[i][j] = false;
            }else{
                nodes[i][j] = randomBool ();
            }
            cout << nodes[i][j] << " ";
        }
        cout << "]" << endl;
    }

    //Choose the start node for BFS
    int startNode = randomInteger (0, numNodes - 1);
    //add start node to the queue
    queue.add (startNode);
    //check start node as visited
    visited[startNode] = true;
    //check start node for future create the path between itself and another node
    path[startNode] = -1;

    cout << "Start search from [" << startNode << "] node." << endl;
    while(!queue.isEmpty ()){
        //get the index of the first node in the queue
        int currNode = queue.dequeue ();
        cout << "Got to [" << currNode<< "] node." << endl;
        for(int i = 0; i < numNodes; i++){
            //if current node has the edge with other node, and other node wasn't visited
            if(nodes[currNode][i] && !visited[i]){
                cout << "Add [" << i << "] node." << endl;
                //add new node to the queue
                queue.add(i);
                //check this node as visited
                visited[i] = true;
                //add this node to the path vector
                path[i] = currNode;
            }
        }
    }

    calculatePath(path, visited);

    return 0;
}
