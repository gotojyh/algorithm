#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "kfifo.h"
#include "list.h"

//

struct __kfifo g_ff;
typedef struct Data
{
	int id;
	char data[128];
}Data;

typedef struct DataNode
{
	Data d;
	struct list_head ptr;
}DataNode;

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
pthread_mutex_t lock;
void* register_data(void *arg)
{
	int i;
	Data d;
	while(1)
	{
		pthread_mutex_lock(&lock);
		if(__kfifo_out(&g_ff,&d,1)>0)
		{
			printf("%d\t",d.id);
			fflush(stdout);
		}
//		else 
//			sleep(1);
		pthread_mutex_unlock(&lock);
	}
	
	return 0;
}
void add_data()
{
	int i=0;
	srand(time(NULL));
	for(i=1;i<100;++i)
	{
//		sleep(rand()%3);
		Data *d=(Data*)malloc(sizeof(Data));
		d->id=i;
		sprintf(d->data,"data %d",i);
//		pthread_mutex_lock(&lock);
		__kfifo_in(&g_ff,d,1);
//		pthread_mutex_unlock(&lock);
	}
}

struct list_head g_head;
void test_list()
{
	int i=0;
	INIT_LIST_HEAD(&g_head);
	for(i=0;i<100;++i)
	{
		DataNode *n=(DataNode*)malloc(sizeof(DataNode));
		n->d.id=100-i;
		list_add(&n->ptr,&g_head);
	}
	DataNode *n1=list_first_entry(&g_head,DataNode,ptr);

	return ;
}

int main()
{
//	test_1();
//	pthread_t id;
//	pthread_mutex_init(&lock,NULL);
//
//	__kfifo_alloc(&g_ff,1024,sizeof(Data));
//	pthread_create(&id,0,register_data,0);
//	pthread_create(&id,0,register_data,0);
//	pthread_create(&id,0,register_data,0);
//	add_data();
//
//	sleep(100);
	test_list();
	
	return 0;
}
//haier
