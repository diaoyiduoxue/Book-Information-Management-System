#include "circulatemanage.h"
#include"bookcircle.h"
#include"config.h"
#include"bookmanage.h"

#include"reader.h"
#include"Sqelist.h"
#include"book.h"
#include"menu.h"
#include<string.h>
#include<time.h>
void cirmanage_init(Circulatemanage* cirmage,Bookmanage*bmage, ReaderManage* readermge)
{
	init_linklist(&cirmage->cirmanagelist);
	cirmanage_load(cirmage, "./date/bookcircle.txt");

	cirmage->bookmanage = bmage;
	cirmage->readermanage = readermge;
}

static void bookcirculate_save(Circulate*cir,FILE*fp)
{
	char buffer[BUFSIZ] = { 0 };
	sprintf(buffer, "%llu\t%d\t%s\t%s\t%s\n", cir->readerNO,cir->bookNO,cir->borrowdate,cir->returndate,cir->remark);
	fputs(buffer, fp);
}
void cirmanage_quit(Circulatemanage* cirmage)
{
	FILE* fp = fopen("./date/bookcircle.txt", "w");
	fputs("读者号\t书号\t借书日期\t还书日期\t备注\n", fp);
	Node* curNode = cirmage->cirmanagelist.front;
	while (curNode->next)
	{
		curNode = curNode->next;
		bookcirculate_save(curNode->date, fp);
	}
	fclose(fp);
}

void cirmanage_load(Circulatemanage* cirmage,const char*filename)
{
	FILE* fp = fopen(filename, "r");
	if (!fp)
	{
		perror("open failed");
		return;
	}
	//读取数据
	char buf[BUFSIZ] = { 0 };
	fgets(buf, BUFSIZ, fp);//读取表头文字
	while (fgets(buf, BUFSIZ, fp))
	{
		Circulate* cir = createmptycir();
		int ret = sscanf(buf, "%llu %d %s %s %s ", &cir->readerNO, &cir->bookNO, cir->borrowdate, cir->returndate, cir->remark);
		if (ret <= 0)
		{
			//printf("circle sscanf failed\n");
			return;
		}
		link_bakeinsert(&cirmage->cirmanagelist, cir);
	}
	fclose(fp);

}

