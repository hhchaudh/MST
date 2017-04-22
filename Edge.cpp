#include "Edge.h"

Edge::Edge( Vertex* v1, Vertex* v2, long aCost ):
    mVertex1(v1),
    mVertex2(v2),
    mCost(aCost)
{
}

Edge::Edge( const Edge& aEdge )
{
    mVertex1 = aEdge.mVertex1;
    mVertex2 = aEdge.mVertex2;
    mCost = aEdge.mCost;
}

Edge::Edge( Edge * aEdgePtr )
{
    mVertex1 = aEdgePtr->mVertex1;
    mVertex2 = aEdgePtr->mVertex2;
    mCost = aEdgePtr->mCost;
}

Vertex * Edge::getV1()
{
    return mVertex1;
}

Vertex * Edge::getV2()
{
    return mVertex2;
}

long Edge::getCost()
{
    return mCost;
}

bool Edge::operator==( const Edge & rhs ) const
{
    return mCost == rhs.mCost;
}

bool Edge::operator>( const Edge & rhs ) const
{
    return mCost > rhs.mCost;
}

bool Edge::operator>=( const Edge & rhs ) const
{
    return mCost >= rhs.mCost;
}

bool Edge::operator<( const Edge & rhs ) const
{
    return mCost < rhs.mCost;
}

bool Edge::operator<=( const Edge & rhs ) const
{
    return mCost <= rhs.mCost;
}
