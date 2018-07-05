#include "stdafx.h"

const char GOODS_SALES_RECORD_PATH[50] = "Data\\sold_goods_list.txt";

//初始化销售记录裂变，创建带头结点的链表
RecordsList InitRecordsList()
{
	RecordsList head = (RecordsList)malloc(sizeof(struct RecordsListNode));
	head->next = NULL;

	return head;
}


void DeleteRecordsList(RecordsList head)
{
	GoodsList next;

	while (head) {
		next = head->next;
		free(head);
		head = next;
	}
}

//遍历销售记录链表，进行某种操作
void TraverseRecordsList(RecordsList head,void(*Fun)(SoldGoodsRecord *))
{
	RecordsList p = head->next;
	while (p) {
		Fun(&p->record);
		p = p->next;
	}
}

//输出一个销售记录的信息
void DisplayARecordInfo(SoldGoodsRecord *record)
{
	printf("%d %s %.2f %.2f %d %d-%d-%d-%d:%d:%d\n", record->id, record->name, record->buying_price,
		record->selling_price, record->sold_quantity, record->date.year, record->date.month, record->date.day,
		record->date.hour, record->date.min, record->date.second);
}

//在销售记录链表尾部增加一条销售记录信息
void AddRecordToList(RecordsList head, SoldGoodsRecord record)
{
	RecordsList newNode = (RecordsList)malloc(sizeof(struct RecordsListNode));
	newNode->record = record;
	newNode->next = NULL;

	RecordsList p = head;
	while (p->next) p = p->next;
	
	p->next = newNode;
}

FILE* OpenRecordsFile(char *mod)
{
	return fopen(GOODS_SALES_RECORD_PATH, mod);
}

//向文件中新增加一条销售记录数据
void AppendARecordToFile(SoldGoodsRecord record, FILE *fp)
{
	fprintf(fp, "%d %s %.2f %.2f %d %d-%d-%d-%d:%d:%d\n", record.id, record.name, record.buying_price,
		record.selling_price, record.sold_quantity, record.date.year, record.date.month, record.date.day,
		record.date.hour, record.date.min, record.date.second);

	fclose(fp);

}

//从文件中导入销售记录数据
void ImportRecordsFromFile(RecordsList head, FILE *fp)
{
	SoldGoodsRecord record;
	while (!feof(fp))
	{
		fscanf(fp, "%d %s %lf %lf %d %d-%d-%d-%d:%d:%d\n", &record.id, record.name, &record.buying_price,
			&record.selling_price, &record.sold_quantity, &record.date.year, &record.date.month,& record.date.day,
			&record.date.hour, &record.date.min, &record.date.second);
		AddRecordToList(head, record);
	}
	
	fclose(fp);
}

//获取销售时间
SoldDate GetNowDate()
{
	SoldDate date;
	time_t now;
	struct tm *tm_now;
	time(&now);
	tm_now = localtime(&now);

	date.year = tm_now->tm_year + 1900;
	date.month = tm_now->tm_mon + 1;
	date.day = tm_now->tm_mday;
	date.hour = tm_now->tm_hour;
	date.min = tm_now->tm_min;
	date.second = tm_now->tm_sec;

	return date;
}


