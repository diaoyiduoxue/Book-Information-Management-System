#include "linklist.h"
#include"config.h"
static bool isvaild(list*list)
{
	printf("list invaild\n");
	return list != NULL;
}
Node* creatNode(variant val)
{
	Node* newNode = calloc(1, sizeof(Node));
	if (!newNode)
	{
		printf("creat faild\n");
		return NULL;
	}
	newNode->date = val;
	return newNode;
}
void init_linklist(list* list)
{
	if (!isvaild)
		return;
	list->front = list->tial=calloc(1,sizeof(Node));
	if (!list->front)
	{
		printf("calloc faild\n");
		return;
	}
}

void link_bakeinsert(list* list, variant val)
{
	if (!isvaild)
		return;
	Node* newNode = creatNode(val);
	list->tial->next = newNode;
	list->tial = newNode;
	list->size++;
}

void link_removeone(list* list, variant val)
{
	
	if (!isvaild)
		return;
	Node* curNode = list->front->next;
	Node* preNode = list->front;
	while (curNode)
	{
		
		if (curNode->date == val)
			break;
		preNode = curNode;
		curNode = curNode->next;
	}
	preNode->next = curNode->next;
	free(curNode);
}

void link_callbake(list* list, LISTCALLBAKE callbake)
{
	if (!isvaild)
		return;
	Node* curNode = list->front->next;
	while (curNode)
	{
		callbake(curNode->date);
		curNode = curNode->next;
	}
}

variant link_callbake_search(list* list, CALLBAKE_CMP cmp, variant val)
{
	Node* curnode = list->front->next;
	while (curnode)
	{
		if (cmp(curnode->date, val))
		{
			return curnode->date;
		}
		curnode = curnode->next;
	}
	return NULL;
}

void destory(list* list)
{
	if (!isvaild)
		return;
	Node* curNode = list->front;
	Node* nextNode = curNode->next;
	while (curNode)
	{
		nextNode = curNode->next;
		free(curNode);
		curNode = nextNode;
	}
}

