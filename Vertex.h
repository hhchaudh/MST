/**
*	@file : Vertex.h
*	@author :  Haaris Chaudhry
*	@date : Apr 17, 2017
*	Purpose: This class represents an vertex
*/
#ifndef VERTEX_H
#define VERTEX_H

#include "Queue.h"

class Vertex
{
public:
    /**
    * Constructor for the Vertex class
    * @param aName The "name" of the vertex, in this case we're using integers.
    * @return A Vertex with initialized values
    */
    Vertex( long aName );

    /**
    * Function that gets the parent of the current vertex (these vertexs are designed to be in a set)
    * @return A Vertex pointer pointing to the parent
    */
    Vertex* getParent() const;

    /**
    * A function that gets the "name" of the vertex
    * @return A long integer that represents the name
    */
    long getName() const;

    /**
    * Non recursive function that gets the root of the tree that the vertex is in
    * @return A Vertex pointer pointing to the root Vertex
    */
    Vertex* getRoot();

    /**
    * A recursive function that gets the root of the tree that the vertex is in
    * @param vertexPath A queue that will contain the vertexes that are along the path to the root
    * @return A Vertex pointer pointing to the root Vertex
    */
    Vertex* getRoot( Queue<Vertex*>& vertexPath );

    /**
    * A function that increments the rank of the current vertex
    */
    void incrementRank();

    /**
    * A function that sets the parent of the current vertex
    * @param aNewParent A pointer pointing to the new parent of the vertex
    */
    void setParent( Vertex* aNewParent );

    /**
    * A function that joins two vertexes into the same tree
    * @param aNewChild The vertex that will become a child of the current vertex
    */
    void vUnion( Vertex& aNewChild );

    /**
    * A function that joins two vertexes into the same tree
    * @param aNewChild The vertex that will become a child of the current vertex
    */
    void vUnion( Vertex* aNewChild );
private:
    Vertex* mParent;            // The parent of the current vertex
    long mName;                 // The name of the current vertex
    long mRank;                 // The rank of the current vertex
};
#endif // !VERTEX_H