void cirmanage_operation(Circulatemanage* cirmage)
{
	bool isquit = false;
	while (!isquit)
	{
		system("cls");
		int op = bookcirculatemenu();
		switch (op)
		{
		case 1:
			cirmanage_borrowbook(cirmage);
			break;
		case 2:
			cirmanage_returnbook(cirmage);
			break;
		case 3:
			isquit = true;
			break;
		}
		system("pause");
	}
}
bool cir_reader_cmp(variant v1, variant v2)
{
	Reader* reader = v1;
	unsigned long long num = v2;
	return reader->readerID == num;
}
void cirmanage_borrowbook(Circulatemanage* cirmage)
{
	bool find=false;
	printf("请输入借书的读者号，书号>>\033[38;2;207;1;255m");
	Circulate* cir = createmptycir();
	int ret=scanf_s("%llu %d", &cir->readerNO, &cir->bookNO);
	struct tm* tp;
	time_t t;
	time(&t);
	tp = localtime(&t);
	char buff[12];
	if (tp->tm_mon + 1 < 10 && tp->tm_mday < 10)
		sprintf(buff, "%d/0%d/0%d", tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday);
	else if (tp->tm_mon + 1 >= 10 && tp->tm_mday < 10)
		sprintf(buff, "%d/%d/0%d", tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday);
	else if (tp->tm_mon + 1 < 10 && tp->tm_mday >= 10)
		sprintf(buff, "%d/0%d/%d", tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday);
	else
		sprintf(buff, "%d/%d/%d", tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday);
	strcpy(cir->returndate, buff);
	Reader* reader = link_callbake_search(&cirmage->readermanage->readerlist, cir_reader_cmp, cir->readerNO);
	if (ret == 2)
	{
		if (!reader)
		{
			printf("\033[1;38;2;255;0;0m读者库里没有这个读者\033[0m\n");
			return;
		}
		
		foreach(Book * book, &cirmage->bookmanage->books)
		{
			if (book->bookNO == cir->bookNO)
			{
				book->borrowcnt += 1;
				reader->yetborrowcnt += 1;
				//判断是否借太多书没还
				if (reader->yetborrowcnt > 10)
				{
					printf("\033[1;38;2;255;0;0m您借书的数量已经超过上限了，请及时归还已借的书籍，此次借书操作失败！！\n\033[0m");
					reader->yetborrowcnt -= 1;//因为借书操作失败了，所以这次的加一不能算
					return;
				}
				find = true;
				Break;
			}
			
		}
		if (find)
		{
			printf("\033[1;38;2;255;0;0m添加借书信息成功\033[0m\n");
			link_bakeinsert(&cirmage->cirmanagelist, cir);
		}
		else 
		{
			printf("\033[1;38;2;255;0;0m书库里没有这本书\033[0m\n");
		}
		
	}
}
static bool outdate(char* bdate, char* rdate)
{
	//根据格式4,7位为'/'
	bdate[4] = bdate[7] = '0';
	rdate[4] = rdate[7] = '0';
	unsigned long long llubdate, llurdate;
	sscanf(bdate, "%llu", &llubdate);
	sscanf(rdate, "%llu", &llurdate);
	bdate[4] = bdate[7] = '/';
	rdate[4] = rdate[7] = '/';
	if (llurdate - llubdate > 3000)
		return true;
	else
		return false;
}
static bool cmp_cir(Circulate* c1,Circulate* c2)
{
	return (c1->bookNO == c2->bookNO && c1->readerNO == c2->readerNO);
}
void cirmanage_returnbook(Circulatemanage* cirmage)
{
	Circulate cir;
	printf("请输入要还图书的读者的读者号和图书的书号>>\033[38;2;207;1;255m");
	scanf_s("%llu %d", &cir.readerNO, &cir.bookNO);
	Circulate*circulate=link_callbake_search(&cirmage->cirmanagelist, cmp_cir, &cir);
	if (!circulate)
	{
		printf("\033[1;38;2;255;0;0m没有读者或该读者没有借过这本书\033[0m\n");
		return;
	}
	else
	{
		/*printf("请输入还书日期:");
		scanf_s("%s", circulate->returndate, 12);*/
		struct tm* tp;
		time_t t;
		time(&t);
		tp = localtime(&t);
		char buff[12];
		if (tp->tm_mon + 1 < 10 && tp->tm_mday < 10)
			sprintf(buff, "%d/0%d/0%d", tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday);
		else if (tp->tm_mon + 1 >= 10 && tp->tm_mday < 10)
			sprintf(buff, "%d/%d/0%d", tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday);
		else if (tp->tm_mon + 1 < 10 && tp->tm_mday >= 10)
			sprintf(buff, "%d/0%d/%d", tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday);
		else
			sprintf(buff, "%d/%d/%d", tp->tm_year + 1900, tp->tm_mon + 1, tp->tm_mday);
		strcpy(circulate->returndate, buff);
		if (outdate(circulate->borrowdate, circulate->returndate))
		{
			strcpy(circulate->remark, "逾期归还");
		}
	}
	//link_removeone(&cirmage->cirmanagelist, circulate);
	Reader* reader = link_callbake_search(&cirmage->readermanage->readerlist, cir_reader_cmp, cir.readerNO);
	//在读者库里找到还书的这个读者，因为读者借了多少本书这个信息是放在Reader里的不是Circulate里的。
	foreach(Book * book, &cirmage->bookmanage->books)
	{
		if (book->bookNO == cir.bookNO)
		{
			book->borrowcnt -= 1;
			reader->yetborrowcnt -= 1;//还书了，已借书数要减一
			Break;
		}
	}
}
