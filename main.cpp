#include <iostream>
#include <fstream>
#include "Kruskal.h"
#include "Prim.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
using namespace std;

class Timer {
private:

	timeval startTime;
        timeval endTime;

public:

	void start(){
		gettimeofday(&startTime, NULL);
	}

	double stop(){
	        long seconds, nseconds;
		double duration;

		gettimeofday(&endTime, NULL);

		seconds  = endTime.tv_sec  - startTime.tv_sec;
		nseconds = endTime.tv_usec - startTime.tv_usec;

		duration = seconds + nseconds/1000000.0;

		return duration;
	}

	void printTime(double duration){
		printf("%5.6f seconds\n", duration);
	}
};

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

void printData(const std::string algoName, double durationArray[], long costArray[])
{
    int sizes[4] = {1000, 2000, 4000, 8000};
    int sizeIndex = 0;
    double durationSum = 0;
    long costSum = 0;

    for(int i = 1; i <= 20; i++)
    {
        costSum += costArray[i - 1];
        durationSum += durationArray[i - 1];

        if(i % 5 == 0)
        {
            std::cout << "The average time for " << algoName << " at n = " << sizes[sizeIndex] << " is: "
                        << durationSum / 5.0 << std::endl;
            std::cout << "The average cost for " << algoName << " at n = " << sizes[sizeIndex++] << " is: "
                        << costSum / 5 << std::endl;
            durationSum = 0;
            costSum = 0;
        }
    }
}


int main()
{
    Timer myTimer;
    double kruskalDurations[20];
    double primDurations[20];
    long kruskalCosts[20];
    long primCosts[20];
    long** adjMatrix;
    long kComputedCost = 0;
    long pComputedCost = 0;
    long cost;
    double x;
    long sizes[4] = {1000, 2000, 4000, 8000};
    int sizeIndex = -1;


    for( int h = 1; h <= 20; h++ )
    {
        if((h-1) % 5 == 0)
        {
            sizeIndex++;
            if(sizeIndex > 0)
            {
                deleteArray( adjMatrix, sizes[sizeIndex-1] );
            }
            adjMatrix = createMatrix(sizes[sizeIndex]);
            std::cout << "*************Using size: " << sizes[sizeIndex] << " *************" << std::endl;
        }
        std::cout << "Seed = " << h << std::endl;
        srand( h );
        for( long i = 0; i < sizes[sizeIndex]; i++ )
        {
            for( long j = i; j < sizes[sizeIndex]; j++ )
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
                    cost = ( rand() % ( 4 * sizes[sizeIndex] ) + 1 );
                    adjMatrix[i][j] = cost;
                    adjMatrix[j][i] = cost;
                }
            }
        }


        Kruskal kruskal( adjMatrix, sizes[sizeIndex] );
        myTimer.start();
        kComputedCost = kruskal.computePath();
        kruskalDurations[ h - 1 ] = myTimer.stop();
        kruskalCosts[ h - 1 ] = kComputedCost;
        std::cout << "Kruskal Cost is: " << kComputedCost << "\n";

        Prim prim( adjMatrix, sizes[sizeIndex] );
        myTimer.start();
        pComputedCost = prim.computePath();
        primDurations[ h - 1 ] = myTimer.stop();
        primCosts[ h - 1 ] = pComputedCost;
        std::cout << "Prim Cost is: " << pComputedCost << "\n";
        std::cout << std::endl;

    }

    printData("Kruskal", kruskalDurations, kruskalCosts);
    printData("Prim", primDurations, primCosts);


    deleteArray( adjMatrix, 8000 );


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
