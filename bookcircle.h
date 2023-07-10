#ifndef _BOOKCIRCLE_H_
#define _BOOKCIRCLE_H_
typedef struct Circulate
{
	unsigned long long readerNO;//读者ID
	int bookNO;//书籍NO
	char borrowdate[11];
	char returndate[11];
	char remark[16];
}Circulate;
Circulate* createmptycir();
void cirprint(Circulate* cir);

#endif
