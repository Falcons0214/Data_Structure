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

void DFS(struct Vertex *v)
{
    int top = 0, UsedVertexCount = 0;
    struct Vertex* stack[10];
    struct Vertex* used[10];
    struct Vertex* current;
    stack[top++] = v;
    while(top > 0)
    {
        current = stack[--top];
        used[UsedVertexCount++] = current;
        printf("%d ", current->id);
        for(int i = 0; i < current->edgeCount; i++)
        {
            int IsUsedVertex = 0, End = 0;
            if(current->edgeList[i]->end[0] == current)
                End = 1;
            for(int k = 0; k < UsedVertexCount; k++)
                if(used[k] == current->edgeList[i]->end[End])
                    IsUsedVertex = 1;
            for(int k = 0; k < top; k++)
                if(stack[k] == current->edgeList[i]->end[End])
                    IsUsedVertex = 1;
            if(!IsUsedVertex)
                stack[top++] = current->edgeList[i]->end[End];
        }
    }
}


void BFS(struct Vertex *v)
{
    int top = 0, bot = 0;
    struct Vertex* queue[10];
    struct Vertex* current;
    queue[bot++] = v;
    while(top != bot)
    {
        current = queue[top++];
        printf("%d ", current->id);
        for(int i = 0; i < current->edgeCount; i++)
        {
            int IsUsedVertex = 0, End = 0;
            if(current->edgeList[i]->end[0] == current)
                End = 1;
            for(int k = 0; k < bot; k++)
                if(queue[k] == current->edgeList[i]->end[End])
                    IsUsedVertex = 1;
            if(!IsUsedVertex)
                queue[bot++] = current->edgeList[i]->end[End];
        }
    }
}

void print(struct Vertex v[10])
{
    int j, k;
    for(j = 0; j < 10; j ++)
    {
        printf("%d :", v[j].id);
        for(k = 0; k < v[j].edgeCount; k ++)
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
    for(j = 0; j < 10; j ++)
    {
        v[j].id = j + 1;
        v[j].edgeCount = 0;
    }

    //產生邊
    k = rand() % 20 + 1; //邊的數量
    for(j = 0; j < k; j ++)
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
    for(j = 0; j < 10; j ++)
    {
        BFS(&v[j]);
        printf("\n");
        DFS(&v[j]);
        printf("\n");
    }
}