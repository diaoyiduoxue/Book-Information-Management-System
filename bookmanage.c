#include "bookmanage.h"
#include"Sqelist.h"
#include"book.h"
#include"config.h"
#include"menu.h"
#include"user.h"
#include<string.h>
static bool canop()
{
	extern User* g_curuser;
	if (!isBookad(g_curuser))
	{
		printf("\033[1;38;2;255;0;0m你没有权限,只有系统管理员有此权限\n");
		return false;
	}
	return true;
}
void bookmanage_init(Bookmanage* bmage)
{
	
	sqelist_init(&bmage->books);
	bookmanage_load(bmage, "./date/book.txt");
}

void bookmanage_quit(Bookmanage* bmage)
{

	FILE* fp = fopen("./date/book.txt", "w");
	
	fputs("记录号\t书号\t书名\t作者\t出版社\t藏书量\t借出数\n", fp);
	char buffer[BUFSIZ] = { 0 };
	size_t i = 0;
	foreach(Book * book, &bmage->books)
	{	/*
		size_t recordNO;//记录号
		size_t bookNO;//书号
		char name[30];//书名
		char author[30];//作者
		char press[30];//出版社
		int bookcnt;//藏书量
		int borrowcnt;//借出数
		*/
		sprintf(buffer, "%llu\t%llu\t%s\t%s\t%s\t%d\t%d\n", i++, book->bookNO, book->name,
			book->author,book->press, book->bookcnt, book->borrowcnt);
		fputs(buffer, fp);
	}
	fclose(fp);
}

void bookmanage_load(Bookmanage* bmage,const char*filename)
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
	while (fgets(buf, BUFSIZ, fp))//最后一行不会读两次
	{
		
		Book* book = createmptybook();
		int ret = sscanf(buf, "%llu %llu %s %s %s %d %d", &book->recordNO, &book->bookNO, book->name, book->author, book->press, &book->bookcnt,&book->borrowcnt);
		if (ret <= 0)
		{
			//printf("bookload sscanf failed\n");
			return;
		}
		sqelist_pushbake(&bmage->books, book);
	}
	fclose(fp);

}

void bookmanage_operation(Bookmanage* bmage)
{
	bool isquit = false;
	while (!isquit)
	{
		system("cls");
		int op = bookmenu();
		switch (op)
		{
		case 1:
			bookmanage_input(bmage);
			break;
		case 2:
			bookmamage_modify(bmage);
			break;
		case 3:
			bookmanage_serch(bmage);
			break;
		case 4:
			bookmanage_statistic(bmage);
			break;
		case 5:
			isquit = true;
			break;
		}
		system("pause");
	}
}

void bookmanage_input(Bookmanage* bmage)
{
	if (!canop())
	{
		return;
	}
	
	Book* book = createmptybook();
	printf("请输入图书（书号，作者，书名，出版社，藏书量）>>\033[38;2;207;1;255m");
	int ret = scanf_s("%llu %s %s %s %d", &book->bookNO, book->author,30,book->name,30,book->press,30,&book->bookcnt);
	foreach(Book*books,&bmage->books)
	{
		if (book->bookNO == books->bookNO)
		{
			
			printf("书号重复，已经被占用\n");
			printf("\033[1;38;2;255;0;0m添加书籍失败\033[0m\n");
			return;
		}
		

	}
	if (ret != 5)
	{
		printf("\033[1;38;2;255;0;0m添加书籍失败\033[0m\n");
		return;
	}
	else 
	{
		sqelist_pushbake(&bmage->books,book);
		printf("\033[1;38;2;255;0;0m添加图书成功\033[0m\n");
	}
}

void bookmamage_modify(Bookmanage* bmage)
{
	if (!canop())
	{
		return;
	}
	printf("请输入要修改的书号\033[38;2;207;1;255m\n");
	size_t bookno = -1;
	scanf_s("%llu", &bookno);
	Book* book = NULL;
	bool havebook=false;
	foreach(book, &bmage->books)
	{
		
		if (book->bookNO == bookno)
		{
			printf("\033[0m请输入修改后的藏书量\033[38;2;207;1;255m\n");
			int ret = scanf_s("%d", &book->bookcnt);
			if (ret == 1)
			{
				havebook = true;
				printf("\033[1;38;2;255;0;0m修改成功\033[0m\n");
				return;
			}
		}
	}
	if (!havebook)
	{
		printf("\033[1;38;2;255;0;0m你要找的书不存在\033[0m\n");
		return;
	}
}

