#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Node Node;
typedef struct queue queue;
typedef struct cell cell;

struct Node
{
	int data;
	Node *left, *right;
};

struct cell
{
    Node *node;
    cell *next;
    cell *prev;
};

struct queue
{
    cell *head; // queue head pointer
    cell *tail; // queue tail pointer
    cell *cur; // queue slow pointer
};

Node *getNode(int data) // init tree node
{
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->right = NULL, temp->left = NULL;
    return temp;
}

cell *getCell(Node *temp) // init queue node
{
    cell *node = (cell*)malloc(sizeof(cell));
    node->node = temp;
    node->next = NULL;
    node->prev = NULL;
    return node;
}
/*
Function getHeight take one parameter represent a tree root
and return an integer as the height of the tree.
*/
int getHeight(Node *root)
{
    int height = 0;
    while(root)
    {
        root = root->left;
        height += 1;
    }
    return height;
}

void MaxHeapify(Node *root)
{
    if( root->left == NULL && root->right == NULL)
        return ;
    Node *node = root->left;
    if(root->left != NULL && root->right != NULL)
    {
        if( root->left->data > root->right->data )
            node = root->left;
        else
            node = root->right;
    }
    if( node->data > root->data )
    {
        int temp = node->data;
        node->data = root->data;
        root->data = temp;
    }
    if( root->left != NULL || root->right != NULL )
        MaxHeapify(node);
}

void Build_Max_Heap(queue *list)
{
    cell *temp;
    if(list->cur != NULL)
    {
        if(list->cur->node->left != NULL)
            temp = list->cur;
        else
            temp = list->cur->prev;
    }else{
        temp = list->head;
    }
    while(temp)
    {
        MaxHeapify(temp->node);
        temp = temp->prev;
    }
}
/*
Function insert take parament root represent a maximum heap and insert data
into the maximum heap.
*/
void insert(Node **root, int data, queue *list) // insert -> last location of level order
{
    Node *temp_node = getNode(data);
    cell *temp_cell = getCell(temp_node);
    if( (*root) == NULL )
    {
        (*root) = temp_node;
        list->head = temp_cell;
        list->tail = temp_cell;
        list->cur = temp_cell;
    }else{
        if(list->cur->node->left == NULL)
        {
            list->cur->node->left = temp_node;
        }else{
            list->cur->node->right = temp_node;
            list->cur = list->cur->next;
        }
        list->tail->next = temp_cell;
        temp_cell->prev = list->tail;
        list->tail = temp_cell;
    }
    Build_Max_Heap(list);
}
/*
Function remove take parament root represent a maximum heap and remove the root
from heap.
Please keep the heap as a maximum heap while removing the root.
Return the data you removed.
If there is nothing in the heap, return NULL.
*/
Node *remove(Node **root, queue *list) // remove from tree root
{
    if(list->tail == NULL)
        return NULL;
    Node *node = getNode(0);
    Node *temp = list->tail->node;
    if(list->head->node->right == NULL && list->head->node->left == NULL)
    {
        node->data = list->head->node->data;
        free(temp);
        list->head = NULL;
        list->tail = NULL;
        *root = NULL;
        return node;
    }
    node->data = list->head->node->data;
    list->head->node->data = list->tail->node->data;
    list->tail = list->tail->prev;
    list->tail->next = NULL;
    if(list->cur->node->left == NULL && list->cur->prev != NULL)
        list->cur = list->cur->prev;
    if(list->cur->node->right == temp)
    {
        list->cur->node->right = NULL;
    }else{
        list->cur->node->left = NULL;
        list->cur = list->cur->prev;
    }
    free(temp);
    Build_Max_Heap(list);
    return node;
}

void inorder(Node *root)
{
    if(!root)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int main()
{
    int j, num;
    Node *heap = NULL, *k;
    queue list;
    list.head = NULL, list.tail = NULL;

	//srand(time(NULL));
	for(j = 0;j < 10;j ++)
    {
        num = rand()%10;
        //printf("insert : %d\n", num);
		insert(&heap, num, &list);
        inorder(heap);
        printf("\n");
    }

    while(1)
    {
	    k = remove(&heap, &list);
        if(k == NULL)
            break;
	    printf("%d(%d) ", k->data, getHeight(heap));
    }
    printf("\n");
    for(j = 0;j < 10;j ++)
    {
        num = rand()%10; 
		insert(&heap, num, &list);
        inorder(heap);
        printf("\n");
    }

    return 0;
}