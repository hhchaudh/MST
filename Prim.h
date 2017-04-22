/**
*	@file : Prim.h
*	@author :  Haaris Chaudhry
*	@date : Apr 17, 2017
*	Purpose: This class will take in a 2d array and use Prim's algorithm to calculate
                the MST
*/

#ifndef PRIM_H
#define PRIM_H

#include "Edge.h"
#include "Min3Heap.h"

class Prim
{
public:
    /**
    * Constructor for the Prim class
    * @param aAdjMatrix The 2d adjacency matrix
    * @param aNumVertices The number of vertices represented by the adjacency matrix
    * @return A Prim object containing initialized variables and ready to compute the MST
    */
    Prim( long** aAdjMatrix, long aNumVertices );

    /**
    * Destructor for the Prim class
    */
    ~Prim();

    /**
    * A function that creates a set of vertices based off of the adjacency matrix
    */
    void makeSet();

    /**
    * Function that computes the MST based on Prim's algorithm
    * @return An array containing Edge pointers that point to each edge in the MST in order starting at vertex 0
    */
    long computePath();
private:
    long mNumMaxEdges;      // The maximum possible number of edges that will be used
    long mNumVertices;      // The number of vertices represented by the adj. matrix
    long** mAdjMatrix;      // The adj matrix
    Edge** mEdgePath;       // The MST
    Vertex** mVertexSet;    // The set of vertices that we'll use
    bool* mUsedVertices;    // An array that keeps track of which vertices we've used.
};
#endif // !PRIM_H
