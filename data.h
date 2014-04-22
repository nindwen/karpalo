#ifndef _DATA
#define _DATA

struct node
{
	int x;
	int y;
	struct node *prev;
	struct node *next;
	struct node *parent;
	int F;
	int G;
	int H;
};

struct list
{
	struct node *first;
	struct node *last;
};

int listCreat(struct list *list, struct node *node);
int listAdd(struct list *list, struct node *node);

#endif


