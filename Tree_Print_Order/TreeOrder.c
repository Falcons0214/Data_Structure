#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int insert(int root[2000], int node)
{
	int index = 0;
	while(index < 2000 && root[index] != -1)
	{
		if(root[index] < node)
			index = index * 2 + 2;
		else
			index = index * 2 + 1;
	}
	root[index] = node;
}

void inorder(int root[2000], int n)
{
    if(root[n*2+1] != -1)
        inorder(root, n*2+1);
    printf("%d ", root[n]);
    if(root[n*2+2] != -1)
        inorder(root, n*2+2);

    return ;
}

void preorder(int root[2000], int n)
{
    printf("%d ", root[n]);
    if(root[n*2+1] != -1)
        preorder(root, n*2+1);
    if(root[n*2+2] != -1)
        preorder(root, n*2+2);

    return ;
}

void postorder(int root[2000], int n)
{
    if(root[n*2+1] != -1)
        postorder(root, n*2+1);
    if(root[n*2+2] != -1)
        postorder(root, n*2+2);
    printf("%d ", root[n]);

    return ;
}

void levelorder(int root[2000])
{
    for(int i=0; i<2000; i++)
        if(root[i] != -1)
            printf("%d ", root[i]);
}

int main()
{
	int tree[2000];
	int j, k, node;
	srand(time(NULL));

	for(j = 0;j < 2000;j ++)
		tree[j] = -1;

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
}
