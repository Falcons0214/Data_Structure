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