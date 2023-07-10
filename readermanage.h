#ifndef _READERMANAGE_H
#define _READERMANGE_H
#include"linkilst.h"
#include"reader.h"
typedef struct ReaderManage
{
	list readerlist;
}ReaderManage;
void readermanage_init(ReaderManage* rmage);
void readermanage_quit(ReaderManage* rmage);
void readermanage_loadedate(ReaderManage* rmage,const char*filename);
void readermanage_operation(ReaderManage* rmage);
//读者信息输入
void readermanage_input(ReaderManage* rmage);
//读者信息修改
void readermanage_modify(ReaderManage* rmage);
//读者信息删除
void readermanage_remove(ReaderManage* rmage);
//读者信息查找
void readermanage_search(ReaderManage* rmage);
//读者信息显示
void readermanage_show(ReaderManage* rmage);
#endif
