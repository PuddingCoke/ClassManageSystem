#pragma once

#include<stdio.h>
#include<malloc.h>
#include<conio.h>
#include<string.h>

#include"List.h"

struct ClassInfo//�༶��Ϣ
{
	List* students;
	size_t subNumber;
	char** subjects;
};

typedef struct ClassInfo ClassInfo;

void addStudent(ClassInfo* info)//����ѧ��
{
	addNode(info->students);
	info->students->cur->sum = 0;
	info->students->cur->score = (size_t*)malloc(sizeof(size_t) * info->subNumber);
}

void sumScoreOfStu(ClassInfo* info, Node* node)//����ѧ���ܷ�
{
	node->sum = 0;
	for (size_t i = 0; i < info->subNumber; i++)
	{
		node->sum += node->score[i];
	}
}

ClassInfo* readFromFile()//���ļ���ȡ����
{
	ClassInfo* info = (ClassInfo*)malloc(sizeof(ClassInfo));

	info->subNumber = 0;

	FILE* fp;

	fopen_s(&fp, "class.txt", "r");

	if (fp == NULL)
	{
		printf_s("�ļ���ʧ��\n");
		return NULL;
	}

	int beginAt = 0;
	
	for (; fgetc(fp) == ' '; beginAt++) {}

	for (int end = 1,temp; end && ((temp = (char)fgetc(fp)) != EOF);)
	{
		if (temp < 0)
		{
			info->subNumber++;
			while (1)
			{
				temp = fgetc(fp);
				if (temp == ' ')
				{
					break;
				}
				else if (temp == EOF || temp == '\n')
				{
					end = 0;
					break;
				}
			}
		}
	}

	info->students = createList();

	info->subjects = (char**)malloc(sizeof(char*) * info->subNumber);

	for (size_t i = 0; i < info->subNumber; i++)
	{
		info->subjects[i] = (char*)malloc(sizeof(char) * 12ULL);
	}

	fseek(fp, beginAt, SEEK_SET);

	for (size_t i = 0; i < info->subNumber; i++)//��ȡ��Ŀ����
	{
		char subjectName[12];
		for (size_t j = 0; j < 12; j++)
		{
			char temp = fgetc(fp);

			if (temp < 0 && temp != EOF)
			{
				subjectName[j] = temp;
			}
			else
			{
				subjectName[j] = '\0';
				for (size_t k = 0; k < j + 1ULL; k++)
				{
					info->subjects[i][k] = subjectName[k];
				}
				break;
			}
		}
	}

	for (;;)
	{
		char temp = fgetc(fp);

		if (temp == EOF)
		{
			break;
		}

		temp = fgetc(fp);

		if (temp == EOF)
		{
			break;
		}

		fseek(fp, -2, SEEK_CUR);

		addStudent(info);

		char name[32];

		for (size_t j = 0; j < 32; j++)
		{
			temp = fgetc(fp);

			if (temp < 0)
			{
				name[j] = temp;
			}
			else
			{
				name[j] = '\0';

				for (size_t k = 0; k < j + 1ULL; k++)
				{
					info->students->cur->name[k] = name[k];
				}

				break;
			}
		}

		fscanf_s(fp, "%zu", &info->students->cur->id);

		for (size_t j = 0; j < info->subNumber; j++)
		{
			fscanf_s(fp, "%zu", &info->students->cur->score[j]);
		}

		fseek(fp, 2, SEEK_CUR);

	}

	fclose(fp);

	return info;
}

void saveToFile(ClassInfo* info)//���浽�ļ�
{
	FILE* fp;
	fopen_s(&fp, "class.txt", "w");
	if (fp == NULL)
	{
		printf_s("�ļ�����ʧ��\n");
		return;
	}
	for (size_t i = 0; i < info->subNumber; i++)
	{
		fprintf_s(fp, " %s", info->subjects[i]);
	}
	fprintf_s(fp, "\n");

	Node* node = info->students->head;
	for (size_t i = 0; i < info->students->i; i++)
	{
		fprintf_s(fp, "%s %zu", node->name, node->id);
		for (size_t j = 0; j < info->subNumber; j++)
		{
			fprintf_s(fp, " %zu", node->score[j]);
		}
		fprintf_s(fp, "\n");
		node = node->next;
	}

	fclose(fp);
}

