#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//data type
typedef struct node node;
typedef struct student student;

struct node
{
    node *parent;
    node *left, *right;
};

struct student
{
    node link;
    int grade;
    char name;
};

//function for special case
void *to_void(void *node)
{
    return (void*)node;
}

void print_node(void *node)
{
    printf("%c ", ((student*)node)->name);
}

int comp(void *node1, void *node2)
{
    if( ((student*)node1)->grade > ((student*)node2)->grade )
        return 1;
    return 0;
}

int find(void *node1, void *node2)
{
    if( ((student*)node1)->name == ((student*)node2)->name )
        return 1;
    return 0;
}

int equ(void *node1, void *node2)
{
    if( ((student*)node1)->grade == ((student*)node2)->grade )
        return 1;
    return 0;
}

// lib function
void insert_node(node **root, void *element,  int(*compare)(void *, void *))
{
    if( (*root) == NULL )
    {
        (*root) = ((node*)element);
        return ;
    }else{
        node *temp = *root;
        while(1)
        {
            if( compare(temp, element) )
            {
                if( temp->left == NULL )
                {
                    temp->left = ((node*)element);
                    ((node*)element)->parent = temp;
                    break;
                }else{
                    temp = temp->left;
                }
            }else{
                if( temp->right == NULL )
                {
                    temp->right = ((node*)element);
                    ((node*)element)->parent = temp;
                    break;
                }else{
                    temp = temp->right;
                }
            }
        }
    }
}

node *find_max(node *root)
{
    while(root->right != NULL)
        root = root->right;
    return root;
}

node *find_min(node *root)
{
    while(root->left != NULL)
        root = root->left;
    return root;
}

node *inorder_successor(node *current)
{
    if(current->right != NULL)// if cur->right_child != NULL, find the min from cur(relative root)
        return find_min(current->right);
    node *temp = current->parent;
    while(1)
    {
        if(temp->left == current)
        {
            return temp;
        }else{
            current = current->parent;
            temp = current->parent;
        }
    }
}

node *find_node(node *root, void *tar, int(*check)(void*, void*))
{
    node *cur = find_min(root); 
    while(1)// use inorder traversal
    {
        if( check(cur, tar) )
            return cur;
        if(cur->right == find_max(root) && cur->left == NULL) // if not find -> break out
            break;
        cur = inorder_successor(cur);
    }
    return NULL;
}

void connect(node *root, node *temp)
{
    if( (root->parent)->left == root )
        (root->parent)->left = temp;
    else
        (root->parent)->right = temp;
    if(root->left != temp && root->left != NULL)
        (root->left)->parent = temp;
    if(root->right != temp && root->right != NULL)
        (root->right)->parent = temp;
    temp->parent = root->parent;
    temp->left = root->left;
    temp->right = root->right;
}

void delete_node(void *root)
{
    if( ((node*)root)->right != NULL )
    {
        node *temp = find_min( ((node*)root)->right );
        delete_node(to_void(temp));
        connect((node*)root, temp); 
    }else if( ((node*)root)->left != NULL ){
        node *temp = find_max( ((node*)root)->left );
        delete_node(to_void(temp));
        connect((node*)root, temp);
    }else{
        if( (((node*)root)->parent)->left == ((node*)root) )
            (((node*)root)->parent)->left = NULL;
        else
            (((node*)root)->parent)->right = NULL;
    }
}

void *delete_root(void *root)
{
    node *temp;
    if( ((node*)root)->right )
        temp = find_min( ((node*)root)->right );
    else
        temp = find_max( ((node*)root)->left );
    delete_node(to_void(temp));
    temp->parent = NULL;
    temp->left = ((node*)root)->left;
    temp->right = ((node*)root)->right;
    if( ((node*)root)->left != NULL )
        ((node*)root)->left->parent = temp;
    if( ((node*)root)->right != NULL )
        ((node*)root)->right->parent = temp; 
    return temp;
}

void tree_copy(node **new_root, node *origin_root, int node_size)
{
    if(origin_root == NULL)
        return ;
    void *temp = malloc(sizeof(char) * node_size); // node_size -> user defind struct size 
    memcpy(temp, origin_root, node_size);
    *new_root = (node*)temp;
    tree_copy(&(*new_root)->left, origin_root->left, node_size);
    tree_copy(&(*new_root)->right, origin_root->right, node_size);
}

