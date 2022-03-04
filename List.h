#pragma once

#include<stdio.h>
#include<malloc.h>

typedef struct Node
{
	char name[32];
	size_t id;
	size_t sum;
	size_t* score;
	struct Node* next;
} Node;

typedef struct List
{
	size_t i;
	Node* head;
	Node* cur;
} List;

List* List_Create()//创建链表
{
	List* list = (List*)malloc(sizeof(List));
	if (list == NULL)
	{
		printf_s("createList() 分配内存失败\n");
		return NULL;
	}
	list->i = 0;
	list->cur = NULL;
	list->head = NULL;
	return list;
}

void List_Free(List *list)//释放链表
{
	Node* temp;
	while (list->head != NULL)
	{
		temp = list->head;
		free(temp->score);
		list->head = list->head->next;
		free(temp);
	}
	free(list);
}

void List_AddNode(List* list)//增加节点
{
	if (list->head == NULL)
	{
		list->head = (Node*)malloc(sizeof(Node));
		if (list->head == NULL)
		{
			printf_s("addNode() 分配内存失败");
			return;
		}
		list->head->next = NULL;
		list->cur = list->head;
	}
	else
	{
		list->cur->next= (Node*)malloc(sizeof(Node));
		if (list->cur->next == NULL)
		{
			printf_s("addNode() 分配内存失败\n");
			return;
		}
		list->cur = list->cur->next;
		list->cur->next = NULL;
	}
	list->i++;
}