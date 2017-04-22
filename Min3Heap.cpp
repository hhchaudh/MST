#include "Min3Heap.h"
#include <iostream>

// Simple constructor that creates an empty array of size aSize
Min3Heap::Min3Heap( long aSize ) :
    mSIZE( aSize ),
    mNumNodes( 0 ),
    mHeapArray( new Edge*[aSize] )
{
    for( long i = 0; i < mSIZE; i++ )
    {
        mHeapArray[i] = nullptr;
    }
}

// The destructor, destroys the heap array
Min3Heap::~Min3Heap()
{
    for( long i = 0; i < mSIZE; i++ )
    {
        if( mHeapArray[i] )
        {
            delete mHeapArray[i];
        }
    }
    delete[] mHeapArray;
}

// bottomUpInsert simply inserts values in the heap
// without heapifying
void Min3Heap::bottomUpInsert( Edge* aEdge )
{
    mHeapArray[mNumNodes] = aEdge;
    mNumNodes++;
}

// Inserts values into the heap, and then heapifies
void Min3Heap::insert( Edge* aEdge )
{
    if(mNumNodes == mSIZE)
    {
        return;
    }
    bottomUpInsert( aEdge );
    heapifyUp( aEdge, mNumNodes - 1 );
}

// replaces the top value with the last value then heapifies
void Min3Heap::deleteMin()                                          
{
    if( mNumNodes > 0 )
    {
        mHeapArray[0] = mHeapArray[mNumNodes - 1];
        mHeapArray[mNumNodes - 1] = nullptr;
        mNumNodes--;
        heapifyDown( mHeapArray[0], 0 );
    }
}

Edge* Min3Heap::peek()
{
    if( mHeapArray[0] )
    {
        return mHeapArray[0];
    }
    else
    {
        return nullptr;
    }
}

// Heapify downward
void Min3Heap::heapifyDown( Edge* aValueToMove, const long aIndex )
{
    long smallestChildIndex = findSmallestChildIndex( aValueToMove, aIndex );

    if( smallestChildIndex > -1 )       // If smallestChildIndex returned -1, that means there are no smaller children
    {
        mHeapArray[aIndex] = mHeapArray[smallestChildIndex];

        if( isParent( smallestChildIndex ) )
        {
            heapifyDown( aValueToMove, smallestChildIndex );
        }
        else
        {
            mHeapArray[smallestChildIndex] = aValueToMove;
        }
    }
    else
    {
        mHeapArray[aIndex] = aValueToMove;
    }
}

// Heapify up
void Min3Heap::heapifyUp( Edge* aValueToMove, long aIndex )
{
    long parentIndex = getParent( aIndex );

    if( parentIndex > -1 )                  // If the parentIndex is -1, that means there is no parent
    {
        if( *aValueToMove < *mHeapArray[parentIndex] )
        {
            mHeapArray[aIndex] = mHeapArray[parentIndex];
            heapifyUp( aValueToMove, parentIndex );
        }
        else
        {
            mHeapArray[aIndex] = aValueToMove;
        }
    }
    else
    {
        mHeapArray[aIndex] = aValueToMove;
    }
}

// Use k*i < n-1 to check for parent status, k=3
bool Min3Heap::isParent( long aIndex ) const
{
    return ( ( aIndex * 3 ) < ( mNumNodes - 1 ) );
}

// Use (i-1)/k to get parent, k=3
long Min3Heap::getParent( long aIndex ) const
{
    if( aIndex > 0 )
    {
        return ( ( aIndex - 1 ) / 3 );
    }
    else
    {
        return -1;
    }
}

// Check if the aNthChild exists
bool Min3Heap::nthChildExists( long aIndex, long aNthChild ) const
{
    return ( ( 3 * aIndex + aNthChild ) < mNumNodes );
}

// Get the aNthChild
long Min3Heap::getNthChild( long aIndex, long aNthChild ) const
{
    if( nthChildExists( aIndex, aNthChild ) )
    {
        return 3 * aIndex + aNthChild;
    }
    else
    {
        return -1;
    }
}

// Calculates powers of 3
long Min3Heap::pow( const long exponent ) const
{
    if( exponent == 0 )
    {
        return 1;
    }
    else
    {
        long returnValue = 1;

        for( long i = 0; i < exponent; i++ )
        {
            returnValue *= 3;
        }

        return returnValue;
    }
}

// Check if the heap is empty
bool Min3Heap::isEmpty() const
{
    return ( mNumNodes > 0 );
}

// Find the index of the maximum value, search and compare each leaf
long Min3Heap::findMaxIndex()
{
    long maxValIndex = lastParentIndex() + 1;

    for( long i = lastParentIndex() + 2; i < mNumNodes; i++ )
    {
        if( *mHeapArray[i] > *mHeapArray[maxValIndex] )
        {
            maxValIndex = i;
        }
    }

    return maxValIndex;
}

// Find the index of the last parent
long Min3Heap::lastParentIndex()
{
    return ( ( mNumNodes - 2 ) / 3 );
}

// Find the index of the smallest child
long Min3Heap::findSmallestChildIndex( Edge* aValueToMove, long aIndex ) const
{
    if( isParent( aIndex ) )
    {
        Edge* childIndices[3];

        for( long i = 1; i <= 3; i++ )
        {
            long ithChildIndex = getNthChild( aIndex, i );

            if( ithChildIndex > -1 )
            {
                childIndices[i - 1] = mHeapArray[ithChildIndex];
            }
            else
            {
                childIndices[i - 1] = nullptr;
            }
        }

        long minValueIndex = -1;

        for( long i = 0; i < 3; i++ )
        {
            if( childIndices[i] && (*aValueToMove > *childIndices[i]) )
            {
                if( minValueIndex == -1 || ( *childIndices[i] < *childIndices[minValueIndex] ) )
                {
                    minValueIndex = i;      // minValueIndex has the potential to stay at -1 here, indicating no smaller children
                }
            }
        }

        if( minValueIndex > -1 )
        {
            return ( getNthChild( aIndex, minValueIndex + 1 ) );
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}
