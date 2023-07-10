#include "user.h"
#include"config.h"

User* createmptyuser()
{
	User* user = calloc(1, sizeof(User));
	if (!user)
	{
		printf("creat emptyuser faild\n");
		return NULL;
	}
	return user;
}

void printuser(User* user)
{
	printf("\033[03;01m\033[38;2;180;255;245m%-10llu %-16s %10d\n", user->number, user->passward, user->type);
}

bool isSysad(User* user)
{
	return user->type==ut_sysadminuser;
}

bool isBookad(User* user)
{
	return user->type==ut_bookadminuser;
}

bool isComuser(User* user)
{
	return user->type==ut_commentuser;
}
