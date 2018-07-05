#include "stdafx.h"


//判断是否为管理员账户，无法打开文件返回-1，是返回1，否返回0
int IsAdminAccount(char *account, char *password)
{
	FILE *fp = fopen("Data\\user.dat", "rb");

	if (fp == NULL)
		return -1;

	fseek(fp, 0, SEEK_END);
	int size = ftell(fp)/sizeof(UserAccount);
	fseek(fp, 0, SEEK_SET);

	UserAccount* user = (UserAccount*)malloc(size * sizeof(UserAccount));
	
	for (int i = 0; i < size; i++) {
		fread(user + i, sizeof(UserAccount), 1, fp);
		if (strcmp(account, user[i].account) == 0 && strcmp(password, user[i].password) == 0 
			&& user[i].permission_level == 1)
			return 1;
	}

	free(user);
	fclose(fp);

	return 0;
}

//增加账户信息，无法打开返回-1，成功返回1，账户已存在返回0（更改密码）
int AddAccount(UserAccount *newInfo)
{
	FILE *fp = fopen("Data\\user.dat", "rb+");

	if (fp == NULL)
		return -1;

	fseek(fp, 0, SEEK_END);
	int size = ftell(fp) / sizeof(UserAccount);
	fseek(fp, 0, SEEK_SET);

	int index = -1;
	UserAccount *user = (UserAccount*)malloc((size + 1) * sizeof(UserAccount));
	for (int i = 0; i < size; i++) {
		fread(user + i, sizeof(UserAccount), 1, fp);
		if (strcmp(user[i].account, newInfo->account) == 0) {
			return 0;
		}
	}

	user[size] = *newInfo;
	fseek(fp, 0, SEEK_SET);

	for (int i = 0; i <= size; i++) {
		fwrite(user + i, sizeof(UserAccount), 1, fp);
	}

	free(user);
	fclose(fp);
	return 1;
	
}


//更该所有用户的密码，文件无法打开返回-1，删除成功返回1，失败返回0
int DeleteAccount(char *account)
{
	FILE *fp = fopen("Data\\user.dat", "rb+");

	if (fp == NULL)
		return -1;

	fseek(fp, 0, SEEK_END);
	int size = ftell(fp) / sizeof(UserAccount);
	fseek(fp, 0, SEEK_SET);

	UserAccount *user = (UserAccount*)malloc(size * sizeof(UserAccount));
	int index = -1;
	for (int i = 0; i < size; i++) {
		fread(user + i, sizeof(UserAccount), 1, fp);
		if (strcmp(user[i].account, account) == 0) {
			index = i;
		}
			
	}
	fclose(fp);
	
	if (index != -1) {
		fp = fopen("Data\\user.dat", "wb+");

		for (int i = 0; i < size; i++) {
			if (i == index) continue;
			//printf("look: %s %s %d\n", user[i].account, user[i].password, user[i].permission_level);
			fwrite(user + i, sizeof(UserAccount), 1, fp);
		}

		fclose(fp);
	}

	free(user);

	return index != -1 ? 1 : 0;
}


//显示系统内所有账户信息，无法打开返回-1
int DisplayAccountInfo()
{
	FILE *fp = fopen("Data\\user.dat", "rb");

	if (fp == NULL)
		return -1;

	fseek(fp, 0, SEEK_END);
	int size = ftell(fp) / sizeof(UserAccount);
	fseek(fp, 0, SEEK_SET);

	UserAccount* own = (UserAccount*)malloc(size * sizeof(UserAccount));
	printf("--------------------------------------\n");
	printf("%-10s %-10s  %-2s\n", "账号", "密码", "权限");
	for (int i = 0; i < size; i++) {
		fread(own + i, sizeof(UserAccount), 1, fp);
		if (own[i].permission_level)
			printf("%-10s %-10s %-2s\n", own[i].account, own[i].password, "管理员");
		else
			printf("%-10s %-10s %-2s\n", own[i].account, own[i].password, "售货员");
	}
	printf("--------------------------------------\n");

	free(own);
	fclose(fp);

	return 1;
}


