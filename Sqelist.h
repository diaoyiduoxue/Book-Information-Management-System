#ifndef _SQELIST_H_
#define _SQELIST_H_
#include"config.h"
#define SEQLIST_INIT_SIZE 10
typedef struct sqelist
{
	size_t size;
	size_t capcity;
	variant* date;

}sqelist;

//内存可能分配失败，此时为NULL
//初始化数组
#define sqelist_init(plist)\
(plist)->size=0;\
(plist)->capcity=SEQLIST_INIT_SIZE;\
(plist)->date=(variant*)malloc(((plist)->capcity)*sizeof(variant));\
if(!((plist)->date))\
{\
printf("malloc (plist)->date faild\n");\
}

#define sqelist_pushbake(plist,val)\
if((plist)->size==(plist)->capcity)\
{\
	(plist)->date=realloc((plist)->date,((plist)->capcity+10)*sizeof(variant));\
	if(!(plist)->date)\
	{\
		printf("realloc faild\n");\
	}\
	else\
	{\
		(plist)->capcity = (plist)->capcity + 10;\
		(plist)->date[(plist)->size++] = val;\
	}\
}\
else\
{\
	(plist)->date[((plist))->size++] = val;\
}

#define foreach(variable,plist)\
for(int _i=0,_cnt=0;_i<(plist)->size;_i++,_cnt=0)\
	for(variable=(plist)->date[_i];_cnt<1;_cnt++)

#define Break break;_i=999999;
