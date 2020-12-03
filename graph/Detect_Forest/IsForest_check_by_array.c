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
    int graph[10][11] = {0};
	int i, h, flag = 1;
	for(i=0; i<10; i++)
	{
		for(h=0; h<v[i].edgeCount; h++)
		{
			graph[v[i].edgeList[h]->end[1]->id-1][10]++, graph[v[i].edgeList[h]->end[0]->id-1][10]++;
			graph[ v[i].edgeList[h]->end[1]->id-1 ][ v[i].edgeList[h]->end[0]->id-1 ] += 1;
			graph[ v[i].edgeList[h]->end[0]->id-1 ][ v[i].edgeList[h]->end[1]->id-1 ] += 1;
		}
	}
	while(flag)
	{
		flag = 0;
		for(i=0; i<10; i++)
		{
			if(graph[i][10] == 2)
			{
				flag = 1;
				graph[i][10] = 0;
				for(h=0; h<10; h++)
				{
					if( graph[i][h] == 2 )
					{
						graph[h][10] -= 2;
						break;
					}
				}
			}
		}
	}
	for(i=0; i<10; i++)
		if( graph[i][10] != 0 )
			return 0;
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

	k = 5;//rand() % 10 + 1; // number fo edge
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