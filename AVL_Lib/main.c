#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"
#include "AVL.c"

typedef struct student STD;

struct student
{
    node Link;
    char id;
    int score;
};

STD *init(char i, int s)
{
    STD *temp = (STD*)malloc(sizeof(STD));
    temp->id = i, temp->score = s;
    temp->Link.parent = NULL, temp->Link.left = NULL, temp->Link.right = NULL;
    temp->Link.Righthigh = 0, temp->Link.Lefthigh = 0;
    return temp;
}

int cmp(void *A, void *B)
{
    if( ((STD*)A)->score > ((STD*)B)->score )
        return 1;
    return 0;
}

int Find(void *A, void *B)
{
    if( ((STD*)A)->score == ((STD*)B)->score )
        return 3;
    if( ((STD*)A)->score > ((STD*)B)->score )
        return 2;
    else
        return 1;
}

void inorder(node *root)
{
    if(root == NULL)
        return ;
    inorder(root->left);
    printf("Score: %d Left: %d Right: %d\n", ((STD*)root)->score, ((STD*)root)->Link.Lefthigh, ((STD*)root)->Link.Righthigh );
    inorder(root->right);
}

void preorder(node *root)
{
    if(root == NULL)
        return ;
    printf("Score: %d Left: %d Right: %d\n", ((STD*)root)->score, ((STD*)root)->Link.Lefthigh, ((STD*)root)->Link.Righthigh );
    preorder(root->left);
    preorder(root->right);
}

int main()
{
    STD *class1[10];
    char class_name[20] = "ABCDEFGHIJ";
    int class_score[10] = {21, 34, 45, 90, 81, 12, 66, 77, 88, 99};
    int (*c)(void *, void *) = &cmp;
    int (*f)(void *, void *) = &Find;

    for(int i=0; i<10; i++)
        class1[i] = init(class_name[i], class_score[i]);

    node *root = NULL;
    for(int i=0; i<10; i++)
    {
        insert_node(&root, class1[i], c);
    }

    int i=0;
    while(root)
    {
        node *temp = find_node(root, class1[i++], f);
        Delete_node(temp, &root);
        inorder(root);
        printf("\n");
        preorder(root);
        printf("\n");
    }
    printf("finish");
    return 0;
}