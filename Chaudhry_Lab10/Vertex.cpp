#include "Vertex.h"
#include "Queue.h"

Vertex::Vertex( long aName ):
    mName(aName),
    mParent(this),
    mRank(0)
{

}

Vertex* Vertex::getParent() const
{
    return mParent;
}

long Vertex::getName() const
{
    return mName;
}

// getRoot works by creating a queue that will contain the 
// pointers to the nodes that are on the path to the root node.
// The pointers are then used to redirect the parent pointers of each path
// node to point to the root.
Vertex * Vertex::getRoot()
{
    if( mParent->getName() == mName )
    {
        return mParent;
    }
    else
    {
        Queue<Vertex*> vertexQueue;
        Vertex* root = getRoot( vertexQueue );
        while( !vertexQueue.isEmpty() )
        {
            vertexQueue.peekFront()->setParent( root );
            vertexQueue.dequeue();
        }

        return root;
    }
}

Vertex * Vertex::getRoot( Queue<Vertex*>& vertexPath )
{
    if( mParent->getName() != mName )
    {
        vertexPath.enqueue( mParent );
        return mParent->getRoot();
    }
    else
    {
        return mParent;
    }
}

void Vertex::incrementRank()
{
    mRank++;
}

void Vertex::setParent( Vertex* aNewParent )
{
    mParent = aNewParent;
}

// Union works by taking in a new vertex, checking which one has higher rank
// and then make the lower rank vertex the child of the higher rank vertex.
// If the ranks are equal to each other, then the current set's vertex root gets a higher rank.
void Vertex::vUnion( Vertex& aNewChild )
{
    Vertex* r1 = getRoot();
    Vertex* r2 = aNewChild.getRoot();

    if( r2->mRank > r1->mRank )
    {
        Vertex* temp = r1;
        r1 = r2;
        r2 = temp;
    }

    r2->setParent( r1 );
    if( r1->mRank == r2->mRank )
    {
        r1->incrementRank();
    }
}

void Vertex::vUnion( Vertex* aNewChild )
{
    Vertex* r1 = getRoot();
    Vertex* r2 = aNewChild->getRoot();

    if( r2->mRank > r1->mRank )
    {
        Vertex* temp = r1;
        r1 = r2;
        r2 = temp;
    }

    r2->setParent( r1 );
    if( r1->mRank == r2->mRank )
    {
        r1->incrementRank();
    }
}
