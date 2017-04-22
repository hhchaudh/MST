#include <iostream>
#include <fstream>
//#include <stdlib.h>
//#include <stdio.h>
#include "Kruskal.h"
#include "Prim.h"

void deleteArray( long** ary, long size )
{
    for( long i = 0; i < size; i++ )
    {
        delete ary[i];
    }
    delete[] ary;
}

void outputMatrix( long** matrix, long size )
{
    for( long i = 0; i < size; i++ )
    {
        for( long j = 0; j < size; j++ )
        {
            std::cout << matrix[i][j];
            if( j < size - 1 )
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

long** createMatrix( long size )
{
    long** matrix = new long*[size];

    for( long i = 0; i < size; i++ )
    {
        matrix[i] = new long[size];
    }

    return matrix;
}

int main()
{
    long size = 8000;
    int iterations;
    long** adjMatrix = new long*[size];
    long kComputedCost = 0;
    long pComputedCost = 0;
    Edge** computedEdges;
    long cost;
    double x;

    adjMatrix = createMatrix( size );

    

    for( int h = 1; h <= 5; h++ )
    {
        srand( h );
        for( long i = 0; i < size; i++ )
        {
            for( long j = i; j < size; j++ )
            {
                if( j == i )
                {
                    adjMatrix[i][j] = 0;
                    continue;
                }
                x = rand() / static_cast<double>( RAND_MAX );

                if( x >= 0 && x < 0.5 )
                {
                    adjMatrix[i][j] = 0;
                    adjMatrix[j][i] = 0;
                }
                else
                {
                    cost = ( rand() % ( 4 * size ) + 1 );
                    adjMatrix[i][j] = cost;
                    adjMatrix[j][i] = cost;
                }
            }
        }

        Kruskal kruskal( adjMatrix, size );
        kComputedCost = kruskal.computePath();
        std::cout << "\nKruskal Cost is: " << kComputedCost << "\n";

        Prim prim( adjMatrix, size );
        pComputedCost = prim.computePath();
        std::cout << "\Prim Cost is: " << pComputedCost << "\n";
    }

    //outputMatrix( adjMatrix, size );

    

    deleteArray( adjMatrix, size );

    //std::ifstream fileReader( "data.txt" );

    //if( fileReader.is_open() )
    //{
    //    fileReader >> iterations;

    //    // Create the matrix before passing it off to the algorithm classes.
    //    for( int i = 0; i < iterations; i++ )
    //    {
    //        fileReader >> size;
    //        adjMatrix = new long*[size];

    //        for( long j = 0; j < size; j++ )
    //        {
    //            adjMatrix[j] = new long[size];

    //            for( long k = 0; k < size; k++ )
    //            {
    //                fileReader >> cost;
    //                adjMatrix[j][k] = cost;
    //            }
    //        }

    //        Kruskal kruskal( adjMatrix, size );
    //        computedEdges = kruskal.computePath();

    //        long index = 0;
    //        std::cout << "Kruskal: ";
    //        while( computedEdges[index] )
    //        {
    //            std::cout << "(" << computedEdges[index]->getV1()->getName() << ", " << computedEdges[index]->getV2()->getName() << ") ";
    //            index++;
    //        }
    //        std::cout << std::endl;

    //        Prim prim( adjMatrix, size );
    //        computedEdges = prim.computePath();
    //        index = 0;
    //        std::cout << "Prim: ";
    //        while( computedEdges[index] )
    //        {
    //            std::cout << "(" << computedEdges[index]->getV1()->getName() << ", " << computedEdges[index]->getV2()->getName() << ") ";
    //            index++;
    //        }

    //        std::cout << std::endl;
    //        deleteArray( adjMatrix, size );
    //    }
    //}
    //else
    //{
    //    std::cout << "Error reading file\n";
    //    exit( 1 );
    //}


    return 0;
}