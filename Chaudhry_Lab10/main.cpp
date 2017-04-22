#include <iostream>
#include <fstream>
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
int main()
{
    long size;
    int iterations;
    long** adjMatrix;
    Edge** computedEdges;
    long cost;
    std::ifstream fileReader( "data.txt" );

    if( fileReader.is_open() )
    {
        fileReader >> iterations;

        // Create the matrix before passing it off to the algorithm classes.
        for( int i = 0; i < iterations; i++ )
        {
            fileReader >> size;
            adjMatrix = new long*[size];

            for( long j = 0; j < size; j++ )
            {
                adjMatrix[j] = new long[size];

                for( long k = 0; k < size; k++ )
                {
                    fileReader >> cost;
                    adjMatrix[j][k] = cost;
                }
            }

            Kruskal kruskal( adjMatrix, size );
            computedEdges = kruskal.computePath();

            long index = 0;
            std::cout << "Kruskal: ";
            while( computedEdges[index] )
            {
                std::cout << "(" << computedEdges[index]->getV1()->getName() << ", " << computedEdges[index]->getV2()->getName() << ") ";
                index++;
            }
            std::cout << std::endl;

            Prim prim( adjMatrix, size );
            computedEdges = prim.computePath();
            index = 0;
            std::cout << "Prim: ";
            while( computedEdges[index] )
            {
                std::cout << "(" << computedEdges[index]->getV1()->getName() << ", " << computedEdges[index]->getV2()->getName() << ") ";
                index++;
            }

            std::cout << std::endl;
            deleteArray( adjMatrix, size );
        }
    }
    else
    {
        std::cout << "Error reading file\n";
        exit( 1 );
    }


    return 0;
}