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
};

struct Edge
{
    Vertex *end[2];
	int w;
};

//判斷傳入的 v 是否為樹林 
int isForest(Vertex v[10])
{
    Vertex *visited[15]; // record vertices it is visited
    for(int i=0; i<10; i++)
    {   
        Edge *used[100]; // record edges it is uesed
        int bot = 0, top = 0, edgecount = 0;
        visited[bot++] = &v[i]; 
        while(top != bot) // stop when queue is empty
        {
            //printf("%d %d %d\n",i, top, bot);
            for(int j=0; j<visited[top]->edgeCount; j++) // visiting every edges
            {
                used[edgecount++] = visited[top]->edgeList[j];
                int flag = 1;
                if( visited[top]->edgeList[j]->end[0] == visited[top]->edgeList[j]->end[1] )
                    return 0;
                if( visited[top]->edgeList[j]->end[0] == visited[top] )
                {
                    for(int k=0; k<edgecount-1; k++)
                        if( used[k] == visited[top]->edgeList[j] )
                            flag = 0;
                    if(flag)
                    {
                        for(int k=bot-1; k>=0; k--)
                        {   // trace back, if find same vertex retrun 0
                            if( visited[top]->edgeList[j]->end[1] == visited[k])
                                return 0;
                        }
                        // if edge is not visited, add the vertex in the visieted array
                        visited[bot++] = visited[top]->edgeList[j]->end[1];
                    }
                }else{
                    for(int k=0; k<edgecount-1; k++)
                        if( used[k] == visited[top]->edgeList[j] )
                            flag = 0;
                    if(flag)
                    {
                        for(int k=bot-1; k>=0; k--)
                        {
                            if( visited[top]->edgeList[j]->end[0] == visited[k])
                                return 0;
                        }
                        visited[bot++] = visited[top]->edgeList[j]->end[0];visited[bot++] = visited[top]->edgeList[j]->end[0];
                    }
                }
            }
            top ++;
        }
    }
    return 1;
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
	}

	k = rand() % 10 + 1; // number fo edge
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

	print(v);
	printf("%s", isForest(v)? "is forest":"not forest"); 
}