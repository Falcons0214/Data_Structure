#ifndef AVL
#define AVL

typedef struct node node;

struct node
{
    node *parent;
    node *left;
    node *right;
    int Lefthigh, Righthigh;
};

void insert_node(node **root, void *element, int(*cmp)(void *, void *));
void Delete_node(node *del, node **root);
node *find_node(node *root, void *target, int(*check)(void *, void *));

#endif