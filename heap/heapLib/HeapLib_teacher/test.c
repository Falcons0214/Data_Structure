#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Heap Heap;
typedef struct PQheap PQheap;
typedef struct stu stu;

typedef enum {
    MinHeap, MaxHeap // 0, 1
}HeapClass;

struct Heap
{
    void *root;
    int elementNum; 
};

struct PQheap
{
    HeapClass type;
    Heap heap;
    int current_size, elementSize;
    int (*compare)(void *EA, void *EB);
};


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

static void swap(void *EA, void *EB, int ES)
{
    void *temp = (void*)malloc(sizeof(char) * ES);
    memcpy(temp, EA, ES);
    memcpy(EA, EB, ES);
    memcpy(EB, temp, ES);
    free(temp);
}

static void HeapUp(PQheap *PQHeap, int index)
{
    Heap cur = PQHeap->heap;
    int size = PQHeap->elementSize;
    if(index == 1)
        return ;
    // MaxHeap -> 1, MinHeap -> 0
    if( PQHeap->compare( ((char*)cur.root) + size * index, ((char*)cur.root) + size * (index/2)) == PQHeap->type )
    {
        swap( ((char*)cur.root) + size * index, ((char*)cur.root) + size * (index/2), PQHeap->elementSize);
        HeapUp(PQHeap, index/2);
    }
}

static void HeapDown(PQheap *PQHeap, int index)
{
    if( index*2 >= PQHeap->current_size )
        return ;
    Heap cur = PQHeap->heap;
    int checkpoint = -1, size = PQHeap->elementSize;
    if( index*2 + 1 <= PQHeap->current_size )
    {
        if( PQHeap->compare( ((char*)cur.root) + size * (index*2), ((char*)cur.root) + size * ((index*2)+1)) == PQHeap->type )
            checkpoint = index * 2;
        else
            checkpoint = index * 2 + 1;
    }else
        checkpoint = index * 2;
    if( PQHeap->compare( ((char*)cur.root) + size * checkpoint, ((char*)cur.root) + size * index) == PQHeap->type )
        swap(((char*)cur.root) + size * checkpoint, ((char*)cur.root) + size * index, PQHeap->elementSize);
    else
        return ;
    HeapDown(PQHeap, checkpoint); 
}

// define Lib function
void CreateHeap(PQheap *Heap, HeapClass type, int elementsize, int maxsize, int (*compare)(void *EA, void *EB))
{
    Heap->type = type;
    Heap->heap.elementNum = maxsize+1;
    Heap->current_size = 1;
    Heap->compare = compare;
    Heap->elementSize = elementsize;
    Heap->heap.root = (void*)malloc(sizeof(char) * elementsize * (maxsize+1));
}

int IsEmpty(PQheap *Heap)
{
    if( Heap->current_size == 1 )
        return 1;
    return 0;
}

int IsFull(PQheap *Heap)
{
    if( Heap->current_size == Heap->heap.elementNum )
        return 1;
    return 0;
}

int EnQueue(PQheap *PQHeap, void *element)
{
    if( IsFull(PQHeap) )
        return 0;
    Heap cur = PQHeap->heap;
    memcpy(((char*)cur.root) + PQHeap->elementSize * PQHeap->current_size, element, PQHeap->elementSize);
    HeapUp(PQHeap, PQHeap->current_size);
    PQHeap->current_size ++;
    return 1;
}

void *DeQueue(PQheap *PQHeap)
{
    if( IsEmpty(PQHeap) )
    {
        printf("Heap is empty!\n");
        return NULL;
    }
    Heap cur = PQHeap->heap;
    void *var = (void*)malloc(sizeof(char) * PQHeap->elementSize);
    memcpy(var, (((char*)cur.root) + PQHeap->elementSize), PQHeap->elementSize);
    PQHeap->current_size -= 1;
    memcpy((((char*)cur.root) + PQHeap->elementSize), ((char*)cur.root) + PQHeap->elementSize * PQHeap->current_size, PQHeap->elementSize);
    HeapDown(PQHeap, 1);
    return var;
}

int main()
{
    stu class1[10];
    stu class2[5];
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

    class2[0].ID = 'Z', class2[0].grade = 81;
    class2[1].ID = 'X', class2[1].grade = 69;
    class2[2].ID = 'J', class2[2].grade = 15;
    class2[3].ID = 'L', class2[3].grade = 44;
    class2[4].ID = 'H', class2[4].grade = 99;

    CreateHeap(&class_heap, MaxHeap, sizeof(stu), 20, tt);

    for(int i=0; i<9; i++)
        EnQueue(&class_heap, &class1[i]);
    
    void *root1;

    for(int i=0; i<5; i++)
    {
        root1 = DeQueue(&class_heap);
        if( root1 != NULL )
            printf("%d %c\n", ((stu*)(root1))->grade, ((stu*)(root1))->ID );
    }

    for(int i=0; i<5; i++)
        EnQueue(&class_heap, &class2[i]);

    for(int i=0; i<11; i++)
    {
        root1 = DeQueue(&class_heap);
        if( root1 != NULL )
            printf("%d %c\n", ((stu*)(root1))->grade, ((stu*)(root1))->ID );
    }

    return 0;
}