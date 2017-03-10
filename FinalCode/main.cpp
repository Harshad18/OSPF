/*
 * Shortes Path in the Network using Dijkstra's Source Code
 * Developer : Harshad Lele.
 * Date : 04/25/2016
 * Time : 3:15
 */

#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<list>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<sstream>
#include<math.h>
#include<stdlib.h>
#include <algorithm>

#define INFINITY1 10000
#define nil 0
#define up 1
#define down 0
#define no 0
#define yes 1

using namespace std;

class Edge
{
public:
    Edge(){};
    Edge(string s, float w)
    {
        destination = s;
        weight = w;
        statusEdge = up;
    };
    string getDestination(){return destination;};
    float getWeight(){return weight;};
    float setWeight(float w){weight=w;};
    int statusEdge;
private:
    string destination;
    float weight;

};

class Vertex{
public:
    Vertex(){};
    Vertex(string s)
    {
        name=s;
        statusVertex = up;
    };
    vector<Edge> adjlist;               // Adjacency list of edges for particular Vertex
    vector<Vertex*> priorityQueue;      // Vertex in the priority queue are stored in this vector
    string name;
    float value;
    string prev;
    int visited;
    int statusVertex;
};
class Graph
{
    public:
        typedef map<string, Vertex *> vmap;
        vmap mygraph;
        Vertex* getVertex(const string &name);          // Checking if the Vertex if already there in the map if not it Adds new Vertex in the Graph
        void addEdge_first_time(const string& , const string& , float ); // After reading data for the first time through the file this function constructs initial Graph
        void print();                       // Prints the graph
        void dijkstras(const string& , const string& ); // Finds the shortest path if Destination and Source are given
        int left_heap(int );                            // Left child cal.
        int right_heap(int );                           // Right child cal.
        int parent(int );                               // Calculates parent
        void min_heapify(vector<Vertex*>& ,int ,int );  // Restores heap order
        void buildminHeap(vector<Vertex*>& ,float );    // Builds initial Min Heap.
        Vertex extractMin(vector<Vertex*>&);            // Extracts minimum element in the heap
        void reset();                                   // Sets all the Vertex Value to infinity and predecessors value to nil
        void swapValue(vector<Vertex*>&);                   // Swaps the value
        void addEdge(const string&, const string&, float);  // Adds the new edge in the graph is not already present this edge will be directional edge
        void decreaseKey(vector<Vertex*>&,int,float);       // restores heap order in log(n) time
        void printPath(string);                             // Prints shortest path
        void deleteEdge(const string&, const string&);         // Deletes edge
        void downEdge(const string&, const string&);        // Changes edge status to Down
        void upEdge(const string&, const string&);          // Changes edge status to Up
        void vertexDown(const string&);                     // Changes Vertex status to Down
        void vertexUp(const string&);                       //// Changes Vertex status to Up
        void reachable();                                   // Prints out names of reachable Vertexes in the Graphs from all the Vertex
        void checkAndUpdate(Vertex*,vector<Vertex*>&);      // Recursive function which helps to locate reachable Vertexes
};

void Graph::reachable()
{
    map<string,int> Reachable_Data;
    vmap::iterator itr = mygraph.begin();
    vmap::iterator iter = mygraph.begin();
    vector<Vertex*> VisitedNodes;               // vector of reachable nodes
    for (; iter != mygraph.end(); ++iter)
    {
        vmap::iterator iter1 = mygraph.begin();
        VisitedNodes.clear();
        for (; iter1 != mygraph.end(); ++iter1)
        {
            Vertex *statusNode = iter1->second;
            statusNode->visited = no;
        }
        Vertex *node = iter->second;

        if(node->statusVertex == up)            // checks for Vertex status
        {
            cout <<node->name << endl;
            node->visited = yes;
            checkAndUpdate(node,VisitedNodes);      // recursive function which assists reachable function
            for(int i=0;i<VisitedNodes.size();i++)
            {
                Reachable_Data.insert(make_pair(VisitedNodes[i]->name,i));
            }
            map<string,int>::iterator reach = Reachable_Data.begin();   // logic for sorting the vertex names
            for(;reach != Reachable_Data.end();++reach)
            {
                cout << "  " << reach->first << endl;
            }
            Reachable_Data.clear();
        }
        else
            cout << endl;
    }
}

