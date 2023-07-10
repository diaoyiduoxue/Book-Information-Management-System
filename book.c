#include "book.h"
#include"config.h"
Book* createmptybook()
{
	Book* book = calloc(1, sizeof(Book));
	if (!book)
	{
		printf("creat emptyuser faild\n");
		return NULL;
	}
	return book;
    
}

void printbook(Book* book)
{
	printf("\033[38;2;180;255;245m%-8llu %-5llu %-10s %-10s %-10s %-5d %-6d \033[0m\n",book->recordNO,book->bookNO, book->name, book->author, book->press, book->bookcnt, book->borrowcnt);
}
