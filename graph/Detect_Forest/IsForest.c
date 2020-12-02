#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Vertex Vertex;
typedef struct Edge Edge;

struct Vertex
{
	Edge *edgeList[100];
	int edgeCount;
	int id;
    int status; // 0 = unvisited, 1 = visited, 2 = double visited
};

struct Edge
{
    Vertex *end[2];
	int w;
};

void find_node(Vertex v[10], int vertex, int *count)
{
    if( v[vertex].status == 2)
        return ;
    if( !v[vertex].status )
    {
        (*count) += 1;
        if( *count == 2 )
            return ;
        v[vertex].status = 1;
    }else
        return ;
    
    for(int i=0; i<v[vertex].edgeCount; i++)
    {
        for(int h=0; h<2; h++)
        {
            if( v[vertex].edgeList[i]->end[h]->id == v[vertex].id )// pointer to self
                continue;
            if( v[v[vertex].edgeList[i]->end[h]->id - 1].status )// pointer to parent 
                break;
            find_node(v, v[vertex].edgeList[i]->end[h]->id - 1, count);            
        }
    }
}

int isForest(Vertex v[10], int num)
{
    int count = 0;
    find_node(v, 0, &count);
    printf("graph node: %d, tree node: %d\n", num, count);
    if( num == count )
        return 1;
    return 0;
}

void print(Vertex v[10])
{
	int j, k;
	for(j = 0;j < 10;j ++)
	{
		printf("%d :", v[j].id);
		for(k = 0;k < v[j].edgeCount;k ++)
		{
			if(v[j].edgeList[k]->end[0] == &v[j])
				printf("%d ", v[j].edgeList[k]->end[1]->id);
			else
				printf("%d ", v[j].edgeList[k]->end[0]->id);
		}
		printf("\n");
	}
}

int main()
{
    Vertex v[10]; 
	Edge e[100];
	int j, k, i, l;
    int count = 0;
	
	srand(time(NULL));

	// generate vertex, vertex.1 -> vertex.10
	for(j = 0;j < 10;j ++)
	{
		v[j].id = j + 1;
		v[j].edgeCount = 0;// init edge count
        v[j].status = 0;
	}

	k = 9 ;//rand() % 10 + 1; // number fo edge 
	for(j = 0;j < k;j ++)
	{
		// init two vertex
		i = rand() % 10;
		l = rand() % 10;

		// setting edge weight 
		e[j].w = rand() % 100;

		// connect two vertices, "set the Edge.vertex end[0] and end[1]"
		e[j].end[0] = &v[i];
		e[j].end[1] = &v[l];
	    //printf("!!\n");

		// add edge in the Vertex.egdelist and increase edgeCount
		v[i].edgeList[v[i].edgeCount] = &e[j];
		v[i].edgeCount ++;
		v[l].edgeList[v[l].edgeCount] = &e[j];
		v[l].edgeCount ++;
	}
    
    /*
    e[0].w = rand() % 100;
    e[0].end[0] = &v[0];
	e[0].end[1] = &v[1];

    v[0].edgeList[v[0].edgeCount] = &e[0];
	v[0].edgeCount ++;
	v[1].edgeList[v[1].edgeCount] = &e[0];
	v[1].edgeCount ++;

    e[1].w = rand() % 100;
    e[1].end[0] = &v[0];
	e[1].end[1] = &v[2];

    v[0].edgeList[v[0].edgeCount] = &e[1];
	v[0].edgeCount ++;
	v[2].edgeList[v[2].edgeCount] = &e[1];
	v[2].edgeCount ++;

    e[2].w = rand() % 100;
    e[2].end[0] = &v[0];
	e[2].end[1] = &v[3];

    v[0].edgeList[v[0].edgeCount] = &e[2];
	v[0].edgeCount ++;
	v[3].edgeList[v[3].edgeCount] = &e[2];
	v[3].edgeCount ++;

    e[3].w = rand() % 100;
    e[3].end[0] = &v[3];
	e[3].end[1] = &v[4];

    v[3].edgeList[v[3].edgeCount] = &e[3];
	v[3].edgeCount ++;
	v[4].edgeList[v[4].edgeCount] = &e[3];
	v[4].edgeCount ++;

    e[4].w = rand() % 100;
    e[4].end[0] = &v[3];
	e[4].end[1] = &v[5];

    v[3].edgeList[v[3].edgeCount] = &e[4];
	v[3].edgeCount ++;
	v[5].edgeList[v[5].edgeCount] = &e[4];
	v[5].edgeCount ++;

    e[5].w = rand() % 100;
    e[5].end[0] = &v[3];
	e[5].end[1] = &v[6];

    v[3].edgeList[v[3].edgeCount] = &e[5];
	v[3].edgeCount ++;
	v[6].edgeList[v[6].edgeCount] = &e[5];
	v[6].edgeCount ++;

    e[6].w = rand() % 100;
    e[6].end[0] = &v[5];
	e[6].end[1] = &v[7];

    v[5].edgeList[v[5].edgeCount] = &e[6];
	v[5].edgeCount ++;
	v[7].edgeList[v[7].edgeCount] = &e[6];
	v[7].edgeCount ++;

    e[7].w = rand() % 100;
    e[7].end[0] = &v[6];
	e[7].end[1] = &v[8];

    v[6].edgeList[v[6].edgeCount] = &e[7];
	v[6].edgeCount ++;
	v[8].edgeList[v[8].edgeCount] = &e[7];
	v[8].edgeCount ++;

    e[8].w = rand() % 100;
    e[8].end[0] = &v[6];
	e[8].end[1] = &v[9];

    v[6].edgeList[v[6].edgeCount] = &e[8];
	v[6].edgeCount ++;
	v[9].edgeList[v[9].edgeCount] = &e[8];
	v[9].edgeCount ++;
    */

	print(v);
	printf("%s", isForest(v, 10)? "is tree":"not tree"); 
}