void Graph::checkAndUpdate(Vertex* CurrentVertex, vector<Vertex*>&finalNodes)
{
    vector<Edge> &print1 = CurrentVertex->adjlist;
    vmap::iterator itr = mygraph.begin();
    vmap::iterator iter1 = mygraph.begin();

    for(int i=0;i<print1.size();i++)
    {
        if( print1[i].statusEdge == up )                    // checks the status of the Edge
        {
            itr=mygraph.find(print1[i].getDestination());
            Vertex *newNode = itr->second;
            if(newNode->visited == no)
            {
                if (newNode->statusVertex == up)            // checks for Vertex status
                {
                    newNode->visited =yes;
                    (finalNodes).push_back(newNode);         // If edge and Vertex are up the adds to final reachable vector
                    checkAndUpdate(newNode,finalNodes);
                }
            }
        }
    }
}

void Graph::vertexUp(const string&from)
{
    vmap::iterator itr = mygraph.begin();
    itr = mygraph.find(from);
    Vertex *final1 = itr->second;
    final1->statusVertex = up;
}
void Graph::vertexDown(const string&from)
{
    vmap::iterator itr = mygraph.begin();
    itr = mygraph.find(from);
    Vertex *final1 = itr->second;
    final1->statusVertex = down;

}
void Graph::upEdge(const string& from, const string& to)
{
    vmap::iterator itr = mygraph.begin();
    itr = mygraph.find(from);
    Vertex *final1 = itr->second;

    vector<Edge>&print1 = final1->adjlist;
    for (int i=0;i<print1.size();i++)
    {
        if (print1[i].getDestination() == to)
        {
            print1[i].statusEdge = up;
        }
    }

}
void Graph::downEdge(const string& from, const string& to)
{
    vmap::iterator itr = mygraph.begin();
    itr = mygraph.find(from);
    Vertex *final1 = itr->second;

    vector<Edge>&print1 = final1->adjlist;
    for (int i=0;i<print1.size();i++)
    {
        if (print1[i].getDestination() == to)
        {
            print1[i].statusEdge = down;
        }
    }

}
void Graph::deleteEdge(const string& from, const string& to)
{
    vmap::iterator itr = mygraph.begin();
    itr = mygraph.find(from);
    Vertex *final1 = itr->second;
    int deleteIndex;
    vector<Edge>&print1 = final1->adjlist;

    for (int i=0;i<print1.size();i++)
    {
        if (print1[i].getDestination() == to)
        {
            deleteIndex = i;
        }
    }
    print1.erase(print1.begin() + deleteIndex);
}

void Graph::addEdge(const string& from, const string& to, float cost)
{
    Vertex *u=getVertex(from);
    Vertex *v=getVertex(to);
    int edgeUpdated=0;
    vector<Edge> &print1 = u->adjlist;

    for (int i=0;i<print1.size();i++)
    {
        if(print1[i].getDestination() == to)
        {
            print1[i].setWeight(cost);
            return ;
        }
    }
    Edge *E1;
    E1 = new Edge(to,cost);
    (u->adjlist).push_back(*E1);
}

void Graph::addEdge_first_time(const string& from, const string& to, float cost)
{
    Vertex *u=getVertex(from);
    Vertex *v=getVertex(to);
    Edge *E1;
    Edge *E2;
    E1 = new Edge(to,cost);
    E2 = new Edge (from,cost);
    (u->adjlist).push_back(*E1);
    (v->adjlist).push_back(*E2);
}

Vertex* Graph::getVertex(const string &name)
{
    vmap::iterator itr=mygraph.begin();
    itr=mygraph.find(name);
    if(itr==mygraph.end())
    {
        Vertex *v;
        v= new Vertex(name);
        mygraph[name]=v;
        return v;
    }
    return itr->second;
}

