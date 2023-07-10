#ifndef _BOOK_H_
#define _BOOK_H_

typedef struct Book
{

	size_t recordNO;//记录号
	size_t bookNO;//书号
	char name[30];//书名
	char author[30];//作者
	char press[30];//出版社
	int bookcnt;//藏书量
	int borrowcnt;//借出数

}Book;

Book* createmptybook();
void printbook(Book* book);

#endif