void bookmanage_serch(Bookmanage* bmage)
{
	bool isquit = false;
	while (!isquit)
	{
		int op = booksearchmenu();
		switch (op)
		{
		case 1:
			search_bookNO(bmage);
			break;
		case 2:
			search_bookname(bmage);
			break;
		case 3:
			search_bookauthor(bmage);
			break;
		case 4:
			search_bookpress(bmage);
			break;
		case 5:
			isquit = true;
			break;
		}
	}
}

void search_bookNO(Bookmanage* bmage)
{
	size_t bookno = 1;
	Book* book = NULL;
	bool havebook = false;
	printf("请输入书号>>\033[38;2;207;1;255m");
	scanf_s("%llu", &bookno);
	foreach(book, &bmage->books)
	{
		if (book->bookNO == bookno)
		{
			printf("\033[38;2;180;255;245m%-8s %-5s %-10s %-10s %-10s %s %s \n", "记录号", "书号", "书名", "作者", "出版社", "藏书量", "借出量");
			printbook(book);
			havebook = true;
		}
		
	}
	if (!havebook)
	{
		printf("\033[1;38;2;255;0;0m你要找的书不存在\033[0m\n");
	}
}

void search_bookname(Bookmanage* bmage)
{
	char name[30] = { 0 };
	Book* book = NULL;
	bool havebook = false;
	printf("请输入书名>>\033[38;2;207;1;255m");
	gets_s(name, 30);
	foreach(book, &bmage->books)
	{
		if (strcmp(book->name,name)==0)
		{
			printf("\033[38;2;180;255;245m%-8s %-5s %-10s %-10s %-10s %s %s \n", "记录号", "书号", "书名", "作者", "出版社", "藏书量", "借出量");
			printbook(book);
			havebook = true;
		}
		
	}
	if (!havebook)
	{
		printf("\033[1;38;2;255;0;0m你要找的书不存在\033[0m\n");
	}
}

void search_bookauthor(Bookmanage* bmage)
{
	char auther[30] = { 0 };
	Book* book = NULL;
	//Book* prebook = NULL;
	bool havebook = false;
	printf("请输入作者的名字>>\033[38;2;207;1;255m");
	gets_s(auther, 30);
	foreach(book, &bmage->books)
	{
		if (strcmp(book->author, auther) == 0)
		{
			printf("\033[38;2;180;255;245m%-8s %-5s %-10s %-10s %-10s %s %s \033[0m\n", "记录号", "书号", "书名", "作者", "出版社", "藏书量", "借出量");
			printbook(book);
			//prebook = book;
			havebook = true;
		}

	}
	if (!havebook)
	{
		printf("\033[1;38;2;255;0;0m你要找的书不存在\033[0m\n");
	}
}

void search_bookpress(Bookmanage* bmage)
{
	char press[30] = { 0 };
	Book* book = NULL;
	bool havebook = false;
	printf("请输入出版社的名称>>\033[38;2;207;1;255m");
	gets_s(press, 30);

	foreach(book, &bmage->books)
	{
		if (strcmp(book->press, press) == 0)
		{
			printf("\033[38;2;180;255;245m%-8s %-5s %-10s %-10s %-10s %s %s \n", "记录号", "书号", "书名", "作者", "出版社", "藏书量", "借出量");
			printbook(book);
			havebook =true;
		}

	}
	if (!havebook)
	{
		printf("\033[1;38;2;255;0;0m你要找的书不存在\033[0m\n");
	}
}
void bookmanage_statistic(Bookmanage* bmage)
{
	extern User* g_curuser;
	if (!isBookad(g_curuser))
	{
		printf("\033[1;38;2;255;0;0m你没有权限,只有图书管理员有此权限\033[0m\n");
		return;
	}
	int i = 0;
	int cnt=0;
	int borcnt=0;
	int curcnt=0;
	foreach(Book * book, &bmage->books)
	{
		++i;
		cnt += book->bookcnt;
		borcnt += book->borrowcnt;
		curcnt = cnt - borcnt;
	}
	printf("图书馆有书籍[%d]种，藏书量[%d]本，借出[%d]本，现有[%d]本", i,cnt, borcnt, curcnt);
}
