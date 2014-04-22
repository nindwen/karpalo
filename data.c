#include <stdlib.h>
#include "data.h"

int listCreat(struct list *list, struct node *node)
{
	list->first=node;
	list->last=node;
	node->prev=NULL;
	node->next=NULL;
}

int listAdd(struct list *list, struct node *node)
{
	node->prev=list->last;
	list->last->next=node;
	node->next=NULL;
}
	
int listRemove(struct list *list, struct node *node)
{
	node->prev->next=node->next;
	node->next->prev=node->prev;
}

struct node * listFind(struct list *list,int y, int x)
{
	struct node *cur = list->first;
	while(cur->next != NULL)
	{
		if(cur->y==y && cur->x==x)
		{
			return cur;
		}
		else
		{
			cur=cur->next;
		}
	}
	return NULL;
}

