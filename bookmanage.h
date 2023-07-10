#ifndef _BOOKMANAGE_H_
#define _BOOKMANAGE_H_
#include"Sqelist.h"

typedef struct Bookmanage
{
	sqelist books;
}Bookmanage;
void bookmanage_init(Bookmanage* bmage);

void bookmanage_quit(Bookmanage* bmage);

void bookmanage_load(Bookmanage* bmage,const char*filename);

void bookmanage_operation(Bookmanage* bmage);
void bookmanage_input(Bookmanage* bmage);

void bookmamage_modify(Bookmanage* bmage);

void bookmanage_serch(Bookmanage* bmage);
void search_bookNO(Bookmanage* bmage);//按书号搜索
void search_bookname(Bookmanage* bmage);//按书名搜索
void search_bookauthor(Bookmanage* bmage);//按作者搜索
void search_bookpress(Bookmanage* bmage);//按出版社搜索
void bookmanage_statistic(Bookmanage* bmage);
#endif
