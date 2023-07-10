#include<string.h>
#include "usermanage.h"
#include"config.h"
#include"linkilst.h"
#include"user.h"
#include"menu.h"
User* g_curuser = NULL;
void userMana_init(UserManage* umage)
{
	init_linklist(&umage->userlist);
	umage->curuser = NULL;
	
	userManage_loadeDate(umage, "./date/user.txt");
}
static void user_save(User* user,FILE*fp)
{
	char buffer[BUFSIZ] = { 0 };
	sprintf(buffer, "%llu\t%s\t%d\n", user->number, user->passward, user->type);
	fputs(buffer, fp);
}
void userManage_quit(UserManage* umage)
{
	FILE* fp = fopen("./date/user.txt", "w");
	fputs("用户名\t密码\t类型\n", fp);
	Node* curNode = umage->userlist.front;
	while (curNode->next)
	{
		curNode = curNode->next;
		user_save(curNode->date,fp);
	}
	fclose(fp);
}



void userManage_loadeDate(UserManage* umage, const char* filename)
{
	FILE* fp = fopen("./date/user.txt", "rb");
	if (!fp)
	{
		//perror("open failed");
		return;
	}
	//读取数据
	char buf[BUFSIZ] = { 0 };
	fgets(buf, BUFSIZ, fp);//读取表头文字
	while (fgets(buf, BUFSIZ, fp))
	{
		
		User* user = createmptyuser();
		int ret = sscanf(buf, "%llu %s %d", &user->number, user->passward, &user->type);
		if (ret <= 0)
		{
			//printf("user sscanf failed\n");
			return;
		}
		link_bakeinsert(&umage->userlist, user);
	}
	fclose(fp);
}
static bool UserCmp(User* u1, User* u2)
{
	return (u1->number == u2->number && strcmp(u1->passward,u2->passward)==0);
}
bool userManage_login(UserManage* umage, unsigned long long number, const char* passwar)
{
	User user;
	user.number = number;
	strcpy(user.passward, passwar);
	User*u=link_callbake_search(&umage->userlist, UserCmp, &user);//u1 is userlist,u2 is user
	if (!u)
		return false;
	else
	{
		umage->curuser = u;
		g_curuser = u;
		return true;
	}
		
}

void userManaopration(UserManage* umage)
{
	bool isquit = false;
	while (!isquit)
	{
		system("cls");
		int op = usermenu();
		switch (op)
		{
		case 1:
			userManage_input(umage);
			break;
		case 2:
			userManagetype_modify(umage);
			break;
		case 3:
			userManage_remove(umage);
			break;
		case 4:
			userManage_show(umage);
			break;
		case 5:
			userManage_passwardmodify(umage);
			break;
		case 6:
			isquit = true;
			break;
		}
		system("pause");
	}
}

void userManage_input(UserManage* umage)
{
	if (!isSysad(umage->curuser))
	{
		printf("\033[38;2;255;0;0m你没有权限,只有系统管理员有此权限\n\033[0m");
		return;
	}
	printf("请输入用户（ID 密码 类型）\033[38;2;207;1;255m\n");
	User* user = createmptyuser();
    int  count=scanf_s("%llu %s %d", &user->number, &user->passward,16, &user->type);
	if (count == 3)
	{
		printf("\033[38;2;255;0;0m添加用户成功\033[0m\n");
		link_bakeinsert(&umage->userlist, user);
		
	}
	else
	{
		printf("\033[38;2;255;0;0m添加用户失败\033[0m\n");
		return;
	}
}
bool user_cmp(variant v1, variant v2)
{
	User* user = v1;
	unsigned long long num = v2;
	return user->number == num;
}

void userManagetype_modify(UserManage* umage)
{
	if (!isSysad(umage->curuser))
	{
		printf("\033[38;2;255;0;0m你没有权限,只有系统管理员有此权限\n\033[0m");
		return;
	}
	printf("请输入你要修改的用户ID>\033[38;2;207;1;255m\n");
	unsigned long long number = -1;
	scanf_s("%llu", &number);
	User*user=link_callbake_search(&umage->userlist, user_cmp, number);
	if (!user)
	{
		printf("\033[38;2;255;0;0m没有你要找的用户\033[0m\n");
		return;
	}
	else
	{
		int type = user->type;
		printf("请输入修改后的类型（1，2，3）\033[38;2;207;1;255m\n");
		scanf_s("%d", &user->type);
		if (user->type == 1 || user->type == 2 || user->type == 3)
		{
			printf("\033[38;2;255;0;0m修改成功\033[0m\n");
		}
		else
		{
			printf("\033[38;2;255;0;0m修改失败，仍是未修改前类型\033[0m\n");
			user->type = type;
		}
	}
}

void userManage_remove(UserManage* umage)
{
	if (!isSysad(umage->curuser))
	{
		printf("\033[38;2;255;0;0m你没有权限,只有系统管理员有此权限\n\033[0m");
		return;
	}
	printf("请输入你要删除的用户ID>\033[38;2;207;1;255m\n");
	unsigned long long number = -1;
	scanf_s("%llu", &number);
	User* user = link_callbake_search(&umage->userlist, user_cmp, number);
	if (!user)
	{ 
		printf("\033[38;2;255;0;0m没有你要删除的用户\033[0m\n");
		return;
	}
	link_removeone(&umage->userlist, user);
	printf("\033[38;2;255;0;0m用户删除成功\033[0m\n");
}

void userManage_show(UserManage* umage)
{
	if (!isSysad(umage->curuser))
	{
		printf("\033[1;38;2;255;0;0m你没有权限,只有系统管理员有此权限\n\033[0m");
		return;
	}
	printf("\033[01m%-10s %-16s	%-10s\n", "用户ID", "用户密码", "用户类型");
	link_callbake(&umage->userlist, printuser);
}

void userManage_passwardmodify(UserManage* umage)
{
	if (!isSysad(umage->curuser))
	{
		printf("\033[38;2;255;0;0m你没有权限,只有系统管理员有此权限\n\033[0m");
		return;
	}
	printf("请输入你要修改密码的用户ID>\033[3m\033[1m\033[38;2;207;1;255m\n");
	unsigned long long number = -1;
	scanf_s("%llu", &number);
	User* user = link_callbake_search(&umage->userlist, user_cmp, number);
	if (!user)
	{
		printf("\033[38;2;255;0;0m没有你要找的用户\n");
		return;
	}
	else
	{
		printf("请输入修改后的密码\033[3m\033[1m\033[38;2;207;1;255m\n");
		int count = scanf_s("%s", user->passward,(unsigned int)sizeof(user->passward));
		if (count == 1)
		{
			printf("\033[1m\033[38;2;255;0;0m !\033[0m\ 修改成功\033[1m\033[38;2;255;0;0m !\033[0m\n");
		}
	}

}

