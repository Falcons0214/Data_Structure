#include <iostream>
#include <list>

using namespace std;

typedef struct node node;
typedef struct edge edge;

struct node // define Vertex
{
    edge *EdgeList[20];
    int EdgeCount;
    char id;
    int status;
};

struct edge // define Edge
{
    node *end[2];
    int weight;
};

class Graph // define Graph class
{
private:
    int TotalNode;
    int TotalEdge;
    list <node*> NodeList;
    list <edge*> EdgeList;

public:
    Graph(): TotalEdge(0), TotalNode(0) {};
    node *getNode(char id);
    edge *getEdge(char weight);
    void Connect(char from, char to, int weight);
    void BFS(char s);
};

node* Graph::getNode(char id) // init
{
    node *temp = new(node);
    temp->status = 0, temp->EdgeCount = 0, temp->id = id;
    return temp;
}

edge* Graph::getEdge(char weight) // init
{
    edge *temp = new(edge);
    temp->weight = weight;
    return temp;
}

void Graph::Connect(char from, char to, int weight) 
{
    edge *CurEdge = getEdge(weight);
    node *From = NULL, *To = NULL;

    for(list<node*>::iterator Cur=NodeList.begin(); Cur!=NodeList.end(); Cur++)
    {
        if( (*Cur)->id == from )
            From = (*Cur);
        if( (*Cur)->id == to )
            To = (*Cur);
    }

    if( From == NULL )
    {
        From = getNode(from);
        NodeList.push_back(From);
        TotalNode ++;
    }
    if( To == NULL )
    {
        To = getNode(to);
        NodeList.push_back(To);
        TotalNode ++;
    }
 
    EdgeList.push_back(CurEdge); // push new node in the NodeList
    TotalEdge += 1;

    CurEdge->end[0] = From, CurEdge->end[1] = To; // Connect two vertices
    From->EdgeList[From->EdgeCount] = CurEdge, To->EdgeList[To->EdgeCount] = CurEdge; // add edge in the node's EdgeList
    From->EdgeCount ++, To->EdgeCount ++; // increase edgecount
}

void Graph::BFS(char s)
{
    int Distance[9]={0}; // A->I
    char Prev[9]={'\0'};
    
    node *start;
    for(list<node*>::iterator Cur=NodeList.begin(); Cur!=NodeList.end(); Cur ++) // Find start node
    {
        if( (*Cur)->id == s )
        {
            start = (*Cur);
            break;
        }
    }

    list<node*> queue;
    queue.push_back(start);
    while(queue.size() != 0) // When queue is empty stop
    {
        queue.front()->status = 1; // visited
        for(int i=0; i<queue.front()->EdgeCount; i++)
        {
            if( queue.front()->EdgeList[i]->end[0]->id != queue.front()->id )
            {
                if( queue.front()->EdgeList[i]->end[0]->status )
                {   // if vertex is visited, compared two path
                    if( Distance[queue.front()->id - 'A'] + queue.front()->EdgeList[i]->weight < Distance[queue.front()->EdgeList[i]->end[0]->id - 'A'] )
                    {   // if new path is small than before, replaced it
                        Distance[queue.front()->EdgeList[i]->end[0]->id - 'A'] = Distance[queue.front()->id - 'A'] + queue.front()->EdgeList[i]->weight;
                        Prev[queue.front()->EdgeList[i]->end[0]->id - 'A'] = queue.front()->id;
                    }
                }else{
                    queue.push_back(queue.front()->EdgeList[i]->end[0]);
                    queue.front()->EdgeList[i]->end[0]->status = 1;

                    Prev[queue.front()->EdgeList[i]->end[0]->id - 'A'] = queue.front()->id;
                    Distance[queue.front()->EdgeList[i]->end[0]->id - 'A'] += Distance[queue.front()->id - 'A'];
                    Distance[queue.front()->EdgeList[i]->end[0]->id - 'A'] += queue.front()->EdgeList[i]->weight;
                }
            }else{
                if( queue.front()->EdgeList[i]->end[1]->status )
                {   // if vertex is visited, compared two path
                    if( Distance[queue.front()->id - 'A'] + queue.front()->EdgeList[i]->weight < Distance[queue.front()->EdgeList[i]->end[1]->id - 'A'] )
                    {   // if new path is small than before, replaced it
                        Distance[queue.front()->EdgeList[i]->end[1]->id - 'A'] = Distance[queue.front()->id - 'A'] + queue.front()->EdgeList[i]->weight;
                        Prev[queue.front()->EdgeList[i]->end[1]->id - 'A'] = queue.front()->id;
                    }
                }else{
                    queue.push_back(queue.front()->EdgeList[i]->end[1]);
                    queue.front()->EdgeList[i]->end[1]->status = 1;

                    Prev[queue.front()->EdgeList[i]->end[1]->id - 'A'] = queue.front()->id;
                    Distance[queue.front()->EdgeList[i]->end[1]->id - 'A'] += Distance[queue.front()->id - 'A'];
                    Distance[queue.front()->EdgeList[i]->end[1]->id - 'A'] += queue.front()->EdgeList[i]->weight;
                }
            }
        }
        queue.pop_front();
    }

    for(int i=0; i<9; i++)
    {
        printf("Shortest path C to %c %d", i+'A', Distance[i]);
        printf(" Prev %c\n", Prev[i]);
    }
}

int main()
{
    Graph map;

    map.Connect('A', 'B', 2), map.Connect('A', 'C', 6), map.Connect('A', 'D', 3);
    map.Connect('B', 'E', 6);
    map.Connect('C', 'E', 5), map.Connect('C', 'H', 7), map.Connect('C', 'F', 6), map.Connect('C', 'G', 7);
    map.Connect('D', 'H', 1);
    map.Connect('E', 'F', 9);
    map.Connect('F', 'I', 3);
    map.Connect('G', 'I', 8);
    map.Connect('H', 'G', 5);

    map.BFS('C'); // Start from 'C' vertex
    return 0;
}