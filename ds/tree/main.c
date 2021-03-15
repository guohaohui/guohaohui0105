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

	if(*root == NULL)//如果根为空
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
		return treeInsert(&(*root)->left, data);//插入根的左边
	}
	else
	{
		return treeInsert(&(*root)->right, data);//右边
	}
}

static void treeMidTraval(const struct node_st *root)//中序打印
{
	if(root == NULL)
		return;
	treeMidTraval(root->left);//左
	printf("%d %s \n", root->data.id, root->data.name);//根
	treeMidTraval(root->right);//右
}

static void treeDestroy(struct node_st **root)//销毁
{
	if(*root == NULL)
		return;
	treeDestroy(&(*root)->left);
	treeDestroy(&(*root)->right);
	printf("%d\n", (*root)->data.id);
	free((*root));
	*root = NULL;
}

static void _draw(const struct node_st *root, int level)
{
	if(root == NULL)
		return ;
	_draw(root->right, level+1);
	for(int i = 0; i < level; i++)
		printf("		");
	printf("%d %s \n", root->data.id, root->data.name);
	_draw(root->left, level+1);
}

static void treeDraw(const struct node_st *root)//画树
{
	_draw(root, 0);
}
/*
static int treeDele(struct node_st **root)//删除根结点
{
	struct node_st *me;
	me = (*root)->left;
	struct node_st *wo= me;
	for(;wo->right != NULL;)
		wo = wo->right;
	wo->right = (*root)->right;
	(*root)->left = (*root)->right = NULL;
	*root = me;
}

static int treeDele_t(struct node_st **root, int id)//删除结点
{
	struct node_st **node = root;
	struct node_st *cur = NULL;
	struct node_st *cur1 = NULL;
	while(*node != NULL && (*node)->data.id != id)
	{
		if(id < (*node)->data.id)
			node = &(*node)->left;
		else
			node = &(*node)->right;
	}
	if(*node == NULL)
		return -1;
	cur = *node;
	if(cur->left == NULL)
		*node = cur->right;
	else
	{
		*node = cur->left;
		cur1 = *node;
		while(cur1->right != NULL)
		{
			cur1 = cur1->right;
		}
		cur1->right = cur->right;
	}
	free(cur);
	cur = NULL;
	return 1;
}

*/
static struct node_st **deleteFind(struct node_st **root , int id)//查找
{
	if(*root == NULL)
		return NULL;
	if((*root)->data.id == id)
		return root;
	if((*root)->data.id >= id)
		return deleteFind(&(*root)->left, id);
	else
		return deleteFind(&(*root)->right, id);

}
//找结点中最大的那个
static struct node_st *treeMaxNode(const struct node_st *root)
{
	if(root == NULL)
		return NULL;
	if(root->right == NULL)
		return (struct node_st *)root;
	return treeMaxNode(root->right);
}
//找结点中最小的那个
static struct node_st *treeMinNode(const struct node_st *root)
{
	if(root == NULL)
		return NULL;
	if(root->left == NULL)
		return (struct node_st *)root;
	return treeMinNode(root->left);
}



//删除
static int treeDelete(struct node_st **root, int id)
{
	if(*root == NULL)
		return -1;
	struct node_st **find = deleteFind(root, id);
	struct node_st *left = (*find)->left;
	struct node_st *right = (*find)->right;

	(*find)->left = (*find)->right = NULL;
	free(*find);

	if(left != NULL)
	{
		*find = left;
		if(right != NULL)
		{
			treeMaxNode(left)->right = right;	
		}
	}
	else
	{
		*find = right;
	}

	return 0;
}

//计算结点个数
static int nodenumber(const struct node_st *root)
{
	if(root == NULL)
		return 0;
	return 1+nodenumber(root->left) + nodenumber(root->right);
}

static void treeTurnRight(struct node_st **root)//右平衡
{
	struct node_st *l, *cur;
	cur = *root;
	l = cur->left;

	*root = l;
	cur->left = NULL;
	treeMaxNode(l)->right = cur;
}

static void treeTurnLeft(struct node_st **root)//左平衡
{
	struct node_st *r, *cur;

	cur = *root;
	r = cur->right;

	*root = r;
	cur->right = NULL;
	treeMinNode(r)->left = cur;
}


//平衡二叉树
static void treeBalance(struct node_st **root)
{
	int val;

	if(*root == NULL)
		return ;
	while(1)
	{
		val = nodenumber((*root)->left) - nodenumber((*root)->right);//左子数结点减右子数结点
		if(val > 1)
		{
			treeTurnRight(root);//右平衡
		}
		else if(val < -1)
		{
			treeTurnLeft(root);//左平衡
		}
		else
			break;
	}
	treeBalance(&(*root)->left);
	treeBalance(&(*root)->right);
}

int main(void)
{
	struct node_st *t = NULL;
	struct stu_st stu;
	
	int ids[] = {1,2,3,4,5,6,7,8,9};

	for(int i = 0; i < sizeof(ids)/sizeof(*ids); i++)
	{
		stu.id = ids[i];
		snprintf(stu.name, NAMESIZE, "stu%d", ids[i]);
		treeInsert(&t, &stu);
	}
	printf("%d\n", nodenumber(t));

	treeMidTraval(t);

	treeDraw(t);
//	treeDelete(&t, 8);
	
	printf("\n\n");
	treeBalance(&t);
	treeDraw(t);
	treeMidTraval(t);
	treeDestroy(&t);
	return 0;
}



