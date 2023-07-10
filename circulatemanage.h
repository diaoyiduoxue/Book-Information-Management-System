#ifndef _CIRCULATEMANAGE_H_
#define _CIRCULATEMANAGE_H_
#include"linkilst.h"
#include"bookmanage.h"
#include"readermanage.h"
typedef struct Bookmanage Bookmanage;
typedef struct Circulatemanage
{
	list cirmanagelist;
	Bookmanage*bookmanage;//修改图书的数据
	ReaderManage* readermanage;
}Circulatemanage;

void cirmanage_init(Circulatemanage* cirmage,Bookmanage*bmage,ReaderManage*readermge);

void cirmanage_quit(Circulatemanage* cirmage);//退出时保存修改的数据

void cirmanage_load(Circulatemanage* cirmage,const char*filename);

void cirmanage_operation(Circulatemanage* cirmage);
void cirmanage_borrowbook(Circulatemanage* cirmage);//添加借书信息
void cirmanage_returnbook(Circulatemanage* cirmage);//还书，删除借书信息
#endif
