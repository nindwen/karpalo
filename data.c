#include <stdlib.h>
#include "data.h"
#include "controls.h"

int listCreat(struct list *list, struct node *node)
{
	list->first	=	node;
	list->last	=	node;
	node->prev	=	NULL;
	node->next	=	NULL;
}

int listAdd(struct list *list, struct node *node)
{
	if(list->first==NULL)
	{
		listCreat(list,node);
		return 1;
	}
	else if(listIsOn(list,node)) { return 0; }
	else
	{
		node->prev=list->last;
		list->last->next=node;
		list->last=node;
		node->next=NULL;
	}
}

int listIsOn(struct list *list, struct node *node)
{
	if(list->first==NULL)
	{
		return 0;
	}
	else
	{
		struct node *cur = list->first;
		while(1)
		{
			if(cur==node)
			{
				return 1;
			}
			if(cur->next==NULL) { return 0; }
			cur=cur->next;
		}
		return 0;
	}
}


	
int listRemove(struct list *list, struct node *node)
{
	if(list->first==node && list->last==node)
	{
		list->first=NULL;
		list->last=NULL;
	}
	else if(list->first==node)
	{
		list->first=node->next;
	}
	else if(list->last==node)
	{
		list->last=node->prev;;
		node->prev->next=NULL;
	}
	else
	{
		node->prev->next=node->next;
		if(node->next != NULL)
		{
			node->next->prev=node->prev;
		}
	}
}

int setF(struct node *node, struct thing *heebo)
{
	if(node->parent!=NULL)
	{
		node->G=node->parent->F+1;
	}
	node->H=abs(node->y - heebo->y)+abs(node->x - heebo->y);
	node->F=node->G + node->H;
}

struct node* listLowest(struct list *list)
{
	if(list->first==NULL)
	{
		return NULL;
	}
	struct node *cur = list->first;
	struct node *low=cur;
	while(1)
	{
		if(cur->F<low->F)
		{
			low=cur;
		}
		if(cur->next==NULL) { break; }
		cur=cur->next;
	}
	return low;
}	


/*
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
*/
