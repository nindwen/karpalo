#ifndef _DATA
#define _DATA

struct node
{
	struct node *prev;
	struct node *next;
	struct node *parent;
	int F;
	int G;
	int H;
	int y;
	int x;
};

struct list
{
	struct node *first;
	struct node *last;
};

int listCreat(struct list *list, struct node *node);
int listAdd(struct list *list, struct node *node);
int listRemove(struct list *list, struct node *node);
struct node * listFind(struct list *list,int y, int x);
struct node* listLowest(struct list *list);

int listIsOn(struct list *list, struct node *node);

#endif


