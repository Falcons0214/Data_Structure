#ifndef PQ_HEAP
#define PQ_HEAP

typedef struct Heap Heap;
typedef struct PQheap PQheap;

typedef enum {
    MinHeap, MaxHeap // 0, 1
}HeapClass;

struct Heap
{
    void **root;
    int current_size; 
};

struct PQheap
{
    HeapClass type;
    Heap heap;
    int elementNum, elementSize;
    int (*compare)(void *EA, void *EB);
};

void CreateHeap(PQheap *Heap, HeapClass type, int elementsize, int maxsize, int (*compare)(void *EA, void *EB));
int IsEmpty(PQheap *Heap);
int IsFull(PQheap *Heap);
int EnQueue(PQheap *PQHeap, void *element);
int Current_Size(PQheap *Heap);
void *DeQueue(PQheap *PQHeap);

#endif