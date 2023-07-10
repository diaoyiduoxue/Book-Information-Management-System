#include"config.h"
#include"menu.h"
#include"linkilst.h"
#include"Sqelist.h"
#include"usermanage.h"
#include"user.h"
#include"readermanage.h"
#include"reader.h"
#include"bookmanage.h"
#include"book.h"
#include"bookcircle.h"
#include"circulatemanage.h"

typedef struct management
{
	UserManage usermanage;
	ReaderManage readermanage;
	Bookmanage bookmanage;
	Circulatemanage circulatemage;
}management;
void manage_init(management* m)//初始化
{
	userMana_init(&(m->usermanage));
	readermanage_init(&m->readermanage);
	bookmanage_init(&m->bookmanage);
	cirmanage_init(&m->circulatemage,&m->bookmanage,&m->readermanage);
}
void Quit(management* m)//退出系统
{
	userManage_quit(&m->usermanage);
	readermanage_quit(&m->readermanage);
	cirmanage_quit(&m->circulatemage);
	bookmanage_quit(&m->bookmanage);
	exit(0);
}
void manage_login(management* m)//登录系统
{
	unsigned long long number = 0;
	char passward[16] = { 0 };
	int loginCnt = 0;
	bool ret = false;
	do
	{
		printf("\033[3m\033[1m账号>>");
		scanf_s("%llu", &number);
		getchar();
		printf("\033[3m\033[1m密码>>\033[8m");//隐藏模式
		gets_s(passward, 16);
		fflush(stdin);
		ret = userManage_login(&m->usermanage, number, passward);
		if (ret)
		{
			printf("登录成功\033[0m \n");

			break;
		}
		else
		{
			loginCnt++;
			if (loginCnt == 3)
			{
				printf("失败次数过多，将退出程序\n");
				
				exit(0);
			}
			printf("输入错误请重新输入\n");
		}
	} while (!ret);
}
void manage_operation(management* m)//系统操作
{
	int op = welcomemenu();
	if (op == 1)
	{
		manage_login(m);
	}
	else
	{
		exit(0);
	}
	
	while (1)
	{
		system("cls");
		int op = mainmenu();
		switch (op)
		{
		case 1:
			userManaopration(&m->usermanage);
			break;
		case 2:
			readermanage_operation(&m->readermanage);
			break;
		case 3:
			bookmanage_operation(&m->bookmanage);
			break;
		case 4:
			cirmanage_operation(&m->circulatemage);
			break;
		case 5:
			Quit(m);
			break;
		default:
			printf("请输入正确的功能\n");
			break;
		}
	}
}

int main()
{
	management m;
	manage_init(&m);
	manage_operation(&m);
	return 0;
}
