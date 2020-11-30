#include <stdio.h>

typedef struct Node Node;

struct Node
{
    Node *left, *right;
    int power;
};

Node *init_Node(int data);
Node *insert(Node *root, int data);
void recursive_insert(Node **root, Node *node);
Node *search(Node *root, int target);
Node *delete_node(Node *root, int data);//
void traversal(Node *root);

int main()
{
    int n, temp;
    Node *root = NULL;

    scanf("%d", &n);

    for(int i=0; i<n; i++)
    {
        scanf("%d", &temp);
        //root = insert(root, temp);
        recursive_insert(&root, init_Node(temp));
    }

    traversal(root);

    /*
    Node *reg;
    int tar;

    scanf("%d", &tar);

    reg = search(root, tar);

    if(reg != NULL)
        printf("find:%d\n", reg->power);
    else
        printf("NULL\n");
    */

    return 0;
}

Node *init_Node(int data)
{
    Node *temp = malloc(sizeof(Node));
    temp->left = NULL;
    temp->right = NULL;
    temp->power = data;
    return temp;
}

void recursive_insert(Node **root, Node *node)
{
    if((*root) == NULL)
    {
        (*root) = node;
        return;
    }

    if( (*root)->power > node->power && (*root)->left == NULL)
    {
        (*root)->left = node;
        return;
    }
    if( (*root)->power < node->power && (*root)->right == NULL)
    {
        (*root)->right = node;
        return;
    }

    if( (*root)->power > node->power)
        recursive_insert( &(*root)->left, node);
    else if( (*root)->power < node->power)
        recursive_insert( &(*root)->right, node);
}

Node *insert(Node *root, int data)
{
    if(root == NULL)
        return init_Node(data);

    Node *temp = root;
    while(1)
    {
        if(temp->power < data && temp->right != NULL)
            temp = temp->right;
        else if(temp->power > data && temp->left != NULL)
            temp = temp->left;

        if(temp->left == NULL && temp->power > data){
            temp->left = init_Node(data);
            break;
        }else if(temp->right == NULL && temp->power < data){
            temp->right = init_Node(data);
            break;
        }
    }
    return root;
}

Node *search(Node *root, int target)
{
    if(root == NULL)
        return NULL;
    if(root->power < target)
        return search(root->right, target);
    if(root->power > target)
        return search(root->left, target);

    return root;
}

void traversal(Node *root)
{
    if(root == NULL)
        return ;
    //printf("%d\n", root->power);
    traversal(root->left);
    printf("%d\n", root->power);
    traversal(root->right);
}
