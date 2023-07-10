#include "bookcircle.h"
#include"config.h"
Circulate* createmptycir()
{
	Circulate* cir = calloc(1, sizeof(Circulate));
	if (!cir)
	{
		printf("creat emptyuser faild\n");
		return NULL;
	}
    return cir;
}

void cirprint(Circulate* cir)
{
	printf("\033[03;01m\033[38;2;180;255;245m%-8llu %-8d %-10s %-10s\t %s", cir->readerNO, cir->bookNO, cir->borrowdate, cir->returndate, cir->remark);
}