void Graph::print()
{
    vector<string>finalPrint;
    map<string,Edge> Print_Data;

    vmap::iterator iter = mygraph.begin();
    vmap::iterator iter1 = mygraph.begin();

    for (; iter != mygraph.end(); ++iter)
    {
        Vertex *final1 = iter->second;
        if(final1->statusVertex == up)
        {
            cout << '\n' << (iter->first) << endl;
            vector<Edge> &print1 = final1->adjlist;

            for(int i=0;i<print1.size();i++)
            {
                string getData = print1[i].getDestination();
                Print_Data.insert(make_pair(getData,print1[i]));
            }

            map<string,Edge>::iterator printing = Print_Data.begin();
            vmap::iterator iter8 = mygraph.begin();
            for(;printing != Print_Data.end();++printing)
            {
                string printName =  printing->first ;
                Edge finalPrint1 = printing->second;
                if(finalPrint1.statusEdge == up)
                {
                    cout << "  "  << printing->first << "  " << finalPrint1.getWeight() << endl;
                }
                else
                    cout << "  "  << printing->first << "  " << finalPrint1.getWeight() <<" Down" << endl;
            }
            Print_Data.clear();
        }
        else
        {
            cout << '\n' << (iter->first) << "  " << "Down"<<endl;
            vector<Edge> &print1 = final1->adjlist;

            for(int i=0;i<print1.size();i++)
            {
                string getData = print1[i].getDestination();
                float getWeight = print1[i].getWeight();
                Print_Data.insert(make_pair(getData,print1[i]));
            }

            map<string,Edge>::iterator printing = Print_Data.begin();
            vmap::iterator iter8 = mygraph.begin();
            for(;printing != Print_Data.end();++printing)
            {
                string printName =  printing->first ;
                Edge finalPrint1 = printing->second;
                if(finalPrint1.statusEdge == up)
                {
                     cout << "  "  << printing->first << "  " << finalPrint1.getWeight() << endl;
                }
                else
                    cout << "  "  << printing->first << "  " << finalPrint1.getWeight() <<" Down" << endl;
            }
            Print_Data.clear();
        }
    }
}

void Graph::buildminHeap(vector<Vertex*> &A, float n )      // Builds min heap
{
    int i = (n/2)-1;
    for(; i >= 0; i--)
    {
        min_heapify(A,i,n);                                 // restores heap order
    }
}

void Graph::min_heapify(vector<Vertex*> &A, int i, int n)       // restores heap order
{

    int l = ( 2*i +1);
    int r = ( 2*i + 2 );
    int smallest;
    if ( (l <= n) && (A[l]->value < A[i]->value) )
    {
        smallest = l;
    }
    else
    {
        smallest = i;
    }
    if ((r<n) && (A[r]->value < A[smallest]->value))
    {
        smallest = r;
    }
    if(smallest != i)
    {
        Vertex* temp;
        temp = A[i];
        A[i] = A[smallest];
        A[smallest] = temp;
        min_heapify(A,smallest,n);
    }
}

void Graph::swapValue(vector<Vertex*>&A)        // swaps the min element with the last element
{
        Vertex *swap_v;
        swap_v = A[A.size()-1];
        swap_v = A[0];
        A[0] = A[A.size()-1];
}

Vertex Graph::extractMin(vector<Vertex*>&A)     // extracts the minimum element
{
    Vertex *value = A[0];
    Vertex &returnValue = *value;
    swapValue(A);
    A.pop_back();
    min_heapify(A,0,(A.size()));
    return returnValue;
}

int Graph::parent(int val)              // calculation of the parent of the vertex
{
    int odd,even;
    if(!(val%2))
        even =1;
    else
        odd = 1;
    if(even ==1)
        return ((val/2)-1);
    else
        return (val/2);
}

void Graph::decreaseKey(vector<Vertex*>&A,int index,float key)      // restores heap order in log(n) time
{
    if(key < A[index]->value)
    {
        cout << "new key is smaller than current key" << endl;
        return;
    }

    A[index]->value = key;
    int j = parent(index);

    while(index > 0 && (A[j]->value > A[index]->value))
    {
        swap(A[index], A[j]);
        index = j;
    }
}

