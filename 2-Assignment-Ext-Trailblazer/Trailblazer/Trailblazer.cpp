/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include <map>
#include "random.h"
using namespace std;

void fillQueueByEdge(int numRows, int numCols, TrailblazerPQueue<Edge> &queue);
void fillClusterByNodes(int numRows, int numCols, Vector<Set<Loc>> &cluster);


/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */

struct Node{
	Color color;
	double distance;
	Loc parent;
};

void createGrid(Map<Loc, Node> &grid, Grid<double> &world){
	//The number of columns and rows of the world grid
	int numColums = world.nCols;
	int numRows = world.nRows;
	for(int i = 0; i < numRows; i++){
		for(int j = 0; j < numColums; j++){
			Loc newLoc = makeLoc(i, j);
			//Mark all nodes as GRAY and a condidate distance 0
			Node newNode = {GRAY, 0, newLoc};
			grid[newLoc] = newNode;
		}
	}
}

void createPath(Loc start, Loc end, Vector<Loc> &path, Map<Loc, Node> &grid){
	//fill path vector with the smallest cost distance
	while(end != start){
		path.insert(0, end);
		end = grid[end].parent;
	}
	path.insert(0, end);
}

Vector<Loc> shortestPath(Loc start, Loc end, Grid<double>& world,
			 double costFn(Loc from, Loc to, Grid<double>& world),
			 double heuristic(Loc start, Loc end, Grid<double>& world)) {
	Vector<Loc> path;
	TrailblazerPQueue<Loc> queue;
	Map<Loc, Node> grid;

	//Mark the initial node as YELLOW
	grid[start].color = YELLOW;
	queue.enqueue(start, heuristic(start, end, world));
	createGrid(grid, world);

	while(!queue.isEmpty()){
		//Dequeue the lowest-cost node from the priority-queue
		Loc currLoc = queue.dequeueMin();
		//Mark current node as green
		grid[start].color = GREEN;
		colorCell(world, currLoc, GREEN);
		if(currLoc == end) break;
		//find all neighbour nodes and mark them as YELLOW
		Loc neighbour;
		for(int i = -1; i <=  1; i++){
			for(int j = -1; j<=1; j++){
				neighbour = makeLoc(currLoc.row + i, currLoc.col + j);
				//check the grid contains neighbour node and this node hasn't been visited before
				if(grid.containsKey(neighbour) && grid[neighbour].color == GRAY){
					//current node is a parent of the neighbour node
					grid[neighbour].parent = currLoc;
					//calculate distance from neighbour to current node
					grid[neighbour].distance = grid[currLoc].distance + costFn(currLoc, neighbour, world);
					//mark neighbour node as YELLOW
					grid[neighbour].color = YELLOW;
					colorCell(world, neighbour, YELLOW);
					//add neighbour node to the queue
					queue.enqueue(neighbour, grid[neighbour].distance + heuristic(neighbour, end, world)); 
				}else if(grid.containsKey(neighbour) && grid[neighbour].color == YELLOW && grid[neighbour].distance > grid[currLoc].distance + costFn(currLoc, neighbour, world)){
					//set neighbour's parent to be current node
					grid[neighbour].parent = currLoc;
					//update neighbour's distance with new smaller distance
					grid[neighbour].distance = grid[currLoc].distance + costFn(currLoc, neighbour, world);
					//update neighbour's priority
					queue.decreaseKey(neighbour, grid[neighbour].distance + heuristic(neighbour, end, world)); 
				}
			}
		}
	}
	createPath(start, end, path, grid);
	
	return path;
}



Set<Edge> createMaze(int numRows, int numCols) {
	Set<Edge> result;
	Vector<Set<Loc>> cluster;
	TrailblazerPQueue<Edge> queue;
	
	fillQueueByEdge(numRows, numCols, queue);
	fillClusterByNodes(numRows, numCols, cluster);

	while(!queue.isEmpty()){
		Edge currentEdge = queue.dequeueMin();
		int first, second;
		for(int i = 0; i < cluster.size(); i++){
			//find the cluster of the start point of the edge
			if(cluster[i].contains(currentEdge.start)) {
				first = i;
			}
			//find the cluster of the end point of the edge
			if(cluster[i].contains(currentEdge.end)){
				second = i;
			}
		}
		if(first != second){
			//connect two clusters into one connect group
			cluster[first] += cluster[second];
			cluster.remove(second);
			result.add(currentEdge);
		}
	}
    return result;
}


void fillQueueByEdge(int numRows, int numCols, TrailblazerPQueue<Edge> &queue){
	for(int i = 0; i < numRows; i++){
		for(int j = 0; j < numCols - 1; j++){
			//the start of the edge
			Loc startNode = makeLoc(i, j);
			//the end of the edge
			Loc endNode = makeLoc(i, j + 1);
			//add new edge to the queue with random priority
			queue.enqueue(makeEdge(startNode, endNode), randomReal(0, 1));
		}
	}
	for(int i = 0; i < numCols; i++){
		for(int j = 0; j < numRows - 1; j++){
			//the start of the edge
			Loc startNode = makeLoc(j, i);
			//the end of the edge
			Loc endNode = makeLoc(j + 1, i);
			//add new edge to the queue with random priority
			queue.enqueue(makeEdge(startNode, endNode), randomReal(0, 1));
		}
	}
}


void fillClusterByNodes(int numRows, int numCols, Vector<Set<Loc>> &cluster){
	for(int i = 0; i < numRows; i++){
		for(int j = 0; j < numCols; j++){
			//find each node
			Loc currentNode = makeLoc(i,j);
			Set<Loc> set;
			//place it into its own cluster
			set.add(currentNode);
			cluster.add(set);
		}
	}
}