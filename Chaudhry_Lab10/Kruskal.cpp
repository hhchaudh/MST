/**
*	@file : Kruskal.cpp
*	@author :  Haaris Chaudhry
*	@date : Apr 17, 2017
*	Purpose: The implementation of the Kruskal class
*/
#include "Kruskal.h"

Kruskal::Kruskal( long** aAdjMatrix, long aNumVertices ) :
    mNumVertices( aNumVertices ),
    mVertexSet( new Vertex*[aNumVertices] ),
    mAdjMatrix(aAdjMatrix)
{
    makeSet();                                                      // Make the set of vertices
    mNumMaxEdges = ( aNumVertices * (aNumVertices - 1 ) ) / 2;      // Check what the max num of edges will be

    mEdgePath = new Edge*[mNumVertices];                            // Create the MST array
    for( long i = 0; i < mNumVertices; i++ )                        // Initialize the MST array
    {
        mEdgePath[i] = nullptr;
    }

    mEdges = new Edge*[mNumMaxEdges];                               // Create the array that will hold all of the edges
    for( long i = 0; i < mNumMaxEdges; i++ )                        // And then initialize it
    {
        mEdges[i] = nullptr;
    }


    // Place edges into the mEdges array
    long edgeIndex = 0;                                             
    for( long i = 0; i < mNumVertices; i++ )
    {
        for( long j = 0; j < i; j++ )
        {
            if( mAdjMatrix[i][j] > 0 )
            {
                if( i < j )
                {
                    mEdges[edgeIndex] = new Edge( mVertexSet[i], mVertexSet[j], mAdjMatrix[i][j] );
                }
                else
                {
                    mEdges[edgeIndex] = new Edge( mVertexSet[j], mVertexSet[i], mAdjMatrix[i][j] );
                }
                edgeIndex++;
            }
        }
    }
}

// The destructor insures the destruction of all vertices and edges that were taken out from the heap.
Kruskal::~Kruskal()
{
    for( long i = 0; i < mNumVertices; i++ )
    {
        delete mVertexSet[i];
        delete mEdgePath[i];
    }

    delete[] mVertexSet;
    delete[] mEdgePath;
    delete[] mEdges;
}

// The function that creates a set of vertices
void Kruskal::makeSet()
{
    for( long i = 0; i < mNumVertices; i++ )
    {
        mVertexSet[i] = new Vertex( i );
    }
}

// The Kruskal algorithm computer.
Edge** Kruskal::computePath()
{
    Min3Heap edgeHeap( mNumMaxEdges );                              // Create a heap that will sort all of the edges

    for( long i = 0; i < mNumMaxEdges; i++ )                        // Insert all of the edges
    {
        if( mEdges[i] )
        {
            edgeHeap.insert( mEdges[i] );
        }
    }

    // While we still have edges in the heap and we havent hit numvertices-1 edges, keep going
    long edgeCounter = 0;
    while( edgeHeap.peek() && ( edgeCounter != mNumVertices - 1 ) )
    {
        Edge* e = edgeHeap.peek();                  // Store the edge at the top of the heap

        // Get the roots of the vertices of this new edge
        Vertex* root1 = e->getV1()->getRoot();      
        Vertex* root2 = e->getV2()->getRoot();

        // Vertices are tree nodes with a value and a parent pointer, make sure that their roots arent the same
        // If the roots arent the same, add the edge to the MST, increase the edge counter, and make these new vertices part of the same set
        if( root1 != root2 )
        {
            mEdgePath[edgeCounter] = e;
            edgeCounter++;
            e->getV1()->vUnion( e->getV2() );
        }

        // Delete the min edge of the heap.
        edgeHeap.deleteMin();

        // Return the edgepath if we reach mNumVertices -1 == edgeCounter
        if( edgeCounter == mNumVertices - 1 )
        {
            return mEdgePath;
        }
    }
}