int tree_equal(node *root1, node *root2, int(*equal)(void*, void*))
{
    node *flag = find_max(root1);
    root1 = find_min(root1); 
    root2 = find_min(root2);
    while(1)
    {
        if( !equal(root1, root2) )
            return 0;
        if( equal(root1, flag) && equal(root2, flag) )
            break;
        root1 = inorder_successor(root1);
        root2 = inorder_successor(root2);
    }
    return 1;
}

void inorder(node *root, void(*print)(void *))
{
    if(root == NULL)
        return ;
    inorder(root->left, print);
    print(root);
    inorder(root->right, print);
}

int main()
{
    student num[9];
    student num2[9];
    int (*alpha)(void*, void*) = &comp;
    void (*out)(void*) = &print_node;
    int (*search)(void*, void*) = &find;
    int (*e)(void*, void*) = &equ;

    num[0].grade = 2; num[1].grade = 1; num[2].grade = 5;
    num[3].grade = 6; num[4].grade = 3; num[5].grade = 4;
    num[6].grade = 9; num[7].grade = 7; num[8].grade = 8;

    num[0].name = 'A'; num[1].name = 'B'; num[2].name = 'C';
    num[3].name = 'D'; num[4].name = 'E'; num[5].name = 'F';
    num[6].name = 'G'; num[7].name = 'H'; num[8].name = 'I';

    num2[0].grade = 2; num2[1].grade = 1; num2[2].grade = 5;
    num2[3].grade = 6; num2[4].grade = 3; num2[5].grade = 4;
    num2[6].grade = 10; num2[7].grade = 7; num2[8].grade = 8;

    num2[0].name = 'A'; num2[1].name = 'B'; num2[2].name = 'C';
    num2[3].name = 'D'; num2[4].name = 'E'; num2[5].name = 'F';
    num2[6].name = 'G'; num2[7].name = 'H'; num2[8].name = 'I';

    for(int i=0; i<9; i++)
    {
        (num[i].link).parent = NULL;
        (num[i].link).left = NULL;
        (num[i].link).right = NULL;
        (num2[i].link).parent = NULL;
        (num2[i].link).left = NULL;
        (num2[i].link).right = NULL;
    }

    node *root = NULL, *root2 = NULL;
    for(int i=0; i<9; i++)
    {
        insert_node(&root, to_void(&num[i]), alpha);
        insert_node(&root2, to_void(&num2[i]), alpha);
    }

    inorder(root, out);
    printf("\n");

    node *temp = find_max(root);
    temp = find_node(root, to_void(&num[1]), search);
    
    print_node(temp);
    printf("\n");
    /*
    node *nr = NULL;
    tree_copy(&nr, root, sizeof(student));

    inorder(nr, out);
    */
    /*
    if( tree_equal(root, root2, e) )
    {
        printf("Tree is equal!\n");
    }else{
        printf("Not equal!\n");
    }
    */
    
    delete_node(to_void(&num[6]));
    free(&num[6]);
    inorder(root, out);
    printf("\n");
    
    delete_node(to_void(&num[3]));
    free(&num[3]);
    inorder(root, out);
    printf("\n");

    delete_node(to_void(&num[4]));
    free(&num[4]);
    inorder(root, out);
    printf("\n");
    
    delete_node(to_void(&num[1]));
    free(&num[1]);
    inorder(root, out);
    printf("\n");

    delete_node(to_void(&num[8]));
    free(&num[1]);
    inorder(root, out);
    printf("\n");

    delete_node(to_void(&num[7]));
    free(&num[1]);
    inorder(root, out);
    printf("\n");

    delete_node(to_void(&num[5]));
    free(&num[1]);
    inorder(root, out);
    printf("\n");
    
    /*
    void *kk = delete_root(to_void(root));
    free(root);
    root = (node*)kk;
    inorder(root, out);
    printf("\n");

    void *pp = delete_root(to_void(root));
    free(root);
    root = (node*)pp;
    inorder(root, out);
    printf("\n");
    
    void *ppg = delete_root(to_void(root));
    free(root);
    root = (node*)ppg;
    inorder(root, out);
    printf("\n");

    void *ppgg = delete_root(to_void(root));
    free(root);
    root = (node*)ppgg;
    inorder(root, out);
    printf("\n");
    */ 
    return 0;
}