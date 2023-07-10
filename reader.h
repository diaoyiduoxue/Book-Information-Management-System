#ifndef _READER_H_
#define _READER_H_

typedef struct Reader
{
	unsigned long long readerID;  //读者号
	char readername[20];//读者姓名
	char readerworkplace[30];//工作单位
	char readertel[15];//联系方式
	int canborrowcnt;//可借书数
	int yetborrowcnt;//已经借书数
}Reader;
Reader* createmptyreader();
void printreader(Reader* reader);


#endif
