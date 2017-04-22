/**
*	@file : Prim.cpp
*	@author :  Haaris Chaudhry
*	@date : Apr 17, 2017
*	Purpose: The implementation of the Prim class
*/
#include "Prim.h"

Prim::Prim( long ** aAdjMatrix, long aNumVertices ):
    mAdjMatrix(aAdjMatrix),
    mNumVertices(aNumVertices),
    mVertexSet(new Vertex*[aNumVertices]),
    mUsedVertices(new bool[aNumVertices])
{
    makeSet();                                                  // create a set of vertices that we'll pass to edges
    mNumMaxEdges = ( aNumVertices * ( aNumVertices - 1 ) ) / 2; // see what the maximum number of edges will be
    mEdgePath = new Edge*[mNumVertices];                        // create and initialize the arrays that will hold the MST and the vertices that have been used
    for( long i = 0; i < mNumVertices; i++ )
    {
        mEdgePath[i] = nullptr;
        mUsedVertices[i] = false;
    }

}

// The destructor ensures that all edges that were taken from the heap are destroyed as well as
// all of the vertexes that we created
Prim::~Prim()
{
    for( long i = 0; i < mNumVertices; i++ )
    {
        if( mVertexSet[i] )
        {
            delete mVertexSet[i];
        }

        if( mEdgePath[i] )
        {
            delete mEdgePath[i];
        }
    }

    delete[] mVertexSet;
    delete[] mEdgePath;
}

// Create vertexes that can be used by the edges.
void Prim::makeSet()
{
    for( long i = 0; i < mNumVertices; i++ )
    {
        mVertexSet[i] = new Vertex( i );
    }
}

// Use prim's algorithm
long Prim::computePath()
{
    Min3Heap edgeHeap( mNumMaxEdges );
    long totalCost = 0;

    // First start with vertex 0 and create edges that are incident from vertex 0, add to the heap
    for( long j = 1; j < mNumVertices; j++ )
    {
        long cost = mAdjMatrix[0][j];
        if( cost > 0 )
        {
            edgeHeap.insert( new Edge( mVertexSet[0], mVertexSet[j], cost ) );
        }
    }

    // Vertex 0 was used, so we'll make sure to note that here
    mUsedVertices[0] = true;
    // We used a vertex, let's make sure that we count how many we've used.
    long numVerticesUsed = 1;

    // Keep doing this until we've used all vertices.
    while( edgeHeap.peek() && numVerticesUsed != mNumVertices )
    {
        long index = numVerticesUsed - 1;           // The index to use in mEdgePath is one behind the number of used vertices
        mEdgePath[index] = edgeHeap.peek();         // Add the lowest cost edge to the MST
        edgeHeap.deleteMin();                       // Remove said edge from the heap

        long vertexIndex = mEdgePath[index]->getV2()->getName();        // Check the values of each vertex
        long vertexIndex2 = mEdgePath[index]->getV1()->getName();

        while( mUsedVertices[vertexIndex] && mUsedVertices[vertexIndex2] )  // If both vertices are part of the used vertices, then we need to get a new edge.
        {
            delete mEdgePath[index];
            mEdgePath[index] = edgeHeap.peek();
            edgeHeap.deleteMin();

            vertexIndex = mEdgePath[index]->getV2()->getName();
            vertexIndex2 = mEdgePath[index]->getV1()->getName();
        }

        totalCost += mEdgePath[index]->getCost();

        for( long j = 0; j < mNumVertices; j++ )                            // Cycle through the vertices that are incident to the new vertex that we've added.
        {
            if( mUsedVertices[j] )                                          // Don't add edges to the heap where the second vertex belongs to the mUsedVertices set
            {
                continue;
            }
                    
            long cost = mAdjMatrix[vertexIndex][j];                         // 
            if( cost > 0 )  
            {
                edgeHeap.insert( new Edge( mVertexSet[vertexIndex], mVertexSet[j], cost ) );
            }
        }
        mUsedVertices[vertexIndex] = true;
        numVerticesUsed++;
    }

    return totalCost;

}
