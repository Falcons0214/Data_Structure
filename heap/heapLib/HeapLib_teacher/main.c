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