void AdminInitMenu()
{
	system("cls");
	int op = -1;

	printf("1) 库存管理\n");
	printf("2) 用户管理\n");
	printf("3) 销售商品\n");
	printf("4) 销售统计\n");
	printf("0) 退出登陆\n");

	printf(">> ");
	scanf("%d", &op);

	if (op == 1)
		StockManagement();
	else if (op == 2)
		UserManagement();
	else if (op == 3)
		SoldManagement();
	else if (op == 4)
		SoldStatistics();
	else
		LogIn();
}


void StockManagement()
{
	system("cls");
	int op = -1;

	printf("1) 添加商品\n");
	printf("2) 批量入库\n");
	printf("3) 查看库存\n");
	printf("4) 查询商品\n");
	printf("5) 清理库存\n");
	printf("0) 返回上级\n");

	printf(">> ");
	scanf("%d", &op);

	GoodsList head = InitGoodsList();
	ImportGoodsFromFile(head, OpenGoodsFile("r"));

	if (op == 1)
		AddGoodsToStock(head);
	else if (op == 2)
		BatchedStock(head);
	else if (op == 3)
		LookOverStock(head);
	else if (op == 4)
		LookUpGoods(head);
	else if (op == 5)
		ClearStock(head);
	else {
		DeleteGoodsList(head);
		AdminInitMenu();
	}
		
}


void AddGoodsToStock(GoodsList head)
{
	system("cls");
	char id[20];

	printf("输入商品id\n>> ");
	scanf("%s", id);

	GoodsList p = FindGoodsByID(head, atoi(id));
	if (p) {
		printf("该商品已存在\n");
		DisplayGoodsInfo(p);
		printf("输入增添数量\n>> ");
		int add_cnt = 0;
		scanf("%d", &add_cnt);
		if (add_cnt < 0) add_cnt = 0;
		p->goods.quantity += add_cnt;

		TraverseGoodsList(head, DisplayGoodsInfo);

		ExportGoodsToFile(head, OpenGoodsFile("w"));
		printf("添加完成\n");
	}
	else {
		Goods goods;
		goods.id = atoi(id);
		printf("输入商品名称\n>> ");
		scanf("%s", goods.name);
		printf("输入商品进价\n>> ");
		scanf("%lf", &goods.buying_price);
		printf("输入商品售价\n>> ");
		scanf("%lf", &goods.selling_price);
		printf("输入商品生产商\n>> ");
		scanf("%s", goods.manufacturer);
		printf("输入商品数量\n>> ");
		scanf("%d", &goods.quantity);

		AddGoodsToList(head, goods);
		ExportGoodsToFile(head, OpenGoodsFile("w"));
		printf("添加完成\n");
		DisplayGoodsInfo(&goods);
	}

	system("pause");
	StockManagement();
}

void BatchedStock(GoodsList head)
{
	FILE *fp = fopen("ExternalData\\added_goods.txt", "r");
	if (fp) {
		ImportGoodsFromFile(head, fp);
		ExportGoodsToFile(head, OpenGoodsFile("w"));
		fclose(fp);
		printf("导入成功\n");
	}
	else {
		printf("打开待导入文件失败\n");
	}
	system("pause");
	StockManagement();
}

void LookOverStock(GoodsList head)
{
	printf("-------------------------------------------------------\n");
	printf("%-5s %-12s %-6s %-6s %-15s %-5s\n", "ID", "名称", "进价", "售价", "生产厂商", "余量");
	TraverseGoodsList(head, DisplayGoodsInfo);
	printf("-------------------------------------------------------\n");
	system("pause");
	StockManagement();
}


void LookUpGoods(GoodsList head)
{
	system("cls");

	if (head->next == NULL) {
		printf("库存为空\n");
		system("pause");
		StockManagement();
	}

	int op = -1;

	printf("1) 按商品名查询\n");
	printf("2) 按生产厂家查询\n");
	printf("3) 综合查询\n");
	printf("0) 返回上级\n");

	scanf("%d", &op);

	if (op == 1)
		LookUpGoodsByName(head);
	else if (op == 2)
		LookUpGoodsByManufacturer(head);
	else if (op == 3)
		LookUpGoodsByNameAndManufacturer(head);
	else {
		StockManagement();
	}
}


void ShowQueriedGoodsListToAdmin(GoodsList queried_goods)
{
	printf("-------------------------------------------------------\n");
	printf("%-5s %-12s %-6s %-6s %-15s %-5s\n", "ID", "名称", "进价", "售价", "生产厂商", "余量");
	TraverseGoodsList(queried_goods, DisplayGoodsInfo);
	printf("-------------------------------------------------------\n");
}

