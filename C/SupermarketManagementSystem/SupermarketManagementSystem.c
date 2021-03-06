// SupermarketManagementSystem.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int main()
{
	DisplayInit();
	LogIn();

	system("pause");

    return 0;
}


void DisplayInit()
{
	system("cls");
	printf("--------------------------------------\n\n");
	printf("     小型超市库存与销售管理系统V1.0     \n\n");
	printf("        Created By GaoTian         \n\n");
	printf("--------------------------------------\n\n");
	getchar();
}

void DisplayExit()
{
	system("cls");
	printf("--------------------------------------\n\n");
	printf("               再见                   \n\n");
	printf("--------------------------------------\n\n");
	getchar();
}

void LogIn()
{
	system("cls");
	int op = -1;
	printf("1) 管理员登陆   \n");
	printf("2) 售货员登陆    \n");
	printf("0) 退出        \n");
	printf(">> ");

	scanf("%d", &op);
	if (op == 1)
		AdminLogIn();
	else if (op == 2)
		SalesmanLogIn();
	else
		DisplayExit();
}


void AdminLogIn()
{
	char account[30], password[30];
	system("cls");
	printf("管理员登陆             \n\n");
	printf("账号\n>> ");
	scanf("%s", account);
	printf("密码\n>> ");
	scanf("%s", password);

	if (IsAdminAccount(account, password))
		AdminInitMenu();
	else {
		printf("\n账号或密码错误\n");
		system("pause");
		LogIn();
	}
}

void SalesmanLogIn()
{
	char account[30], password[30];
	system("cls");
	printf("售货员登陆             \n\n");
	printf("账号\n>> ");
	scanf("%s", account);
	printf("密码\n>> ");
	scanf("%s", password);

	if (IsSalesmanAccount(account, password))
		SalesmanInitMenu();
	else {
		printf("\n账号或密码错误\n");
		system("pause");
		LogIn();
	}
}
