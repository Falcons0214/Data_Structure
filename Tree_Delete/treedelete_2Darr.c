#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

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

void inorder(int root[20][4], int row)
{
    if(row == -1)
		return ;
    inorder(root, root[row][2]);
    printf("%d ", root[row][1]);
	inorder(root, root[row][3]);
}
/*
Function removal will remove all the node tree content data n.
The return value of function removal is a integer represent how many node are removed.
*/
// root[0][0] => 0 no data, 1 have data
// root[0][1] => save data
// root[0][2] => left child
// root[0][3] => right child

int search(int root[20][4], int tar, int *par)
{
	int row = 0;
	while(1)
	{
		if( row == -1 )
			return 0;
		if( root[row][1] == tar )
			return row;
		if( root[row][1] < tar ){
			*par = row;
			row = root[row][3];
		}else{
			*par = row;
			row = root[row][2];
		}
	}
}
/*
int find_parent(int root[20][4], int now, int head)
{
	while(1)
	{
		if(root[head][2] == now || root[head][3] == now)
			break;
		if(root[now][1] > root[head][1])
		{
			head = root[head][3];
		}else{
			head = root[head][2];
		}
	}
	return head;
}
*/
/*
int find_parent(int root[20][4], int now, int head)
{
	if(root[head][2] == now || root[head][3] == now)
		return head;
	if(root[now][1] > root[head][1])
		find_parent(root, now, root[head][2]);
	else
		find_parent(root, now, root[head][3]);
}

int find_parent(int root[20][4], int now)
{
	for(int i=0; i<20; i++)
	{
		if(root[i][2] == now || root[i][3] == now)
			return i;
	} 
}

int find_parent(int root[20][4], int row, int head)
{
	if(root[head][2] == row || root[head][3] == row)
		return head;
	else
		find_parent(root, row, head++);	
}
*/
int find_min(int root[20][4], int row, int *par)
{
	while(1)
	{
		if( root[row][2] == -1)
			return row;
		*par = row;
		row = root[row][2];
	}
}

int find_max(int root[20][4], int row, int *par)
{
	while(1)
	{
		if( root[row][3] == -1 )
			return row;
		*par = row;
		row = root[row][3];
	}
}

void del_node(int root[20][4], int row, int par)
{
	if( root[row][3] != -1 )
	{
		par = row;
		int mostleft = find_min(root, root[row][3], &par);
		root[row][1] = root[mostleft][1];
		del_node(root, mostleft, par);
	}else if( root[row][2] != -1 ){
		par = row;
		int mostright = find_max(root, root[row][2], &par);
		root[row][1] = root[mostright][1];
		del_node(root, mostright, par);
	}else{
		if(root[par][2] == row)
			root[par][2] = -1;
		else
			root[par][3] = -1;
		root[row][1] = -1;
		root[row][0] = -1;
	}
}

int removal(int root[20][4], int n)
{
	int count = 0, par;
	while(1)
	{
		par = 0;
		int temp = search(root, n, &par), flag = 0;
		if(root[0][1] == n) // when target is root, flag -> 1
			flag = 1;
		if(flag != 1 && !temp)
			break;
		del_node(root, temp, par);
		count ++;
	}
	return count;
}

typedef struct node node;

struct node
{
	int i;
	float h;
	node *next;
};

int main()
{
	int tree[20][4];
	int j, k, l, node;
	srand(time(NULL));
	
	for(j = 0;j < 20;j ++)
		for(k = 0;k < 4;k ++)
			tree[j][k] = -1;
	
	for(j = 0;j < 10;j ++)
	{
		node = rand() % 10;
		insert(tree, node);
	}

	inorder(tree, 0);
	printf("\n");
	
	for(j = 0;j < 5;j ++)
	{
		l = rand() % 10;
		k = removal(tree, l);
		printf("Remove %d(%d)\n", l, k);
	}

	inorder(tree , 0);
	printf("\n");

	return 0;
}