void LookUpGoodsByName(GoodsList head)
{
	char goods_name_prefix[MAXGOODSNAME] = { 0 };
	//char manufacturer_prefix[MAXMANUFACTURERNAME] = { 0 };

	printf("输入商品名称或名称前缀\n>> ");
	scanf("%s", goods_name_prefix);
	GoodsList queried_goods = QueryGoodsByName(head, goods_name_prefix);
	ShowQueriedGoodsListToAdmin(queried_goods);
	DeleteGoodsList(queried_goods);
	system("pause");
	LookUpGoods(head);
}

void LookUpGoodsByManufacturer(GoodsList head)
{
	char manufacturer_prefix[MAXMANUFACTURERNAME] = { 0 };

	printf("输入商品生产商名称或生产商名称前缀\n>> ");
	scanf("%s", manufacturer_prefix);
	GoodsList queried_goods = QueryGoodsByManufacturer(head, manufacturer_prefix);
	ShowQueriedGoodsListToAdmin(queried_goods);
	DeleteGoodsList(queried_goods);
	system("pause");
	LookUpGoods(head);
}

void LookUpGoodsByNameAndManufacturer(GoodsList head)
{
	char goods_name_prefix[MAXGOODSNAME] = { 0 };
	char manufacturer_prefix[MAXMANUFACTURERNAME] = { 0 };

	printf("输入商品名称或名称前缀\n>> ");
	scanf("%s", goods_name_prefix);
	printf("输入商品生产商名称或生产商名称前缀\n>> ");
	scanf("%s", manufacturer_prefix);
	GoodsList queried_goods = QueryGoodsByNameAndManufacturer(head, goods_name_prefix, manufacturer_prefix);
	ShowQueriedGoodsListToAdmin(queried_goods);
	DeleteGoodsList(queried_goods);
	system("pause");
	LookUpGoods(head);
}


void ClearStock(GoodsList head)
{
	char op[10];
	printf("是否删除库存内数量为0的商品 (Y 或 N)\n");
	scanf("%s", op);

	if (op[0] == 'Y' || op[0] == 'y') {
		RemoveZeroQuantityGoods(head);
		ExportGoodsToFile(head, OpenGoodsFile("w"));
		printf("清理库存成功\n");
		system("pause");
	}
	
	StockManagement();
}

void UserManagement()
{
	system("cls");
	int op = -1;

	printf("1) 浏览用户\n");
	printf("2) 添加用户\n");
	printf("3) 删除用户\n");
	printf("0) 返回上级\n");

	printf(">> ");
	scanf("%d", &op);

	if (op == 1)
		LookOverUser();
	else if (op == 2)
		AddUser();
	else if (op == 3)
		DeleteUser();
	else
		AdminInitMenu();
}


void LookOverUser()
{
	system("cls");
	DisplayAccountInfo();
	system("pause");
	UserManagement();
}


void AddUser()
{
	system("cls");
	UserAccount ua;
	printf("账号\n>> ");
	scanf("%s", ua.account);
	printf("密码\n>> ");
	scanf("%s", ua.password);
	
	char level[15] = { 0 };
	while (strcmp(level, "0") && strcmp(level, "1")) {
		printf("用户权限(0-售货员  1-管理员)\n>> ");
scanf("%s", level);
	}

	ua.permission_level = atoi(level);
	int ret = AddAccount(&ua);

	if (ret == 1) {
		printf("\n添加用户成功\n");
		printf("--------------------------------------\n");
		printf("%-10s %-10s  %-2s\n", "账号", "密码", "权限");
		if (ua.permission_level)
			printf("%-10s %-10s %-2s\n", ua.account, ua.password, "管理员");
		else
			printf("%-10s %-10s %-2s\n", ua.account, ua.password, "售货员");
		printf("--------------------------------------\n");


	}
	else if (ret == 0) {
		printf("该用户已存在\n");
	}
	else
		printf("添加失败\n");

	system("pause");
	UserManagement();
}


