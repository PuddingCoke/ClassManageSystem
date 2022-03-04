#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

#include"ClassInfo.h"

int main()
{
#ifndef DEBUG

	char pswd[50] = "1234";
	char inputPswd[50] = "";

	for (int count = 3; count > 0; count--)
	{
		printf_s("����:");

		scanf_s("%s", inputPswd, 50);

		if (!strcmp(pswd, inputPswd))
		{
			printf_s("�밴���������ϵͳ\n");
			_getch();
			fflush(stdin);
			break;
		}
		else
		{
			printf_s("������������� %d", count);
			_getch();
			fflush(stdin);
			system("cls");
			if (count == 1)
			{
				return -1;
			}
		}
	}

	system("cls");

#endif // !DEBUG

	ClassInfo* info = ClassInfo_Create();

	if (info == NULL)
	{
		printf_s("���ݶ�ȡʧ��\n");
		_getch();
		fflush(stdin);
		return -1;
	}

	int flag=1;

	while (flag) {

		printf_s("-----�༶��Ϣ����ϵͳ-----\n");
		printf_s("     1.������Ϣ\n");
		printf_s("     2.�޸���Ϣ\n");
		printf_s("     3.��ѯ��Ϣ\n");
		printf_s("     4.��ʾ��Ϣ\n");
		printf_s("     5.������Ϣ\n");
		printf_s("     5.��������\n");
		printf_s("     0.�˳�\n");

		int command;
		printf_s("����������ѡ��(0~5):");
		scanf_s("%d", &command);

		system("cls");

		char name[32] = { 0 };
		size_t id, grade1, grade2;
		Node* node = NULL;
		int pattern;

		switch (command)
		{
		case 0:
			flag = 0;
			break;

		case 1:
			printf_s("���� ѧ�� �ɼ�1 �ɼ�2\n");
			scanf_s("%s %zu %zu %zu", name, 32, &id, &grade1, &grade2);
			ClassInfo_AddStudent(info);
			for (size_t i = 0; i < 32; i++)
			{
				info->students->cur->name[i] = name[i];
			}
			info->students->cur->id = id;
			info->students->cur->score[0] = grade1;
			info->students->cur->score[1] = grade2;
			printf_s("����ɹ�\n");
			break;

		case 2:
			printf_s("���� 1 ����������\n���� 2 ��ѧ�Ų���\n");
			scanf_s("%d", &pattern);
			if (pattern != 1 && pattern != 2)
			{
				printf_s("��������\n");
				break;
			}

			if (pattern == 1)
			{
				printf_s("����:");
				scanf_s("%s", name, 32);
				node = Node_FindByName(info, name);
			}
			else
			{
				printf_s("ѧ��:");
				scanf_s("%zu", &id);
				node = Node_FindByID(info, id);
			}

			if (node == NULL)
			{
				printf_s("δ�ҵ���ѧ��\n");
				break;
			}

			ClassInfo_PrintStudent(info, node);
			printf_s("���� ѧ�� �ɼ�1 �ɼ�2\n");
			scanf_s("%s %zu %zu %zu", name, 32, &id, &grade1, &grade2);
			for (size_t i = 0; i < 32; i++)
			{
				node->name[i] = name[i];
			}
			node->id = id;
			node->score[0] = grade1;
			node->score[1] = grade2;
			printf_s("�޸ĳɹ�!\n");
			node = NULL;
			break;

		case 3:
			printf_s("���� 1 ����������\n���� 2 ��ѧ�Ų���\n");
			scanf_s("%d", &pattern);
			if (pattern != 1 && pattern != 2)
			{
				printf_s("��������\n");
				break;
			}

			if (pattern == 1)
			{
				printf_s("����:");
				scanf_s("%s", name, 32);
				node = Node_FindByName(info, name);
			}
			else
			{
				printf_s("ѧ��:");
				scanf_s("%zu", &id);
				node = Node_FindByID(info, id);
			}

			if (node == NULL)
			{
				printf_s("δ�ҵ���ѧ��\n");
				break;
			}

			ClassInfo_PrintStudent(info, node);
			node = NULL;
			break;

		case 4:
			printf_s("��ʾȫ����Ϣ\n\n");
			ClassInfo_PrintInfo(info);
			break;

		case 5:
			printf_s("�����Ŀ����(�ܷ�):");
			scanf_s("%s", name, 32);

			int find = 0;

			if (strCompare(name, "�ܷ�"))
			{
				find = 1;
				ClassInfo_StudentSort(info, info->subNumber);
			}


			if (!find)
			{
				for (int i = 0; i < info->subNumber; i++)
				{
					if (strCompare(name, info->subjects[i]))
					{
						find = 1;
						ClassInfo_StudentSort(info, i);
						break;
					}
				}
			}

			if (!find)
			{
				printf("δ�ҵ��˿�Ŀ\n");
			}
			else
			{
				printf_s("�������!\n");
			}

			break;
		case 6:
			ClassInfo_SaveToFile(info);
			printf_s("�������!\n");
			break;

		default:
			break;
		}

		_getch();
		fflush(stdin);
		system("cls");

	}
	ClassInfo_Free(info);
	return 0;
}