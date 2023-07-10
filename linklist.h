#ifndef _LINKLIST_H_
#define _LINKLIST_H_
#include"config.h"
typedef struct Node
{
	variant date;//指向数据的指针
	struct Node* next;//指向节点的指针
}Node;

typedef struct list
{
	int size;//节点个数不包括头节点
	Node* front;
	Node* tial;
}list;

typedef void (*LISTCALLBAKE)(variant);//指向有一个参数的函数的指针
typedef bool (*CALLBAKE_CMP)(variant, variant);//指向有两个参数的函数的指针

void init_linklist(list* list);//初始化链表
void link_bakeinsert(list* list, variant val);//插入信息
void link_removeone(list* list, variant val);//移除
void link_callbake(list* list, LISTCALLBAKE callbake);//遍历节点并执行某个操作
variant link_callbake_search(list* list, CALLBAKE_CMP cmp, variant val);//超某个节点
void destory(list* list);




#endif