void DeleteUser()
{
	system("cls");
	DisplayAccountInfo();
	char account[15];

	printf("\n输入待删除用户的账号\n>> ");
	scanf("%s", account);

	if (strcmp(account, "admin") == 0) {
		printf("超级用户, 不能删除\n");
	}
	else {
		int ret = DeleteAccount(account);
		if (ret == 1) {
			printf("删除成功\n");
		}
		else if (ret == -1) {
			printf("无法删除\n");
		}
		else {
			printf("该用户不存在\n");
		}
	}

	system("pause");
	UserManagement();
	return;
}


void SoldManagement()
{
	GoodsList head = InitGoodsList();
	ImportGoodsFromFile(head, OpenGoodsFile("r"));
	SoldGoods(head);
	DeleteGoodsList(head);
	AdminInitMenu();
}


void SoldStatistics()
{
	system("cls");
	RecordsList head = InitRecordsList();
	ImportRecordsFromFile(head, OpenRecordsFile("r"));

	int op = -1;

	printf("1) 单天记录\n");
	printf("2) 多天记录\n");
	printf("3) 多天统计\n");
	printf("0) 返回上级\n");

	printf(">> ");
	scanf("%d", &op);

	if (op == 1)
		SingleDaySoldRecords(head);
	else if (op == 2)
		DaysSoldRecords(head);
	else if (op == 3)
		DaysSoldStatistics(head);
	else {
		AdminInitMenu();
		DeleteRecordsList(head);
	}
	
}


void SingleDaySoldRecords(RecordsList head)
{
	int year, month, day;

	printf("依次输入年 月 日\n>> ");

	scanf("%d %d %d", &year, &month, &day);

	if (year >= 1970 && year <= 9999 && month >= 1 && month <= 12 && day >= 1 && day <= 31) {
		SoldDate start = { year, month, day, 0, 0, 0 };
		SoldDate end = { year, month, day, 23, 59, 59 };

		QuerySoldRecordsByDate(head, start, end);
	}
	else {
		printf("输入有误\n");
	}
	system("pause");
	SoldStatistics();
}


void DaysSoldRecords(RecordsList head)
{
	int start_year, start_month, start_day;
	int end_year, end_month, end_day;

	printf("输入查询开始日期 年 月 日\n>> ");
	scanf("%d %d %d", &start_year, &start_month, &start_day);

	printf("输入查询结束日期 年 月 日\n>> ");
	scanf("%d %d %d", &end_year, &end_month, &end_day);

	if (start_year >= 1970 && end_year >= 1970 && start_year <= 9999 && end_year <= 9999 &&
		start_month >= 1 && end_month >= 1 && start_month <= 12 && end_month <= 12 &&
		start_day >= 1 && end_day >= 1 && start_day <= 31 && end_day <= 31) {
		SoldDate start = { start_year, start_month, start_day, 0, 0, 0 };
		SoldDate end = { end_year, end_month, end_day, 23, 59, 59 };

		QuerySoldRecordsByDate(head, start, end);
	}
	else {
		printf("输入有误\n");
	}
	system("pause");
	SoldStatistics();
}


void DaysSoldStatistics(RecordsList head)
{
	int start_year, start_month, start_day;
	int end_year, end_month, end_day;
	int min_sold_cnt = 0, min_earnings = 0;

	printf("输入查询开始日期 年 月 日\n>> ");
	scanf("%d %d %d", &start_year, &start_month, &start_day);

	printf("输入查询结束日期 年 月 日\n>> ");
	scanf("%d %d %d", &end_year, &end_month, &end_day);

	printf("输入最小销量\n>> ");
	scanf("%d", &min_sold_cnt);

	printf("输入最小销售额\n>> ");
	scanf("%d", &min_earnings);

	if (start_year >= 1970 && end_year >= 1970 && start_year <= 9999 && end_year <= 9999 &&
		start_month >= 1 && end_month >= 1 && start_month <= 12 && end_month <= 12 &&
		start_day >= 1 && end_day >= 1 && start_day <= 31 && end_day <= 31) {
		SoldDate start = { start_year, start_month, start_day, 0, 0, 0 };
		SoldDate end = { end_year, end_month, end_day, 23, 59, 59 };

		SoldStatisticsByDate(head, start, end, min_sold_cnt, min_earnings);
	}
	else {
		printf("输入有误\n");
	}
	system("pause");
	SoldStatistics();
}





