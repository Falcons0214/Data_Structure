#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "heap.h"

static void HeapUp(PQheap *PQHeap, int index)
{
    Heap temp = PQHeap->heap;
    if(index == 1)
        return ; 
    if( PQHeap->compare(temp.root[index], temp.root[index/2]) == PQHeap->type )
    {
        void *var = temp.root[index];
        temp.root[index] = temp.root[index/2];
        temp.root[index/2] = var;
        HeapUp(PQHeap, index/2);
    }
}

static void HeapDown(PQheap *PQHeap, int index)
{
    Heap temp = PQHeap->heap;
    int checkpoint = -1;
    if( temp.root[index * 2] != NULL || temp.root[index * 2 + 1] != NULL )
    {   
        if( temp.root[index*2 + 1] != NULL )
        {
            if( PQHeap->compare(temp.root[index * 2], temp.root[index * 2 + 1]) == PQHeap->type )
                checkpoint = index * 2;
            else
                checkpoint = index * 2 + 1;
        }else
            checkpoint = index * 2;
        if( PQHeap->compare(temp.root[checkpoint], temp.root[index]) == PQHeap->type )
        {
            void* var = temp.root[checkpoint];
            temp.root[checkpoint] = temp.root[index];
            temp.root[index] = var;
        }else
            return ;
        HeapDown(PQHeap, checkpoint); 
    }
}

// define Lib function
void CreateHeap(PQheap *Heap, HeapClass type, int elementsize, int maxsize, int (*compare)(void *EA, void *EB))
{
    Heap->type = type;
    Heap->elementNum = maxsize;
    Heap->heap.current_size = 1;
    Heap->compare = compare;
    Heap->elementSize = elementsize;
    Heap->heap.root = (void**)malloc(sizeof(void*) * (maxsize+1));
    for(int i=0; i<(maxsize+1); i++)
        Heap->heap.root[i] = NULL;
}

int Current_Size(PQheap *Heap)
{
    return Heap->heap.current_size - 1;
}

int IsEmpty(PQheap *Heap)
{
    if( Heap->heap.current_size == 1 )
        return 1;
    return 0;
}

int IsFull(PQheap *Heap)
{
    if( Heap->heap.current_size == Heap->elementNum + 1 )
        return 1;
    return 0;
}

int EnQueue(PQheap *PQHeap, void *element)
{
    if( IsFull(PQHeap) )
        return 0;
    PQHeap->heap.root[PQHeap->heap.current_size] = element;
    HeapUp(PQHeap, PQHeap->heap.current_size);
    PQHeap->heap.current_size ++; 
    return 1;
}

void *DeQueue(PQheap *PQHeap)
{
    if( IsEmpty(PQHeap) )
    {
        printf("Heap is empty!\n");
        return NULL;
    }
    Heap temp = PQHeap->heap;
    void *var = (void*)malloc(sizeof(char) * PQHeap->elementSize);
    memcpy(var, temp.root[1], PQHeap->elementSize);
    PQHeap->heap.current_size -= 1;
    temp.root[1] = temp.root[PQHeap->heap.current_size];
    temp.root[PQHeap->heap.current_size] = NULL; 
    HeapDown(PQHeap, 1);
    return var;
}