#ifndef _USER_H_
#define _USER_H_
#include"config.h"


/*枚举用户类型*/
enum usertype
{
	ut_sysadminuser=1,		//系统管理员
	ut_bookadminuser,		//图书管理员
	ut_commentuser			//普通读者
};
typedef struct user
{
	unsigned long long number;
	char passward[16];
	int type;
}User;
User* createmptyuser();
void printuser(User* user);
bool isSysad(User* user);
bool isBookad(User* user);
bool isComuser(User* user);
#endif
