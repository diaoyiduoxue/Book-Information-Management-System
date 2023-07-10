#include "reader.h"
#include"config.h"
Reader* createmptyreader()
{
	Reader* reader = calloc(1, sizeof(Reader));
	if (!reader)
	{
		printf("creat emptyuser faild\n");
		return NULL;
	}
	return reader;
    
}

void printreader(Reader* reader)
{
	printf("\033[03;01m\033[38;2;180;255;245m%-10llu %-10s %-20s %-15s \t%d\t %d\n", reader->readerID, reader->readername, reader->readerworkplace, reader->readertel, reader->canborrowcnt, reader->yetborrowcnt);
}

