#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "AVL.h"

static void LeftRotation(node *cur, node **root)
{
    node *Right_node = cur->right, *parent_node = cur->parent;
    if( cur == (*root) )
        (*root) = Right_node;

    if( parent_node != NULL )
    {
        if( parent_node->left == cur )
            parent_node->left = Right_node;
        else
            parent_node->right = Right_node;
    }
    Right_node->parent = parent_node;

    cur->right = Right_node->left;
    if( Right_node->left != NULL )
        (Right_node->left)->parent = cur;
    
    Right_node->left = cur;
    cur->parent = Right_node;
}

static void RightRotation(node *cur, node **root)
{
    node *Left_node = cur->left, *parent_node = cur->parent;

    if( cur == (*root) )
        (*root) = Left_node;

    if( parent_node != NULL )
    {
        if( parent_node->left == cur )
            parent_node->left = Left_node;
        else
            parent_node->right = Left_node;
    }
    Left_node->parent = parent_node;

    cur->left = Left_node->right;
    if( Left_node->right != NULL )
        (Left_node->right)->parent = cur;
    
    Left_node->right = cur;
    cur->parent = Left_node;
}

static int get_gap(node *A)
{
    return (A->Lefthigh - A->Righthigh);
}

static node *find_up(node *leaf)
{
    while(1)
    {
        if( !leaf ) return NULL;
        if(  abs(get_gap(leaf)) >= 2 ) return leaf;
        leaf = leaf->parent;
    }
}

static void Backward(node *leaf, node **root) // Backward
{
    node *cur = find_up(leaf);
    if( !cur ) return;
    node *root_L = cur->left, *root_R = cur->right;
    if( get_gap(cur) >= 2 )
    {
        if( get_gap(root_L) > 0 )
            RightRotation(cur, root);
        else
        {
            LeftRotation(root_L, root);
            RightRotation(cur, root);
        }
    }else{
        if( get_gap(root_R) < 0 )
            LeftRotation(cur, root);
        else
        {
            RightRotation(root_R, root);
            LeftRotation(cur, root);
        }
    }
}

static int Max(node *A, node *B)
{
    if(A && B)
        return ( (A->Hight) > (B->Hight) )? (A->Hight) : (B->Hight);
    if(A)
        return A->Hight;
    if(B)
        return B->Hight;
    return 0;
}

static int getBalance(node * A)
{
    if( A == NULL )
        return 0;
    if( A->left && A->right )
        return ((A->left->Hight) - (A->right->Hight));
    if( A->left )
        return A->left->Hight;
    if( A->right )
        return A->right->Hight;
    return 0;
}

static void Forward(node *temp, node **root)
{
    if( !temp ) 
        return;
    Forward(temp->left, root);
    Forward(temp->right, root);
    temp->Hight = 1 + Max(temp->left, temp->right);

    int balance = getBalance(temp);
    //printf("ww %d\n", balance);
    if(balance > 1 && temp->left->Hight > temp->right->Hight )
    {
        LeftRotation(temp->left , root);
        RightRotation(temp , root);
    }
    if(balance < -1 && temp->left->Hight < temp->right->Hight ) 
    {
        RightRotation(temp->right , root);
        LeftRotation(temp , root);
    }
}

static int FindLeftHigh(node *root)
{
    int high = 0;
    while(root->left)
    {
        root = root->left;
        high ++;
    }
    return high;
}

static int FindRightHigh(node *root)
{
    int high = 0;
    while(root->right)
    {
        root = root->right;
        high ++;
    }
    return high;
}

static void UpdataHight(node *root)
{
    if(!root) 
        return;
    root->Lefthigh = FindLeftHigh(root);
    root->Righthigh = FindRightHigh(root);
    UpdataHight(root->left);
    UpdataHight(root->right);
}

void insert_node(node **root, void *element, int(*cmp)(void *, void *))
{
    node *cur = (*root);
    if( cur == NULL )
    {
        (*root) = ((node*)element);
        return;
    }
    while(1)
    {
        if( cmp( cur, element ) )
        {
            if( cur->left == NULL )
            {
                cur->left = ((node*)element);
                ((node*)element)->parent = cur;
                UpdataHight(*root);
                Backward(cur->left, root);
                Forward((*root), root);
                break;
            }
            cur = cur->left;
        }else{
            if( cur->right == NULL )
            {
                cur->right = ((node*)element);
                ((node*)element)->parent = cur;
                UpdataHight(*root);
                Backward(cur->right, root);
                Forward((*root), root);
                break;
            }
            cur = cur->right;
        }
    }
}

static node *find_min(node *root)
{
    while(root->left)
        root = root->left;
    return root;
}

static node *find_max(node *root)
{
    while(root->right)
        root = root->right;
    return root;
}

static void connect(node *root, node *temp)
{   
    if( (root->parent) != NULL )
    {
        if( (root->parent)->left == root )
            (root->parent)->left = temp;
        else
            (root->parent)->right = temp;
    }
    if(root->left != temp && root->left != NULL)
        (root->left)->parent = temp;
    if(root->right !=temp && root->right != NULL)
        (root->right)->parent = temp;
    temp->parent = root->parent;
    temp->left = root->left;
    temp->right = root->right;
}

static void Delete(node *del, node **leaf)
{
    if( del->right )
    {
        node *temp = find_min(del->right);
        Delete(temp, leaf);
        connect(del, temp);
    }else if( del->left ){
        node *temp = find_max(del->left);
        Delete(temp, leaf);
        connect(del, temp);
    }else{
        if( (del->parent) != NULL)
        {
            if( (del->parent)->left == del )
                (del->parent)->left = NULL;
            else
                (del->parent)->right = NULL;
            (*leaf) = del;
        }else
            *leaf = NULL;
    }
}

void Delete_node(node *del, node **root) 
{
    node *leaf;
    if( del == (*root) )
    {
        if( (*root)->right )
            (*root) = find_min(del->right);
        else if( (*root)->left )
            (*root) = find_max(del->left);
        else{
            (*root) = NULL;
            return ;
        }
    }
    Delete(del, &leaf);
    UpdataHight(*root);
    Backward(leaf, root);
    Forward((*root), root);
}
 
node *find_node(node *root, void *element, int(*check)(void *, void *))
{
    while(1)
    {
        if( root == NULL)
            return NULL;
        if( check( ((void*)root), element ) == 3 )
            return root;
        if( check( ((void*)root), element ) == 2 )
            root = root->left;
        else
            root = root->right; 
    }
}