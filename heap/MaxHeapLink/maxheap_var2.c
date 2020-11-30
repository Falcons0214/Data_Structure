#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// define data sturct and node
typedef struct tree_node tree_node;
typedef struct list_node list_node;
typedef struct List List;          

struct tree_node
{
    tree_node *left, *right, *parent;
    int data;
};

struct list_node
{
    list_node *next, *prev;
    tree_node *node;
};

struct List
{
    list_node *head, *tail, *slow;
};

// define traversal function 
void inorder(tree_node *root)
{
    if( !root )
        return ;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

//define init function
tree_node *get_TreeNode(int key) 
{
    tree_node *temp = (tree_node*)malloc(sizeof(tree_node));
    temp->data = key;            
    temp->left = NULL, temp->right = NULL, temp->parent = NULL;
    return temp;
}

list_node *get_QueueNode(tree_node *key) 
{
    list_node *temp = (list_node*)malloc(sizeof(list_node));
    temp->node = key;
    temp->next = NULL, temp->prev = NULL;
    return temp;
}

// define queue function
void push(List *list, tree_node *key) 
{
    list_node *temp = get_QueueNode(key);
    if( list->head == NULL )
    {
        list->head = temp, list->tail = temp, list->slow = temp;
    }
    list->tail->next = temp;
    temp->prev = list->tail;
    list->tail = temp;
}

void pop_from_tail(List *list, tree_node **root)
{
    if( list->head == NULL )
        return ;
    list_node *temp = list->tail; // move tail to the previous node
    list_node **slow = &(list->slow);
    if( list->head != list->tail )
    {
        list->tail = temp->prev;
        list->tail->next = NULL;

        if(list->slow->node->left == NULL) // "slow(pointer to the next insert(level order) location)"
            *slow = list->slow->prev;

        if( (*slow)->node->right == temp->node) 
            (*slow)->node->right = NULL;
        else
            (*slow)->node->left = NULL;
    }else{
        (*root) = NULL;
        list->head = NULL, list->tail = NULL, list->slow = NULL;
    }
    free(temp->node), free(temp);
}

//define Maxheap function
int height(tree_node *root)
{
    int height = 0;
    while(root)
    {
        height ++;
        root = root->left;
    }
    return height;
}

void Maxheapify(tree_node *root)
{
    if(!root)
        return;
    if( root->left != NULL && root->right != NULL)
    {
        tree_node *max = root->left;
        if( root->right != NULL)
        {
            if( root->left->data > root->right->data )
                max = root->left;
            else
                max = root->right;
        }
        if( max->data > root->data )
        {
            int temp = max->data;
            max->data = root->data;
            root->data = temp;
        }
        Maxheapify(max);
    }
}

void find_top(tree_node *leaf)
{
    if( !(leaf->parent) )
        return;
    if( leaf->data > leaf->parent->data )
    {
        int temp = leaf->data;
        leaf->data = leaf->parent->data;
        leaf->parent->data = temp;
        find_top(leaf->parent);
    }
}

void insert_heap(tree_node **root, List *list, int key)
{
    tree_node *temp = get_TreeNode(key);
    push(list, temp);
    if( (*root) == NULL )
    {
        (*root) = temp;
        return ;
    }
    temp->parent = list->slow->node;
    if(list->slow->node->left == NULL){
        list->slow->node->left = temp;
    }else{
        list->slow->node->right = temp;
        list->slow = list->slow->next;
    }
    find_top(temp);
}

tree_node *remove_root(tree_node **root, List *list)
{
    if( (*root) == NULL )
        return NULL;
    tree_node *max = get_TreeNode( (*root)->data );
    (*root)->data = list->tail->node->data;
    pop_from_tail(list, root);
    Maxheapify( (*root) );
    return max;
}

// test
int main()
{
    tree_node *heap = NULL, *top_node;
    List list;
    list.head = NULL, list.tail = NULL, list.tail = NULL;

    //srand(time(NULL));
    for(int i=0; i<11; i++)
    {
        int num = rand()%10;
        insert_heap(&heap, &list, num);
    }

    inorder(heap);
    printf("\n");

    while(1)
	{
		top_node = remove_root(&heap, &list);
        if( !top_node )
            break;
		printf("value : %d (%d)\n", top_node->data, height(heap));
        free(top_node);
	}

    return 0;
}