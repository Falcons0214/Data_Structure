#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct node node;

struct node
{
    node *parent;
    node *left;
    node *right;
    int Lefthigh, Righthigh;
};

typedef struct student STD;

struct student
{
    node Link;
    char id;
    int score;
};

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

static void KeepBalance(node *leaf, node **root)
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
                KeepBalance(cur->left, root);
                break;
            }
            cur = cur->left;
        }else{
            if( cur->right == NULL )
            {
                cur->right = ((node*)element);
                ((node*)element)->parent = cur;
                UpdataHight(*root);
                KeepBalance(cur->right, root);
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
    KeepBalance(leaf, root);
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