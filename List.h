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

List* List_Create()//��������
{
	List* list = (List*)malloc(sizeof(List));
	if (list == NULL)
	{
		printf_s("createList() �����ڴ�ʧ��\n");
		return NULL;
	}
	list->i = 0;
	list->cur = NULL;
	list->head = NULL;
	return list;
}

void List_Free(List *list)//�ͷ�����
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

void List_AddNode(List* list)//���ӽڵ�
{
	if (list->head == NULL)
	{
		list->head = (Node*)malloc(sizeof(Node));
		if (list->head == NULL)
		{
			printf_s("addNode() �����ڴ�ʧ��");
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
			printf_s("addNode() �����ڴ�ʧ��\n");
			return;
		}
		list->cur = list->cur->next;
		list->cur->next = NULL;
	}
	list->i++;
}