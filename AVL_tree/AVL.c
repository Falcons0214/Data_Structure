#include <stdio.h>
#include <stdlib.h>

// define data structure
typedef struct node node;

struct node
{
    int data;
    int left_high, right_high;
    node *left, *right, *parent;
};

// Pivot node
node Pivot;

// init func
node *getnode(int x)
{
    node *temp = (node*)malloc(sizeof(node));
    temp->data = x, temp->left_high = 0, temp->right_high = 0;
    temp->left = NULL, temp->parent = NULL, temp->right = NULL;
    return temp;
}

// updata high func
int leftHigh(node *root)
{
    int high = 0;
    while(root->left)
        root = root->left, high ++;
    return high;
}

int rightHigh(node *root)
{
    int high = 0;
    while(root->right)
        root = root->right, high ++;
    return high;
}

void updata_high(node *root)
{
    if( !root )
        return ;
    root->left_high = leftHigh(root);
    root->right_high = rightHigh(root);
    //printf("qwe %d %d %d\n", root->data, root->left_high, root->right_high);
    updata_high(root->left);
    updata_high(root->right);
}

// Balance func
void LeftRotation(node *root)
{
    node *right_child = root->right, *parent = root->parent;
    if( parent->left == root )
        parent->left = right_child;
    else
        parent->right = right_child;
    
    right_child->parent = parent;

    root->right = right_child->left;
    if(right_child->left != NULL)
        (right_child->left)->parent = root;
    right_child->left = root;
    root->parent = right_child;
}

void RightRotation(node *root)
{
    node *left_child = root->left, *parent = root->parent;
    if( parent->left == root )
        parent->left = left_child;
    else
        parent->right = left_child;
    
    left_child->parent = parent;

    root->left = left_child->right;
    if( left_child->right != NULL )
        (left_child->right)->parent = root;
    left_child->right = root;
    root->parent = left_child;
}

node *findup(node *root) // if return  NULL -> tree is balance else rotation 
{
    while(1)
    {
        if(root == NULL)
            return NULL;
        if( abs(root->right_high - root->left_high) >= 2 )
            return root;
        root = root->parent;
    }
}

int high_gap(node *root)
{
    return (root->left_high - root->right_high);
}

void keepBalance(node *root)
{
    node *cur = findup(root);
    if (cur == NULL)
        return ;
    //printf("%d %d\n", cur->left_high, cur->right_high);
    node *left_child = cur->left, *right_child = cur->right;
    if ( high_gap(cur) >= 2 )           // left >> right
    {
        if( high_gap(left_child) > 0 )  // LL
            RightRotation(cur);
        else
        {   // LR
            LeftRotation(left_child);
            RightRotation(cur);
        }
    }else{                              // right >> left
        if( high_gap(right_child) < 0 ) // RR
            LeftRotation(cur);
        else
        {   // RL
            RightRotation(right_child);
            LeftRotation(cur);
        }
    }
}

// Tree operate func
void insert(node *root, int data)
{
    node *cur = root, *temp = getnode(data);
    if( root == NULL )
    {
        root = temp;
        Pivot.left = root;
        root->parent = &Pivot;
        return ;
    }
    while(1)
    {
        if( cur->data < data )
        {
            if( cur->right == NULL )
            {
                cur->right = temp;
                temp->parent = cur;
                updata_high(root);
                keepBalance(temp);
                break;
            }
            cur = cur->right;
        }else{
            if( cur->left == NULL)
            {
                cur->left = temp;
                temp->parent = cur;
                updata_high(root);
                keepBalance(temp);
                break;
            }
            cur = cur->left;
        }
    }
}

node *find_min(node* root)
{
    while(root->left)
        root = root->left;
    return root;
}

node *find_max(node *root)
{
    while(root->right)
        root = root->right;
    return root;
}

void delete_node(node *root)
{
    node *temp;
    if( root->left )
    {
        temp = find_max(root->left);
        root->data = temp->data;
        delete_node(temp);
    }else if( root->right ){
        temp = find_min(root->right);
        root->data = temp->data;
        delete_node(temp);
    }else{
        temp = root->parent;
        if( temp->left == root )
            temp->left = NULL;
        else
            temp->right = NULL;        
        free(root);
        updata_high(Pivot.left);
        keepBalance(temp);
    }
}

node *search(node *root, int tar)
{
    while(1)
    {
        if( !root )
            return NULL;
        if( root->data == tar )
            return root;
        if( root->data < tar )
            root = root->right;
        else
            root = root->left;
    }
}

// traversal func
void preorder(node *root)
{
    if( !root )
        return ;
    printf("data:%d left:%d right:%d\n", root->data, root->left_high, root->right_high);
    preorder(root->left);
    preorder(root->right);
}

void inorder(node *root)
{
    if( !root )
        return ;
    inorder(root->left);
    printf("data:%d left:%d right:%d\n", root->data, root->left_high, root->right_high);
    inorder(root->right);
}

int main()
{
    node *root = NULL;
    int num[10] = {4, 5, 7, 1, 2, 8, 9, 0, 3, 6};

    Pivot.parent = NULL;
    insert(root, num[0]);

    for(int i=1; i<10; i++){
        insert(Pivot.left, num[i]);
        //preorder(Pivot.left);
        //printf("\n");
    }

    preorder(Pivot.left);
    printf("\n");
    inorder(Pivot.left);
    printf("\n");
    /*
    for(int i=0; i<10; i++)
    {
        node *temp = search(Pivot.left, i);
        if(temp)
            printf("%d\n", temp->data);
    }
    */
    node *del;
    del = search(Pivot.left, 9);
    delete_node(del);
    del = search(Pivot.left, 5);
    delete_node(del);

    preorder(Pivot.left);
    printf("\n");
    inorder(Pivot.left);
    printf("\n");

    return 0;
}
