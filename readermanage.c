#include "readermanage.h"
#include"config.h"
#include"menu.h"
#include"reader.h"
#include"user.h"

static bool canop()
{
	extern User* g_curuser;
	int i = 0;
	if (!isBookad(g_curuser))
	{
		printf("\033[1;38;2;255;0;0m你没有权限,只有系统管理员有此权限\n\033[0m");
		i = 10;
		return false;
	}
	return true;
}
void readermanage_init(ReaderManage* rmage)
{
	init_linklist(&rmage->readerlist);
	readermanage_loadedate(rmage, "./date/reader.txt");
}
static void reader_save(Reader*reader, FILE* fp)
{
	char buffer[BUFSIZ] = { 0 };
	sprintf(buffer, "%llu\t%s\t%s\t%s\t%d\t%d\n", reader->readerID, reader->readername, reader->readerworkplace, reader->readertel, reader->canborrowcnt, reader->yetborrowcnt);
	fputs(buffer, fp);
}
void readermanage_quit(ReaderManage* rmage)
{
	FILE* fp = fopen("./date/reader.txt", "w");
	fputs("读者ID\t读者名\t工作单位\t联系方式\t可借书数\t已借书数\n", fp);
	Node* curNode = rmage->readerlist.front;
	while (curNode->next)
	{
		curNode = curNode->next;
		reader_save(curNode->date, fp);
	}
	fclose(fp);
}

void readermanage_loadedate(ReaderManage* rmage,const char*filename)
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
		
		Reader* reader = createmptyreader();
		int ret = sscanf(buf, "%llu %s %s %s %d %d", &reader->readerID, reader->readername, reader->readerworkplace, reader->readertel, &reader->canborrowcnt, &reader->yetborrowcnt);
		if (ret <= 0)
		{
			//printf("reader sscanf failed\n");
			return;
		}
		link_bakeinsert(&rmage->readerlist, reader);
	}
	fclose(fp);


}

void readermanage_operation(ReaderManage* rmage)
{
	bool isquit = false;
	while (!isquit)
	{
		system("cls");
		int op = readermenu();
		switch (op)
		{
		case 1:
			readermanage_input(rmage);
			break;
		case 2:
			readermanage_modify(rmage);
			break;			   
		case 3:
			readermanage_remove(rmage);
			break;			  
		case 4:
			readermanage_search(rmage);
			break;
		case 5:
			readermanage_show(rmage);
			break;
		case 6:
			isquit = true;
			break;
		}
		system("pause");
	}
}

void readermanage_input(ReaderManage* rmage)
{
	if (!canop())
		return;
	printf("\033[3m\033[1m请输入读者( 读者ID 读者姓名 工作单位 联系方式 可借书数 已借书数)\033[38;2;207;1;255m\n");
	Reader* reader = createmptyreader();
	int  count = scanf_s("%llu %s %s %s %d %d", &reader->readerID,reader->readername,20,reader->readerworkplace,30,reader->readertel,15,&reader->canborrowcnt,&reader->yetborrowcnt);
	if (count == 6)
	{
		printf("\033[1;38;2;255;0;0m添加用户成功\033[0m\n");
		link_bakeinsert(&rmage->readerlist, reader);
	}
}



bool reader_cmp(variant v1, variant v2)
{
	Reader* reader = v1;
	unsigned long long num = v2;
	return reader->readerID == num;
}

void readermanage_modify(ReaderManage* rmage)
{
	if (!canop())
	{
		return;
	}
	printf("请输入你要修改的读者的ID>\033[38;2;207;1;255m\n");
	unsigned long long number = -1;
	scanf_s("%llu", &number);
	Reader* reader = link_callbake_search(&rmage->readerlist, reader_cmp, number);
	if (!reader)
	{
		printf("\033[1;38;2;255;0;0m没有你要找的用户\033[0m\n");
		return;
	}
	else
	{
		const int modifyte = 1 << 0;
		const int modifywork = 1 << 1;
		int ifmodifyte, ifmodifywork;
		printf("请输入两个值，第一个为1表示修改联系方式，第二个为2表示修改工作单位，不修改输入0\n>>");
		scanf("%d %d", &ifmodifyte, &ifmodifywork);
		int op = ifmodifyte | ifmodifywork;
		if (op & modifyte)
		{
			printf("\033[0m请输入修改后的联系方式\033[38;2;207;1;255m\n");
			scanf_s("%s", reader->readertel, 16);
			printf("\033[1;38;2;255;0;0m修改成功\033[0m\n");
		}
		if (op & modifywork)
		{
			printf("请输入修改后的工作单位\033[38;2;207;1;255m\n");
			scanf_s("%s", reader->readerworkplace, 30);
			printf("\033[1;38;2;255;0;0m修改成功\033[0m\n");
		}
		
	}
}

void readermanage_remove(ReaderManage* rmage)
{
	if (!canop())
	{
		return;
	}
	printf("请输入你要删除的读者的ID>\033[38;2;207;1;255m\n");
	unsigned long long number = -1;
	scanf_s("%llu", &number);
	Reader* reader = link_callbake_search(&rmage->readerlist, reader_cmp, number);
	if (!reader)
	{
		printf("\033[1;38;2;255;0;0m没有你要删除的读者\033[0m\n");
		return;
	}
	link_removeone(&rmage->readerlist, reader);
	printf("\033[1;38;2;255;0;0m读者删除成功\033[0m\n");
}

void readermanage_search(ReaderManage* rmage)
{
	if (!canop())
	{
		return;
	}
	printf("请输入你要查找的读者的ID>\033[38;2;207;1;255m\n");
	unsigned long long number = -1;
	scanf_s("%llu", &number);
	Reader* reader = link_callbake_search(&rmage->readerlist, reader_cmp, number);
	if (!reader)
	{
		printf("\033[1;38;2;255;0;0m没有你要查找的读者\033[0m\n");
		return;
	}
	else
	{
		printf("\033[03;01m\033[38;2;180;255;245m%-10s %-10s	%-20s %-15s %s %s\n", "读者ID", "读者姓名", "工作单位", "联系方式", "可借书数", "已借书数");
		printreader(reader);
	}
	
}

void readermanage_show(ReaderManage* rmage)
{
	if (!canop())
	{
		return;
	}
	printf("\033[01m%-10s %-10s	%-20s %-15s %s %s\n", "读者ID", "读者姓名","工作单位", "联系方式","可借书数","已借书数");
	link_callbake(&rmage->readerlist, printreader);
}
