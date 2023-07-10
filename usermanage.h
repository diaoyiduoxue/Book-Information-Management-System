#ifndef _USERMANAGE_H_
#define _USERMANAGE_H_
#include"linklist.h"
#include"user.h"

typedef struct UserManage
{
	list userlist;
	User* curuser;//记录当前登录的用户
	
}UserManage;

//初始化管理结构
void userMana_init(UserManage* umage);
void userManage_quit(UserManage* umage);
void userManage_loadeDate(UserManage* umage, const char* filename);//信息加载
bool userManage_login(UserManage* umage, unsigned long long number, const char* passwar);//判断登录时候成功
void userManaopration(UserManage* umage);
void userManage_input(UserManage* umage);//用户信息输入
void userManagetype_modify(UserManage* umage);//用户信息修改
void userManage_remove(UserManage* umage);//用户信息删除
void userManage_show(UserManage* umage);//用户信息显示
void userManage_passwardmodify(UserManage* umage);//用户密码修改

#endif
