#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stu stu;
// define heap struct 
typedef struct Heap Heap;
typedef struct PQheap PQheap;

typedef enum {
    MinHeap, MaxHeap // 0, 1
}HeapClass;

struct Heap
{
    void **root;
    int elementNum; 
};

struct PQheap
{
    HeapClass type;
    Heap heap;
    int current_size, elementSize;
    int (*compare)(void *EA, void *EB);
};

// define heap function
static void HeapUp(PQheap *PQHeap, int index)
{
    Heap temp = PQHeap->heap;
    if(index == 1)
        return ; 
    if( PQHeap->type )
    {   // MaxHeap
        if( PQHeap->compare(temp.root[index], temp.root[index/2]) )
        {
            void *var = temp.root[index];
            temp.root[index] = temp.root[index/2];
            temp.root[index/2] = var;
            HeapUp(PQHeap, index/2);
        }
    }else{
        // MinHeap
        if( !PQHeap->compare(temp.root[index], temp.root[index/2]) )
        {
            void *var = temp.root[index];
            temp.root[index] = temp.root[index/2];
            temp.root[index/2] = var;
            HeapUp(PQHeap, index/2);
        }
    }
}

static void HeapDown(PQheap *PQHeap, int index)
{
    Heap temp = PQHeap->heap;
    int checkpoint = -1;
    if( temp.root[index * 2] != NULL && temp.root[index * 2 + 1] != NULL )
    {   
        if( PQHeap->type )
        {   // MaxHeap, compare Efirst > Esecond return 1 else 0; 
            if( PQHeap->compare(temp.root[index * 2], temp.root[index * 2 + 1]) ) 
                checkpoint = index * 2;
            else
                checkpoint = index * 2 + 1;
            if( PQHeap->compare(temp.root[checkpoint], temp.root[index]) )
            {
                void* var = temp.root[checkpoint];
                temp.root[checkpoint] = temp.root[index];
                temp.root[index] = var;
            }else
                return ;
            HeapDown(PQHeap, checkpoint);
        }else{
            // MinHeap, compare Efirst > Esecond return 1 else 0; 
            if( PQHeap->compare(temp.root[index * 2], temp.root[index * 2 + 1]) ) 
                checkpoint = index * 2 + 1;
            else
                checkpoint = index * 2;
            if( !PQHeap->compare(temp.root[checkpoint], temp.root[index]) )
            {
                void* var = temp.root[checkpoint];
                temp.root[checkpoint] = temp.root[index];
                temp.root[index] = var;
            }else
                return ;
            HeapDown(PQHeap, checkpoint);
        }   
    }
}

// define Lib function
void CreateHeap(PQheap *Heap, HeapClass type, int elementsize, int maxsize, int (*compare)(void *EA, void *EB))
{
    Heap->type = type;
    Heap->heap.elementNum = maxsize;
    Heap->current_size = 1;
    Heap->compare = compare;
    Heap->elementSize = elementsize;
    Heap->heap.root = (void**)malloc(sizeof(void*) * (maxsize+1));
    for(int i=0; i<(maxsize+1); i++)
        Heap->heap.root[i] = NULL;
}

int IsEmpty(PQheap *Heap)
{
    if( !Heap->current_size )
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
    PQHeap->heap.root[PQHeap->current_size] = element;
    HeapUp(PQHeap, PQHeap->current_size);
    PQHeap->current_size ++;
    return 1;
}

void *DeQueue(PQheap *PQHeap)
{
    if( IsEmpty(PQHeap) )
        return NULL;
    Heap temp = PQHeap->heap;
    void *var = (void*)malloc(sizeof(char) * PQHeap->elementSize);
    memcpy(var, temp.root[1], PQHeap->elementSize);
    PQHeap->current_size -= 1;
    temp.root[1] = temp.root[PQHeap->current_size];
    temp.root[PQHeap->current_size] = NULL; 
    HeapDown(PQHeap, 1);
    return var;
}

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

    CreateHeap(&class_heap, MaxHeap, sizeof(stu), 20, tt);

    for(int i=0; i<9; i++)
        EnQueue(&class_heap, &class1[i]);
    
    inorder(class_heap.heap, 1);
    printf("\n");
    preorder(class_heap.heap, 1);

    void *root1 = DeQueue(&class_heap);

    printf("\n");
    printf("%d %c\n", ((stu*)(root1))->grade, ((stu*)(root1))->ID );

    preorder(class_heap.heap, 1);

    return 0;
}
