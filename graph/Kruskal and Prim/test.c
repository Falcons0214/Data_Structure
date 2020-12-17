#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Vertex Vertex;
typedef struct Edge Edge;

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

int Find_NonDuplicate_Edge(Vertex v[10], Edge **Non)
{
    int Edge_Num = 0;
    for(int i=0; i<10; i++)
    {
        for(int h=0; h<v[i].edgeCount; h++)
        {
            if( v[i].edgeList[h]->end[0] == v[i].edgeList[h]->end[1] ) // ignore self loop
                continue;
            int flag = 1;
            for(int j=0; j<Edge_Num; j++) // find duplicate
            {
                if( Non[j] == v[i].edgeList[h] )
                {
                    flag = 0;
                    break;
                }
                if( (Non[j]->end[0] == v[i].edgeList[h]->end[0] && Non[j]->end[1] == v[i].edgeList[h]->end[1]) ||
                    (Non[j]->end[1] == v[i].edgeList[h]->end[0] && Non[j]->end[0] == v[i].edgeList[h]->end[0]) )
                {
                    flag = 0;
                    Non[j] = v[i].edgeList[h];
                    break;
                }
            }
            if(flag)
                Non[Edge_Num++] = v[i].edgeList[h];
        }
    }
    return Edge_Num;
}

void Sort(Edge **Non, int Num)
{
    for(int i=0; i<Num-1; i++)
    {
        for(int h=0; h<Num-i-1; h++)
        {
            if( Non[h]->w > Non[h+1]->w )
            {
                Edge *temp = Non[h];
                Non[h] = Non[h+1];
                Non[h+1] = temp; 
            }
        }
    }
}

int find_root(int x, int parent[])
{
    int x_root = x;
    while(parent[x_root-1] != 0)
        x_root = parent[x_root-1];
    return x_root;
}

int union_set(int x, int y, int parent[])
{
    int x_root = find_root(x, parent);
    int y_root = find_root(y, parent);
    if( x_root == y_root )
        return 0;
    parent[x_root-1] = y_root;
    return 1;
}

//請把找到的邊存在 result 
void Kruskal(Vertex v[10], Edge e[100], Edge *result[100])
{
    Edge *Sorted_Edge[100] = {0};
    int parent[10] = {0}, Edge_Num = 0, result_num = 0;
    Edge_Num = Find_NonDuplicate_Edge(v, Sorted_Edge);
    Sort(Sorted_Edge, Edge_Num);

    for(int i=0; i<Edge_Num; i++)
    {
        if( result_num == 9 )
            return;
        int ver_1 = Sorted_Edge[i]->end[0]->id;
        int ver_2 = Sorted_Edge[i]->end[1]->id;
        if( union_set( ver_1, ver_2, parent ) )
            result[result_num++] = Sorted_Edge[i];
    }
}

//請把找到的邊存在 result 
void prim(Vertex v[10], Edge e[100], Edge *result[100], int root)
{
    Edge *list[100] = {0}, *Sorted_Edge[100] = {0};
    int result_Num = 0, cur = root, list_Num = 0, Edge_Num = 0;

    Edge_Num = Find_NonDuplicate_Edge(v, Sorted_Edge);
    
    while(1)
    {
        if( result_Num == Edge_Num )
            return ;
        int min = -1, flag = 0;
        for(int i=0; i<v[cur].edgeCount; i++)
        {
            for(int h=0; h<result_Num; h++)
                if( result[h] ==  v[cur].edgeList[i] )
                    flag = 1;
            if( !flag )
            {
                for(int h=0; h<Edge_Num; h++)
                {
                    if(v[cur].edgeList[i] == Sorted_Edge[h])
                    {
                        list[list_Num++] = v[cur].edgeList[i];
                        break;
                    }
                }
            }
        }
        for(int i=0; i<list_Num; i++)
        {
            if( list[i]->w < min)
            {
                flag = 0;
                for(int h=0; h<result_Num; h++)
                    if( result[h] == list[i] )
                        flag = 1;
                if( !flag )
                    min = i;
            }
        }
        if( list[min]->end[0]->id == cur+1 )
            cur = list[min]->end[1]->id - 1;
        else 
            cur - list[min]->end[0]->id - 1;
        result[result_Num++] = list[min];
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
	Vertex v[10];
	Edge e[100];
	Edge *result[100] = {0};
	int j, k, i, l;
	
	srand(time(NULL));
	//產生點
	for(j = 0;j < 10;j ++)
	{
		v[j].id = j + 1;
		v[j].edgeCount = 0;
	}
	
	//產生邊
	k = rand() % 10 + 1; //邊的數量 
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

	Kruskal(v, e, result);
	//prim(v, e, result);
    
    
    printf("\n");
    for(int i=0; i<100; i++)
    {
        if(result[i] == NULL)
            break;
        printf("%d %d\n", result[i]->end[0]->id, result[i]->end[1]->id);
    }
    printf("\n");
    
    printf("End!");
}
