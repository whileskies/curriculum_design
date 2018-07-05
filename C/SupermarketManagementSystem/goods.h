#ifndef GOODS_H
#define GOODS_H

#define MAXGOODSNAME 30
#define MAXMANUFACTURERNAME 50


typedef struct 
{
	int id;
	char name[MAXGOODSNAME];
	double buying_price;
	double selling_price;
	char manufacturer[MAXMANUFACTURERNAME];
	int quantity;
} Goods;

typedef struct GoodsListNode *GoodsList;
struct GoodsListNode
{
	Goods goods;
	GoodsList next;
};

typedef struct
{
	int year;
	int month;
	int day;
	int hour;
	int min;
	int second;
}SoldDate;


typedef struct
{
	int id;
	char name[MAXGOODSNAME];
	double buying_price;
	double selling_price;
	int sold_quantity;
	SoldDate date;
}SoldGoodsRecord;

typedef struct RecordsListNode *RecordsList;
struct RecordsListNode
{
	SoldGoodsRecord record;
	RecordsList next;
};

typedef struct
{
	char account[15];
	char password[15];
	int permission_level;
}UserAccount;


#endif // !GOODS_H