void Graph::dijkstras(const string& from, const string& to)     // shortest path finder between source and destination
{
    vmap::iterator iter = mygraph.begin();
    vmap::iterator iter1 = mygraph.begin();
    vmap::iterator itr = mygraph.begin();

    vector<Vertex*> priorityQueue;
    int flag12 = 0;
    for (; iter != mygraph.end(); ++iter)
    {
        string cmpName = iter->first;

        Vertex *final1 = iter->second;
        final1->value = 10000;                   //initially all nodes are at infinity distance
        final1->prev = "nil";                      // all the predecessor value to nil
        (priorityQueue).push_back(final1);
    }
    for(int i =0;i<priorityQueue.size();i++)
    {
        if(priorityQueue[i]->name == from)
        {
            priorityQueue[i]->value = 0;        // sets the source value to 0
        }
    }

    float size_ofqueue = priorityQueue.size();
    buildminHeap(priorityQueue,size_ofqueue);       // build the min heap

    vector<Vertex> visited;
    while(priorityQueue.size() != 0)
    {
        Vertex minExtracted =  extractMin(priorityQueue);   // minimum value is extracted in minExtracted

        vmap::iterator itr=mygraph.begin();
        vector<Edge> &traverse = minExtracted.adjlist;

        for (int i=0;i<traverse.size();i++)
        {
            string vertex = (traverse[i]).getDestination();
            itr = mygraph.find(vertex);
            Vertex *v = itr->second;
            Vertex &present = *v;
            int flag,index;
                                                            // Dijkstra's Algorithm
            if( ( v->value) > ( minExtracted.value + (traverse[i]).getWeight() ) && (v->statusVertex == up)&& (traverse[i].statusEdge == up) )
            {
                v->value = ( minExtracted.value + (traverse[i]).getWeight() );
                v->prev = minExtracted.name;
                for(int i =0;i<priorityQueue.size();i++)
                {
                    if(v->name == priorityQueue[i]->name)
                    {
                        index = i;
                    }
                }
                decreaseKey(priorityQueue,index,v->value);  // restores heap order
            }
        }
        visited.push_back(minExtracted);        // stores min value extracted in the vector
    }

    printPath(to);                          // prints shortest path

    vmap::iterator value_itr = mygraph.begin();
    value_itr = mygraph.find(to);
    Vertex *final1 = value_itr->second;
    Vertex &printingVariable = *final1;
    cout << printingVariable.value << endl;     // prints the final value required to reach to destination in our case 'time'
}

void Graph::printPath(string destination)
{
    vmap::iterator it = mygraph.begin();
    vmap::iterator itr = mygraph.begin();
    itr = mygraph.find(destination);
    Vertex *final1 = itr->second;
    Vertex &printingVariable = *final1;
    if(printingVariable.statusVertex == down)
    {
        cout << "Path could not be found to reach " << endl;
    }
    else if(printingVariable.prev != "nil")
    {
        printPath(printingVariable.prev);
    }
    cout << printingVariable.name << '\t';
}
void Graph::reset()
{
    vmap::iterator it1 = mygraph.begin();
    for (; it1 != mygraph.end(); ++it1)
    {
        Vertex *final1 = it1->second;
        final1->value = INFINITY1;                   //initially all nodes are at infinity distance
        final1->prev = "nil";
    }
}

int main(int argc, char*argv[])
{
    Graph g;
    string filename = argv[1];
    string line,source,destination,weight,temp[3],line1;
    ifstream inputFile(argv[1]);
    while(getline(inputFile,line))
    {
        string temp1 = line;
        stringstream words(temp1);
        while(words)
        {

            for (int i=0;i<3;i++)
            {
                words >> temp[i];
            }
        }
        source = temp[0];
        destination = temp[1];
        weight = temp [2];
        istringstream i(weight);
            float dist;
            i >> dist;
        g.addEdge_first_time(source,destination,dist);
    }

    while(1)
    {
        string query,inputQuery[4];
        int positionofWord=0;
        cout << "Enter one of the queries" << endl;
        getline(cin,query);
        stringstream words(query);
        while(words)
        {
            words >> inputQuery[positionofWord];
            positionofWord++;
        }

        if(inputQuery[0] == "addedge")
        {
            istringstream i(inputQuery[3]);
                float dist;
                i >> dist;
                g.addEdge(inputQuery[1],inputQuery[2],dist);
        }
        else if(inputQuery[0] == "deleteedge")
        {
            g.deleteEdge(inputQuery[1],inputQuery[2]);
        }

        else if(inputQuery[0] == "edgedown")
        {
            g.downEdge(inputQuery[1],inputQuery[2]);
        }

        else if(inputQuery[0] == "edgeup")
        {
            g.upEdge(inputQuery[1],inputQuery[2]);
        }

        else if(inputQuery[0] == "vertexdown")
        {
            g.vertexDown(inputQuery[1]);
        }

        else if(inputQuery[0] == "vertexup")
        {
            g.vertexUp(inputQuery[1]);
        }
        else if(inputQuery[0] == "path")
        {
            g.dijkstras(inputQuery[1],inputQuery[2]);
        }
        else if(inputQuery[0] == "print")
        {
            g.print();
        }
        else if(inputQuery[0] == "reachable")
        {
            g.reachable();
        }
        else if(inputQuery[0] == "quit")
        {
            return 0;
        }
        else
            cout << "OOps!Invalid Query! Try again" << endl;
    }
}
