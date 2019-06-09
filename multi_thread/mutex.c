#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
pthread_mutex_t mutex;
int a = 0;
void pthread(void *arg)
{
	clock_t start, finish;
	double Total_time;
	start = clock();
	while (1)
	{
		pthread_mutex_lock(&mutex);
		a--;
		printf("pthread:%d\n", a);
		pthread_mutex_unlock(&mutex);
		sleep(3);
		finish = clock();
		Total_time = (double)(finish - start) / CLOCKS_PER_SEC * 10000;
		if (Total_time >= 120)
		{
			exit(0);
		}
	}
}

int main()
{
	pthread_t tid;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&tid, NULL, (void *)pthread, NULL);
	while (1)
	{
		pthread_mutex_lock(&mutex);
		a++;
		printf("main:%d\n", a);
		pthread_mutex_unlock(&mutex);
		sleep(2);
	}
	pthread_join(tid, NULL);
	pthread_mutex_destroy(&mutex);
	return 0;
}
