#include "stdafx.h"

//判断是否为销售员账户，无法打开文件返回-1，是返回1，否返回0
int IsSalesmanAccount(char *account, char *password)
{
	FILE *fp = fopen("Data\\user.dat", "rb");

	if (fp == NULL)
		return -1;

	fseek(fp, 0, SEEK_END);
	int size = ftell(fp) / sizeof(UserAccount);
	fseek(fp, 0, SEEK_SET);

	UserAccount* user = (UserAccount*)malloc(size * sizeof(UserAccount));

	for (int i = 0; i < size; i++) {
		fread(user + i, sizeof(UserAccount), 1, fp);
		if (strcmp(account, user[i].account) == 0 && strcmp(password, user[i].password) == 0
			&& user[i].permission_level == 0)
			return 1;
	}

	free(user);
	fclose(fp);

	return 0;
}

void DisplaySoldGoods(GoodsList head)
{
	printf("------------------------------------------------\n");
	printf("%-5s %-12s %-6s %-15s %-5s\n", "ID", "名称", "售价", "生产厂商", "余量");
	TraverseGoodsList(head, DisplayBasicGoodsInfo);
	printf("------------------------------------------------\n");
}


//购买商品，并更新商品，销售记录
void SoldGoods(GoodsList head)
{
	int id, cnt;
	GoodsList found_goods;
	while (1) {
		system("cls");
		DisplaySoldGoods(head);
		printf("\n输入待销售的商品ID (输入-1退出)\n>");
		scanf("%d", &id);

		if (id < 0) break;
		
		found_goods = FindGoodsByID(head, id);
		if (found_goods) {
			DisplayBasicGoodsInfo(&found_goods->goods);
			printf("输入销售数量\n>");
			scanf("%d", &cnt);
			if (cnt <= 0) {
				printf("商品数量有误\n");
				system("pause");
				continue;
			}
			else {
				FILE *goods_fp = OpenGoodsFile("w");
				FILE *records_fp = OpenRecordsFile("a");
				if (goods_fp && records_fp) {
					if (!ReduceGoodsQuantity(head, id, cnt)) {
						printf("该商品库存不足\n");
						system("pause");;
						continue;
					}
					ExportGoodsToFile(head, goods_fp);
					
					SoldGoodsRecord record;
					record.id = found_goods->goods.id;
					strcpy(record.name, found_goods->goods.name);
					record.selling_price = found_goods->goods.selling_price;
					record.sold_quantity = cnt;
					record.buying_price = found_goods->goods.buying_price;
					record.date = GetNowDate();

					AppendARecordToFile(record, records_fp);
					printf("销售成功\n");
					system("pause");
					continue;
				}
				else {
					if (goods_fp) fclose(goods_fp);
					if (records_fp) fclose(records_fp);
					printf("连接系统数据失败\n");
					system("pause");
					break;
				}
					
			}
		}
		else {
			printf("无此商品\n");
			system("pause");
			continue;
		}
	}
	
}


void SalesmanInitMenu()
{
	system("cls");
	
	int op = -1;

	printf("1) 销售商品\n");
	printf("2) 查询商品\n");
	printf("0) 退出登陆\n");

	printf(">> ");
	scanf("%d", &op);

	GoodsList head = InitGoodsList();
	ImportGoodsFromFile(head, OpenGoodsFile("r"));
	if (op == 1) {
		SoldGoods(head);
		DeleteGoodsList(head);
		SalesmanInitMenu();
	}
	else if (op == 2)
		SalesmanLookUpGoods(head);
	else {
		DeleteGoodsList(head);
		LogIn();
	}
		
}


void SalesmanLookUpGoods(GoodsList head)
{
	system("cls");

	if (head->next == NULL) {
		printf("库存为空\n");
		system("pause");
		SalesmanInitMenu();
	}

	int op = -1;

	printf("1) 按商品名查询\n");
	printf("2) 按生产厂家查询\n");
	printf("3) 综合查询\n");
	printf("0) 返回上级\n");

	scanf("%d", &op);

	if (op == 1)
		SalesmanLookUpGoodsByName(head);
	else if (op == 2)
		SalesmanLookUpGoodsByManufacturer(head);
	else if (op == 3)
		SalesmanLookUpGoodsByNameAndManufacturer(head);
	else {
		SalesmanInitMenu();
	}
}

void ShowQueriedGoodsListToSalesman(GoodsList queried_goods)
{
	printf("----------------------------------------------------\n");
	printf("%-5s %-12s %-6s %-15s %-5s\n", "ID", "名称", "售价", "生产厂商", "余量");
	TraverseGoodsList(queried_goods, DisplayBasicGoodsInfo);
	printf("----------------------------------------------------\n");
}

void SalesmanLookUpGoodsByName(GoodsList head)
{
	char goods_name_prefix[MAXGOODSNAME] = { 0 };
	//char manufacturer_prefix[MAXMANUFACTURERNAME] = { 0 };

	printf("输入商品名称或名称前缀\n>> ");
	scanf("%s", goods_name_prefix);
	GoodsList queried_goods = QueryGoodsByName(head, goods_name_prefix);
	ShowQueriedGoodsListToSalesman(queried_goods);
	DeleteGoodsList(queried_goods);
	system("pause");
	SalesmanLookUpGoods(head);
}

void SalesmanLookUpGoodsByManufacturer(GoodsList head)
{
	char manufacturer_prefix[MAXMANUFACTURERNAME] = { 0 };

	printf("输入商品生产商名称或生产商名称前缀\n>> ");
	scanf("%s", manufacturer_prefix);
	GoodsList queried_goods = QueryGoodsByManufacturer(head, manufacturer_prefix);
	ShowQueriedGoodsListToSalesman(queried_goods);
	DeleteGoodsList(queried_goods);
	system("pause");
	SalesmanLookUpGoods(head);
}

void SalesmanLookUpGoodsByNameAndManufacturer(GoodsList head)
{
	char goods_name_prefix[MAXGOODSNAME] = { 0 };
	char manufacturer_prefix[MAXMANUFACTURERNAME] = { 0 };

	printf("输入商品名称或名称前缀\n>> ");
	scanf("%s", goods_name_prefix);
	printf("输入商品生产商名称或生产商名称前缀\n>> ");
	scanf("%s", manufacturer_prefix);
	GoodsList queried_goods = QueryGoodsByNameAndManufacturer(head, goods_name_prefix, manufacturer_prefix);
	ShowQueriedGoodsListToSalesman(queried_goods);
	DeleteGoodsList(queried_goods);
	system("pause");
	SalesmanLookUpGoods(head);
}

