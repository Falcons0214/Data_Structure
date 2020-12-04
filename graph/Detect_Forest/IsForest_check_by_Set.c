#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct Vertex
{
	struct Edge *edgeList[100];
	int edgeCount;
	int id;
};

struct Edge
{
	struct Vertex *end[2];
	int w;
};

int find_root(int x, int node[10])
{
    if( node[x] == -1 ) // if node is root return node
        return x;
    return find_root(node[x], node); // else find root
}

int union_set(int set1, int set2, int node[10])  
{
	printf("%d %d %d %d\n", set1, set2, node[set1], node[set2]); // can't distinguish duplicate edge
	if( node[set1] == set2 ){
		printf("sss\n");
		return 1;
	}
    int root1 = find_root(set1, node);
    int root2 = find_root(set2, node);
    if( root1 == root2 ) // if root is equal -> have loop
        return 0;
    else
    {
        node[root1] = root2; // else union set
        return 1;
    }
}

//判斷傳入的 v 是否為樹林 
int isForest(struct Vertex v[10])
{
    int node[10], i, h, flag = 1;
    for(i=0; i<10; i++)
        node[i] = -1; // init node
    for(i=0; i<10; i++)
    {
        for(h=0; h<v[i].edgeCount; h++)
        {
            if( v[i].edgeList[h]->end[0]->id == v[i].edgeList[h]->end[1]->id )
                return 0;
            if( v[i].edgeList[h]->end[0] == &v[i] )
                flag = union_set( v[i].edgeList[h]->end[0]->id - 1, v[i].edgeList[h]->end[1]->id - 1, node );
            else
                flag = union_set( v[i].edgeList[h]->end[0]->id - 1, v[i].edgeList[h]->end[1]->id - 1, node );
			printf("%d\n", flag);
			if( !flag )
				return 0;
        }
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
	k = 5;//rand() % 10 + 1; //邊的數量 
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
	printf("%s", isForest(v)? "is forset":"not forset"); 
}