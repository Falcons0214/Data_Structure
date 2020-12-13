#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "heap.c"

typedef struct stu stu;

struct stu
{
    char ID;
    int grade;
};

int Grade(void *EA, void *EB)
{
    if( ((stu*)EA)->grade > ((stu*)EB)->grade )
        return 1;
    return 0;
}

void inorder(Heap heap, int index)
{
    if( !heap.root[index] )
        return ;
    inorder(heap, index*2);
    printf("%d ", ((stu*)(heap.root[index]))->grade );
    inorder(heap, index*2+1);
}

void preorder(Heap heap, int index)
{
    if( !heap.root[index] )
        return ;
    printf("%d ", ((stu*)(heap.root[index]))->grade );
    preorder(heap, index*2);
    preorder(heap, index*2+1);
}

int main()
{
    stu class1[10];
    PQheap class_heap;
    int (*tt)(void*, void*) = &Grade;

    class1[0].ID = 'A', class1[0].grade = 98;
    class1[1].ID = 'B', class1[1].grade = 60;
    class1[2].ID = 'C', class1[2].grade = 77;
    class1[3].ID = 'D', class1[3].grade = 49;
    class1[4].ID = 'E', class1[4].grade = 88;
    class1[5].ID = 'F', class1[5].grade = 19;
    class1[6].ID = 'G', class1[6].grade = 100;
    class1[7].ID = 'H', class1[7].grade = 58;
    class1[8].ID = 'I', class1[8].grade = 67;

    CreateHeap(&class_heap, MinHeap, sizeof(stu), 20, tt);

    for(int i=0; i<9; i++)
        EnQueue(&class_heap, &class1[i]);
    
    inorder(class_heap.heap, 1);
    printf("\n");
    preorder(class_heap.heap, 1);
    printf("\n");
    void *root1;

    for(int i=0; i<10; i++)
    {
        root1 = DeQueue(&class_heap);
        if( root1 != NULL )
            printf("%d %c\n", ((stu*)(root1))->grade, ((stu*)(root1))->ID );
    }

    preorder(class_heap.heap, 1);

    return 0;
}