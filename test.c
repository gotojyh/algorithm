#include <stdio.h>
#include "kfifo.h"

typedef struct Data
{
	int id;
	char data[128];
}Data;

void test_1()
{
	struct __kfifo ff;
	int rt,i;
	rt=__kfifo_alloc(&ff,1024,sizeof(Data));
	for(i=0;i<100;++i)
	{
		Data d;
		d.id=i;
		sprintf(d.data,"data %d",i);
		__kfifo_in(&ff,&d,1);
	}

	for(i=0;i<100;++i)
	{
		Data d;
		__kfifo_out(&ff,&d,1);
		printf("%d %s\n",d.id,d.data);
	}

	__kfifo_free(&ff);
}

int main()
{
	test_1();

	return 0;
}
