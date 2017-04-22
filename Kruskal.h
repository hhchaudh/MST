/**
*	@file : Kruskal
*	@author :  Haaris Chaudhry
*	@date : Apr 17, 2017
*	Purpose: This class will take in a 2d array and use Kruskal's algorithm to calculate
        the MST
*/
#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "Edge.h"
#include "Min3Heap.h"

class Kruskal
{
public:
    /**
    * Constructor for the Prim class
    * @param aAdjMatrix The 2d adjacency matrix
    * @param aNumVertices The number of vertices represented by the adjacency matrix
    * @return A Kruskal object containing initialized variables and ready to compute the MST
    */
    Kruskal(long** aAdjMatrix, long aNumVertices);

    /**
    * Destructor for the Prim class
    */
    ~Kruskal();

    /**
    * Function that creates a set of vertices
    */
    void makeSet();

    /**
    * Function that computes the MST based on Kruskal's algorithm
    * @return An array containing Edge pointers that point to each edge in the MST
    */
    long computePath();
private:
    long mNumMaxEdges;          // The maximum possible number of edges that will be used
    long mNumVertices;          // The number of vertices represented by the adj. matrix
    long** mAdjMatrix;          // The adj matrix
    Edge** mEdgePath;           // The MST
    Edge** mEdges;              // An array that will hold all of the edges contained in the graph
    Vertex** mVertexSet;        // The set of vertices that we'll use
};
#endif // !KRUSKAL_H
