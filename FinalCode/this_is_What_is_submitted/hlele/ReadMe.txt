ITCS 6113 : Data Structures and Algorithm.
Programming Assignment No 2: Dijkstra Algorithms for finding shortes Path.
Developer: Harshad Lele.
UNCC ID: 800904877
Email ID: hlele@uncc.edu
Date: 04/25/2016

Programming Language used - C++

Information about IDE
Code::Blocks 13:12
SDK Version: 1.19.0

C++ Compiler Information 
GNU GCC Compiler 
C++ copiler - mingw32-g++.exe
Linker for dynamic libs - mingw32-g++.exe
Linker for static libs - ar.exe
Enabled - have g++ follow c++11ISO C++ language standard option in Code::Blocks

Program design and structure used :

There are 3 classes in the program.

	1)Edge:
		Member Variables:
		string destination ->name of destination node.
		float weight -> time to travel from source to destination.
		int statusEdge -> to denote whether edge is Up or Down. (Initially status of all the edges are up)
		
	2)Vertex:
		string name -> Name of the Vertex.
		float value -> Value of each Vertex. (While finding shortest path in Dijkstra's this is being set to 10000 - consider it as Infinity)
		string prev -> Name of the previous Vertex (Predecesor)
		int visited -> status to indicate whether this Vertex has been visited or not 1=Visited, 0= Not visited.
		int statusVertex ->TO inidicate whether Vertex is Up or Down. (Initially status of the Vertex is Up)
		vector<Edge> adjlist -> Adjacency list of edges for each Vertex.
		vector<Vertex*> priorityQueue -> Vertex in the priority queue are stored in this vector
		
	3)Graph
		typedef map<string, Vertex *> vmap -> All the Vertex objects of the graphs are maped with the names.(Map Data Structure)
		All the other functions working are explained in the source code file in the comments. However, some of the important functions are :
		
		void buildminHeap(vector<Vertex*>& ,float );     	Builds initial Min Heap.
        Vertex extractMin(vector<Vertex*>&);			 	Extracts the minimum in the Heap
		void reachable(); 									Check for reachability and prints the vertex those are reachable in the Graph
		void dijkstras(const string& , const string& );     Core of the program. Find the shortest distance betwenn two Vertex
		int parent(int );                               	Prints the whole Graph in the specified order
	

More details about the Dijkstra's Implementation:

	* Binary min heap is used for building priority queue. Priority Queue is built with the vector of pointers of Vertex.
	* buildminHeap function is called only once for initial bulding of min heap which takes O(V) time.
	* After building min heap again all the other functions takes O(log V) time, 
	  decreaseKey function restores min heap order after extraction of min element form the queue in O(log V) time.
	* If path could not be reched then it will show destination name and maximum distance i.e. infinity - 10000 - which is considered as path could not be reached.
	  
Details about 'rechable' implementation:

	* It works sort of DFS, however here DFS is applied on all the vertex in the graph.
	* For each Vertex, its adjacency list is travelled and recursive function is being called on the each vertex in the adj list untill all the reachable vertex are covered for that specific vertex.
	* Also, if the new Vertex is found then it is added in the Vector, which keeps track of reachable Vertexes.
	
	Running time for reachable  = Total Number of vertex * (Running time of DFS on each Vertex) 
								= V*(V+E)


BreakDown of the files:
Only 2 files 
1. ShortestPath.cpp 
2. Readme

How to run the program:
This program requires 1 command line argument
Argument1 - file name in .txt format.

On windows:
Please use Code::Blocks IDE for getting optimum results. Tried and tested using Code::Blocks. 
I can not guaranttee whether this program will work fine on other IDE's.

On Ubuntu/Linux:
g++ -c ShortestPath.cpp
g++ -o whateverObjectName ShortestPath.objects
./whateverObjectName .txt file name.

When this program might fail:
1. If wights of the edges are negative.
2. If initial weights of the vertexes are greater than the infinity value considered in the program which is 10000.
3. I have tested and ran program extensively on Code::Blocks IDE. If other IDE is used to compile the program some errors might come.

Thank You for Reading!

==============================================================END=========================================================================================================