void printStudent(ClassInfo* info, Node* node)//��ӡѧ���������
{
	if (node == NULL)
	{
		return;
	}
	printf_s("%s", node->name);
	for (size_t i = 0; i < 16 - strlen(node->name); i++)
	{
		printf_s(" ");
	}
	printf_s("%zu\t\t", node->id);
	for (size_t i = 0; i < info->subNumber; i++)
	{
		printf_s("%zu\t\t", node->score[i]);
	}
	sumScoreOfStu(info, node);
	printf_s("%zu\n", node->sum);
}

double getAverageScore(ClassInfo* info, size_t i)//��ȡĳ�Ƶ�ƽ����
{
	double sum = 0;
	Node* node = info->students->head;
	for (size_t i1 = 0; i1 < info->students->i; i1++)
	{
		if (i < info->subNumber)
		{
			sum += (double)(node->score[i]);
		}
		else
		{
			sum += (double)(node->sum);
		}
		node = node->next;
	}
	return sum / (double)(info->students->i);
}

void printInfo(ClassInfo* info)//��ӡ����
{

	printf_s("����");

	for (size_t i = 0; i < 12; i++)
	{
		printf_s(" ");
	}

	printf_s("ѧ��");

	for (size_t i = 0; i < info->subNumber; i++)
	{
		printf_s("\t\t%s", info->subjects[i]);
	}

	printf_s("\t\t�ܷ�");

	printf_s("\n\n");

	Node* node = info->students->head;
	while (node != NULL)
	{
		printStudent(info, node);
		node = node->next;
		printf_s("\n");
	}

	printf_s("ƽ����:\t\t\t\t");

	for (size_t i = 0; i < info->subNumber; i++)
	{
		printf_s("%.1lf\t\t", getAverageScore(info, i));
	}

	printf_s("%.1lf", getAverageScore(info, info->subNumber));

	printf_s("\n");

}

Node* findByName(ClassInfo* info, char name[32])//ͨ�������ҵ�ѧ��
{
	Node* node = info->students->head;
	for (size_t i = 0; i < info->students->i; i++)
	{
		if (!strcmp(name, node->name))
		{
			return node;
		}
	}
	return NULL;
}

Node* findByID(ClassInfo* info, size_t id)//ͨ��ѧ���ҵ�ѧ��
{
	Node* node = info->students->head;
	for (size_t i = 0; i < info->students->i; i++)
	{
		if (node->id == id)
		{
			return node;
		}
		node = node->next;
	}
	return NULL;
}

void swap(size_t* a, size_t* b)//��������
{
	size_t temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void swapStudent(ClassInfo* info, Node* st1, Node* st2)//����ѧ������
{
	swap(&st1->id, &st2->id);
	for (size_t i = 0; i < info->subNumber; i++)
	{
		swap(&st1->score[i], &st2->score[i]);
	}
	swap(&st1->sum, &st2->sum);
	char name1[32] = { 0 };
	char name2[32] = { 0 };
	size_t index;

	for (index = 0; st1->name[index] != '\0'; index++)
	{
		name1[index] = st1->name[index];
		st1->name[index] = 0;
	}
	name1[index] = st1->name[index];
	st1->name[index] = 0;

	for (index = 0; st2->name[index] != '\0'; index++)
	{
		name2[index] = st2->name[index];
		st2->name[index] = 0;
	}
	name2[index] = st2->name[index];
	st2->name[index] = 0;

	for (index = 0; name2[index] != '\0'; index++)
	{
		st1->name[index] = name2[index];
	}
	st1->name[index] = '\0';

	for (index = 0; name1[index] != '\0'; index++)
	{
		st2->name[index] = name1[index];
	}
	st2->name[index] = '\0';
}

Node* sortList(ClassInfo* info, Node* head, size_t i)//��������
{

	Node* tmpPtr = head;
	Node* tmpNext = head->next;

	while (tmpNext != NULL)
	{
		while (tmpNext != tmpPtr)
		{
			if (i < info->subNumber)
			{
				if (tmpNext->score[i] < tmpPtr->score[i])
				{
					swapStudent(info, tmpNext, tmpPtr);
				}
			}
			else
			{
				sumScoreOfStu(info, tmpNext);
				sumScoreOfStu(info, tmpPtr);
				if (tmpNext->sum < tmpPtr->sum)
				{
					swapStudent(info, tmpNext, tmpPtr);
				}
			}
			tmpPtr = tmpPtr->next;
		}
		tmpPtr = head;
		tmpNext = tmpNext->next;
	}
	return tmpPtr;
}

void releaseInfo(ClassInfo* info)//�ͷ��ڴ�
{
	for (size_t i = 0; i < info->subNumber; i++)
	{
		free(info->subjects[i]);
	}

	free(info->subjects);

	freeList(info->students);

	free(info);
}