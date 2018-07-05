#include "stdafx.h"

//按照商品名前缀查询商品，输出商品基本信息
GoodsList QueryGoodsByName(GoodsList head, char *name)
{
	return QueryGoodsByNameAndManufacturer(head, name, "");
}

//按照生产厂商前缀查询商品，输出商品基本信息
GoodsList QueryGoodsByManufacturer(GoodsList head, char *manufacturer)
{
	return QueryGoodsByNameAndManufacturer(head, "", manufacturer);
}

//按照商品名和生产厂商前缀查询商品，输出商品基本信息
GoodsList QueryGoodsByNameAndManufacturer(GoodsList head, char *goods_name, char *manufacturer)
{
	if (head->next == NULL) 
		return NULL;


	GoodsList queried_goods = InitGoodsList();
	GoodsList p = head->next;
	while (p) {
		char goods_name_prefix[MAXGOODSNAME] = { 0 };
		char manufacturer_prefix[MAXMANUFACTURERNAME] = { 0 };
		strncpy(goods_name_prefix, p->goods.name, strlen(goods_name));
		strncpy(manufacturer_prefix, p->goods.manufacturer, strlen(manufacturer));
		if (strcmp(goods_name_prefix, goods_name) == 0 && strcmp(manufacturer_prefix, manufacturer) == 0) {
			GoodsList newNode = (GoodsList)malloc(sizeof(struct GoodsListNode));
			newNode->goods = p->goods;
			newNode->next = queried_goods->next;
			queried_goods->next = newNode;
		}
		p = p->next;
	}
	
	return queried_goods;
}


void QuerySoldRecordsByDate(RecordsList head, SoldDate start, SoldDate end)
{
	if (head->next == NULL) {
		printf("销售记录为空\n");
		return;
	}

	RecordsList p = head->next;
	printf("------------------------------------------------------------------\n");
	printf("%-5s %-12s %-8s %-6s %5s %15s\n", "ID", "名称", "进价", "售价", "购买量", "购买时间");
	while (p) {
		if (CompareDate(p->record.date, start) >= 0 && CompareDate(p->record.date, end) <= 0) {
			printf("%-5d %-12s %-8.2f %-8.2f %-6d %4d\\%02d\\%02d %02d:%02d:%02d\n", p->record.id, p->record.name,
				p->record.buying_price, p->record.selling_price, p->record.sold_quantity, p->record.date.year, 
				p->record.date.month, p->record.date.day, p->record.date.hour, p->record.date.min, p->record.date.second);
		}

		p = p->next;
	}
	printf("------------------------------------------------------------------\n");
}

