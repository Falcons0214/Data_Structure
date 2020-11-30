#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct queue queue;
typedef struct Node Node;

struct Node
{
    int data;
    Node *next;
};

struct queue
{
    Node *head, *tail;
};

void push(queue *list, int data)
{
    Node *temp = malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;
    if(list->head == NULL && list->tail == NULL)
    {
        list->head = temp;
        list->tail = temp;
    }else{
        list->tail->next = temp;
        list->tail = temp;
    }
}

void pop(queue *list)
{
    if(list->head == NULL)
    {
        printf("NULL!\n");
        return;
    }
    Node *temp = list->head;
    list->head = temp->next;
    free(temp);
}

int insert(int root[20][4], int node)
{
	int f = 0, index = 0;
	while(root[index][0] != -1)
		index ++;
	if(index >= 20)
		return -1;
	if(index == 0)
	{
		root[0][0] = 1;
		root[0][1] = node;
		return 1;
	}
	else
	{
		root[index][0] = 1;
		root[index][1] = node;
		while(1)
		{
			if(root[f][1] < node)
			{
				if(root[f][3] == -1)
				{
					root[f][3] = index;
					return 1;
				}
				else
				{
					f = root[f][3];
				}
			}
			else
			{
				if(root[f][2] == -1)
				{
					root[f][2] = index;
					return 1;
				}
				else
				{
					f = root[f][2];
				}
			}
		}
	}
}

void inorder(int root[20][4], int index)
{
    if(root[index][2] != -1)
        inorder(root, root[index][2]);
    printf("%d ", root[index][1]);
    if(root[index][3] != -1)
        inorder(root, root[index][3]);
    return ;
}

void preorder(int root[20][4], int index)
{
    printf("%d ", root[index][1]);
    if(root[index][2] != -1)
        inorder(root, root[index][2]);
    if(root[index][3] != -1)
        inorder(root, root[index][3]);
    return ;
}

void postorder(int root[20][4], int index)
{
    if(root[index][2] != -1)
        inorder(root, root[index][2]);
    if(root[index][3] != -1)
        inorder(root, root[index][3]);
    printf("%d ", root[index][1]);
    return ;
}

void levelorder(int root[20][4])
{
    queue list;
    list.head = NULL; list.tail = NULL;
    push(&list, 0);

    while(list.head != NULL)
    {
        printf("%d ", root[list.head->data][1]);
        if(root[list.head->data][2] != -1)
            push(&list, root[list.head->data][2]);
        if(root[list.head->data][3] != -1)
            push(&list, root[list.head->data][3]);
        pop(&list);
    }
}

int main()
{
	int tree[20][4];
	int j, k, node;
	srand(time(NULL));

	for(j = 0;j < 20;j ++)
		for(k = 0;k < 4;k ++)
			tree[j][k] = -1;

	for(j = 0;j < 10;j ++)
	{
		node = rand() % 100;
		insert(tree, node);
	}

	inorder(tree, 0);
	printf("\n");

	preorder(tree, 0);
	printf("\n");

	postorder(tree, 0);
	printf("\n");

	levelorder(tree);
	printf("\n");

    return 0;
}
