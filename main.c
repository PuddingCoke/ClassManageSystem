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
		printf_s("密码:");

		scanf_s("%s", inputPswd, 50);

		if (!strcmp(pswd, inputPswd))
		{
			printf_s("请按任意键进入系统\n");
			_getch();
			fflush(stdin);
			break;
		}
		else
		{
			printf_s("密码错误请重试 %d", count);
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
		printf_s("数据读取失败\n");
		_getch();
		fflush(stdin);
		return -1;
	}

	int flag=1;

	while (flag) {

		printf_s("-----班级信息管理系统-----\n");
		printf_s("     1.输入信息\n");
		printf_s("     2.修改信息\n");
		printf_s("     3.查询信息\n");
		printf_s("     4.显示信息\n");
		printf_s("     5.排序信息\n");
		printf_s("     5.保存数据\n");
		printf_s("     0.退出\n");

		int command;
		printf_s("请输入您的选择(0~5):");
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
			printf_s("名字 学号 成绩1 成绩2\n");
			scanf_s("%s %zu %zu %zu", name, 32, &id, &grade1, &grade2);
			ClassInfo_AddStudent(info);
			for (size_t i = 0; i < 32; i++)
			{
				info->students->cur->name[i] = name[i];
			}
			info->students->cur->id = id;
			info->students->cur->score[0] = grade1;
			info->students->cur->score[1] = grade2;
			printf_s("输入成功\n");
			break;

		case 2:
			printf_s("输入 1 按姓名查找\n输入 2 按学号查找\n");
			scanf_s("%d", &pattern);
			if (pattern != 1 && pattern != 2)
			{
				printf_s("输入有误\n");
				break;
			}

			if (pattern == 1)
			{
				printf_s("名称:");
				scanf_s("%s", name, 32);
				node = Node_FindByName(info, name);
			}
			else
			{
				printf_s("学号:");
				scanf_s("%zu", &id);
				node = Node_FindByID(info, id);
			}

			if (node == NULL)
			{
				printf_s("未找到该学生\n");
				break;
			}

			ClassInfo_PrintStudent(info, node);
			printf_s("名字 学号 成绩1 成绩2\n");
			scanf_s("%s %zu %zu %zu", name, 32, &id, &grade1, &grade2);
			for (size_t i = 0; i < 32; i++)
			{
				node->name[i] = name[i];
			}
			node->id = id;
			node->score[0] = grade1;
			node->score[1] = grade2;
			printf_s("修改成功!\n");
			node = NULL;
			break;

		case 3:
			printf_s("输入 1 按姓名查找\n输入 2 按学号查找\n");
			scanf_s("%d", &pattern);
			if (pattern != 1 && pattern != 2)
			{
				printf_s("输入有误\n");
				break;
			}

			if (pattern == 1)
			{
				printf_s("名称:");
				scanf_s("%s", name, 32);
				node = Node_FindByName(info, name);
			}
			else
			{
				printf_s("学号:");
				scanf_s("%zu", &id);
				node = Node_FindByID(info, id);
			}

			if (node == NULL)
			{
				printf_s("未找到该学生\n");
				break;
			}

			ClassInfo_PrintStudent(info, node);
			node = NULL;
			break;

		case 4:
			printf_s("显示全部信息\n\n");
			ClassInfo_PrintInfo(info);
			break;

		case 5:
			printf_s("输入科目名称(总分):");
			scanf_s("%s", name, 32);

			int find = 0;

			if (strCompare(name, "总分"))
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
				printf("未找到此科目\n");
			}
			else
			{
				printf_s("排序完成!\n");
			}

			break;
		case 6:
			ClassInfo_SaveToFile(info);
			printf_s("保存完成!\n");
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