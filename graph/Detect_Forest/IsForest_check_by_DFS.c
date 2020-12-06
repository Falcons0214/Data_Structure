#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct Vertex
{
	struct Edge *edgeList[100];
	int edgeCount;
	int id;
	int status;
};

struct Edge
{
	struct Vertex *end[2];
	int w;
};

int IsTree(struct Vertex v[10], int root, struct Edge *used)
{
	if( v[root].status )
		return 0;
	v[root].status = 1;
	for(int i=0; i<v[root].edgeCount; i++)
	{
		if( v[root].edgeList[i] != used )
		{
			if( v[root].edgeList[i]->end[0] != &v[root] )
			{
				return IsTree(v, v[root].edgeList[i]->end[0]->id - 1, v[root].edgeList[i]);
			}else{  
				return IsTree(v, v[root].edgeList[i]->end[1]->id - 1, v[root].edgeList[i]);
			}
		}
	}
	return 1;
}

//判斷傳入的 v 是否為樹林 
int isForest(struct Vertex v[10])
{
	for(int i=0; i<10; i++)
	{
		for(int h=0; h<10; h++)
			v[h].status = 0;
		if( !IsTree(v, i, NULL) )
			return 0;
	}
	return 1;
}

void print(struct Vertex v[10])
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
	struct Vertex v[10];
	struct Edge e[100];
	int j, k, i, l;
	
	srand(time(NULL));
	//產生點
	for(j = 0;j < 10;j ++)
	{
		v[j].id = j + 1;
		v[j].edgeCount = 0;
	}
	
	//產生邊
	k = 5; //邊的數量 
	for(j = 0;j < k;j ++)
	{
		//先產生兩個端點 
		i = rand() % 10;
		l = rand() % 10;
		//邊的重量 
		e[j].w = rand() % 100;
		//兩個端點的連結 
		e[j].end[0] = &v[i];
		e[j].end[1] = &v[l];
		//在兩個端點加入邊 
		v[i].edgeList[v[i].edgeCount] = &e[j];
		v[i].edgeCount ++;
		v[l].edgeList[v[l].edgeCount] = &e[j];
		v[l].edgeCount ++;
	}
	print(v);
	printf("%s", isForest(v)? "is forest":"not forest"); 
}