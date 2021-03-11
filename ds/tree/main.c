#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMESIZE 32

struct stu_st {
	int id;
	char name[NAMESIZE];
};

struct node_st {
	struct stu_st data;
	struct node_st *left;
	struct node_st *right;
};

//插入新结点
static int treeInsert(struct node_st **root,const struct stu_st *data)
{
	struct node_st *new;

	if(*root == NULL)
	{
		new = malloc(sizeof(*new));
		if(new == NULL)
			return -1;
		memcpy(&new->data, data, sizeof(struct stu_st));
		new->left = new->right = NULL;
		*root = new;
		return 0;
	}
	if(data->id <= (*root)->data.id)
	{
		return treeInsert(&(*root)->left, data);
	}
	else
	{
		return treeInsert(&(*root)->right, data);
	}
}

static void treeMidTraval(const struct node_st *root)
{
	if(root == NULL)
		return;
	treeMidTraval(root->left);
	printf("%d %s \n", root->data.id, root->data.name);
	treeMidTraval(root->right);
}

static void treeDestroy(struct node_st **root)
{
	if(*root == NULL)
		return;
	treeDestroy(&(*root)->left);
	treeDestroy(&(*root)->right);
	printf("%d\n", (*root)->data.id);
	free((*root));
	*root = NULL;
}


int main(void)
{
	struct node_st *t = NULL;
	struct stu_st stu;
	
	int ids[] = {8,3,2,1,6,9,4,7,3,5,10};

	for(int i = 0; i < sizeof(ids)/sizeof(*ids); i++)
	{
		stu.id = ids[i];
		snprintf(stu.name, NAMESIZE, "stu%d", ids[i]);
		treeInsert(&t, &stu);
	}

	treeMidTraval(t);
	treeDestroy(&t);
	return 0;
}



