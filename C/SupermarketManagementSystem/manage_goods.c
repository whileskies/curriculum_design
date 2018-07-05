#include "stdafx.h"

const char GOODS_LIST_PATH[30] = "Data\\goods_list.txt";

//初始化商品链表 创建带头结点的链表
GoodsList InitGoodsList()
{
	GoodsList head = (GoodsList)malloc(sizeof(struct GoodsListNode));
	head->next = NULL;

	return head;
}

void DeleteGoodsList(GoodsList head)
{
	GoodsList next;

	while (head) {
		next = head->next;
		free(head);
		head = next;
	}
}

//遍历商品链表，进行某种操作
void TraverseGoodsList(GoodsList head, void(*Fun)(Goods *))
{
	GoodsList p = head->next;
	while (p) {
		Fun(&p->goods);
		p = p->next;
	}
}


//输出一个商品的信息
void DisplayGoodsInfo(Goods *goods)
{
	printf("%-5d %-12s %-6.2f %-6.2f %-15s %-5d\n", goods->id, goods->name, goods->buying_price, goods->selling_price,
																goods->manufacturer, goods->quantity);
}

//显示一个商品基本信息
void DisplayBasicGoodsInfo(Goods *goods)
{
	printf("%-5d %-12s %-6.2f %-15s %-5d\n", goods->id, goods->name, goods->selling_price, goods->manufacturer, goods->quantity);
}


//在商品链表中添加一条商品信息，原有此商品数量合并，返回1
//原没有，在链表末尾添加，返回0
int AddGoodsToList(GoodsList head, Goods goods)
{
	int id = goods.id;
	GoodsList p = head->next;
	while (p) {
		if (p->goods.id == id) {
			p->goods.quantity += goods.quantity;
			return 1;
		}
		p = p->next;
	}
	
	GoodsList newNode = (GoodsList)malloc(sizeof(struct GoodsListNode));
	newNode->goods = goods;
	newNode->next = head->next;
	head->next = newNode;
	
	return 0;
}


//在商品链表中查找商品序号为id的商品，该商品数量减少quantity
//成功返回1，商品数量不够返回0，无此id商品返回-1
int ReduceGoodsQuantity(GoodsList head, int id, int quantity)
{
	GoodsList p = head->next;
	while (p) {
		if (p->goods.id == id) {
			if (p->goods.quantity < quantity)
				return 0;
			p->goods.quantity -= quantity;
			return 1;
		}
		p = p->next;
	}
	return -1;
}


//在商品链表中查找商品序号为id的商品，该商品数量增加quantity
//成功返回1，无此id商品返回-1
int IncreaseGoodsQuantity(GoodsList head, int id, int quantity)
{
	GoodsList p = head->next;
	while (p) {
		if (p->goods.id == id) {
			p->goods.quantity += quantity;
			return 1;
		}
		p = p->next;
	}
	return -1;
}


//清除商品链表中为数量为0的商品
void RemoveZeroQuantityGoods(GoodsList head)
{
	GoodsList pre = head;
	GoodsList p = head->next;
	while (p) {
		if (p->goods.quantity == 0) {
			GoodsList tmp = p;
			pre->next = tmp->next;
			free(tmp);
			p = pre->next;
		}
		else {
			p = p->next;
			pre = pre->next;
		}
	}
}


//从文件中导入商品数据
void ImportGoodsFromFile(GoodsList head, FILE *fp)
{
	Goods goods;
	while (!feof(fp))
	{
		fscanf(fp, "%d %s %lf %lf %s %d\n", &goods.id, goods.name, &goods.buying_price,
			&goods.selling_price, goods.manufacturer, &goods.quantity);
		AddGoodsToList(head, goods);
	}
	fclose(fp);
}

FILE* OpenGoodsFile(char *mod)
{
	return fopen(GOODS_LIST_PATH, mod);
}

//将系统内商品数据导出到文件
void ExportGoodsToFile(GoodsList head, FILE *fp)
{
	Goods goods;
	GoodsList p = head->next;
	while (p) {
		goods = p->goods;
		fprintf(fp, "%d %s %.2lf %.2lf %s %d\n", goods.id, goods.name, goods.buying_price,
			goods.selling_price, goods.manufacturer, goods.quantity);
		p = p->next;
	}
	fclose(fp);
}


//有ID在商品链表中查找商品，查找到返回链表所在位置，否则返回NULL
GoodsList FindGoodsByID(GoodsList head, int id)
{
	if (id < 0) return NULL;

	GoodsList p = head->next;
	while (p) {
		if (p->goods.id == id)
			return p;
		p = p->next;
	}
	
	return NULL;
}


