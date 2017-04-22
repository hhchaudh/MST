lab10: main.o PrecondViolatedExcep.o Vertex.o Edge.o Min3Heap.o Kruskal.o Prim.o
	g++ -std=c++11 -g -Wall main.o PrecondViolatedExcep.o Vertex.o Edge.o Min3Heap.o Kruskal.o Prim.o -o lab10

main.o: QNode.h QNode.hpp Queue.h Queue.hpp main.cpp
	g++ -std=c++11 -g -Wall -c main.cpp

Vertex.o: Vertex.h Vertex.cpp
	g++ -std=c++11 -g -Wall -c Vertex.cpp
    
Edge.o: Edge.h Edge.cpp
	g++ -std=c++11 -g -Wall -c Edge.cpp

PrecondViolatedExcep.o: PrecondViolatedExcep.h PrecondViolatedExcep.cpp
	g++ -std=c++11 -g -Wall -c PrecondViolatedExcep.cpp
    
Min3Heap.o: Min3Heap.h Min3Heap.cpp
	g++ -std=c++11 -g -Wall -c Min3Heap.cpp
    
Kruskal.o: Kruskal.h Kruskal.cpp
	g++ -std=c++11 -g -Wall -c Kruskal.cpp

Prim.o: Prim.h Prim.cpp
	g++ -std=c++11 -g -Wall -c Prim.cpp

clean:
	rm *.o lab10
	echo clean done