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

void DFS(struct Vertex *v)
{
    if( v->status != 0 )
        return ;
    printf("%d ", v->id);
    v->status = 1;
    for(int i=0; i<v->edgeCount; i++)
    {
        if( v->edgeList[i]->end[0] == v )
            DFS( v->edgeList[i]->end[1]);
        else
            DFS( v->edgeList[i]->end[0]);
    }
}

void BFS(struct Vertex *v)
{
    struct Vertex *visited[100];
    int top = 0, bot = 0;
    
    visited[bot++] = v, visited[top]->status = 1;
    while(top != bot)
    {
        printf("%d ", visited[top]->id);
        for(int i=0; i<visited[top]->edgeCount; i++)
        {
            if( visited[top]->edgeList[i]->end[0] == visited[top]->edgeList[i]->end[1] ) // ignore self loop
                continue;
            if( visited[top]->edgeList[i]->end[0] == visited[top]){
                if( visited[top]->edgeList[i]->end[1]->status != 0)
                    continue;
                visited[top]->edgeList[i]->end[1]->status = 1;
                visited[bot++] = visited[top]->edgeList[i]->end[1];
            }else{
                if( visited[top]->edgeList[i]->end[0]->status != 0)
                    continue;
                visited[top]->edgeList[i]->end[0]->status = 1;
                visited[bot++] = visited[top]->edgeList[i]->end[0];
            }
        }
        top ++;
    }
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
	k = rand() % 20 + 1; //邊的數量 
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
	printf("!!\n");
		//在兩個端點加入邊 
		v[i].edgeList[v[i].edgeCount] = &e[j];
		v[i].edgeCount ++;
		v[l].edgeList[v[l].edgeCount] = &e[j];
		v[l].edgeCount ++;
	}
	print(v);
	for(j = 0;j < 10;j ++)
    {
        for(int i=0; i<10; i++)
            v[i].status = 0;
        printf("v[%d] BFS: ", j+1 );
        BFS(&v[j]);
        printf("\n");

        for(int i=0; i<10; i++)
            v[i].status = 0;
        printf("v[%d] DFS: ", j+1 );
        DFS(&v[j]);
        printf("\n");
    }
}