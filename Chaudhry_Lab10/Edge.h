/**
*	@file : Edge.h
*	@author :  Haaris Chaudhry
*	@date : Apr 17, 2017
*	Purpose: This class represents an edge
*/
#ifndef EDGE_H
#define EDGE_H

#include "Vertex.h"

class Edge
{
public:
    /**
    * Constructor for the Edge class
    * @param v1 The first vertex for the edge
    * @param v2 The second vertex for the edge
    * @param aCost the cost or weight of the edge
    * @return An edge with initialized values
    */
    Edge( Vertex* v1, Vertex* v2, long aCost );

    /**
    * Copy for the Edge class
    * @param aEdge Another edge to copy
    * @return An edge with initialized values
    */
    Edge( const Edge& aEdge );

    /**
    * Copy Constructor for the Edge class
    * @param aEdgePtr Another edge to copy
    * @return An edge with initialized values
    */
    Edge( Edge* aEdgePtr );

    /**
    * Function that returns the first vertex
    * @return A pointer to the first vertex
    */
    Vertex* getV1();

    /**
    * Function that returns the second vertex
    * @return A pointer to the second vertex
    */
    Vertex* getV2();

    /**
    * Function that returns the cost of the edge.
    * @return A pointer to the first vertex
    */
    long getCost();

   
    // The following are overloaded operaters that may be useful when comparing edges.
    bool operator==( const Edge& rhs ) const;
    bool operator>( const Edge& rhs ) const;
    bool operator>=( const Edge& rhs ) const;
    bool operator<( const Edge& rhs ) const;
    bool operator<=( const Edge& rhs ) const;
private:
    Vertex* mVertex1;               // Pointer to the first vertex of the edge
    Vertex* mVertex2;               // Pointer to the second vertex of the edge
    long mCost;                     // The cost of the edge
};
#endif // !EDGE_H
