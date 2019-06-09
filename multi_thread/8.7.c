#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

struct node {
	int n_number;
	struct node *n_next;
} *head = NULL;

static void cleanup_handler(void *arg) {
	printf("Clean up handler of second threead.\n");
	free(arg);
	(void)pthread_mutex_unlock(&mtx);
}

static void *thread_func(void *arg) {
	struct node *p = NULL;
	pthread_cleanup_push(cleanup_handler, p);
	
	pthread_mutex_lock(&mtx);
	while (1) {
		while (head == NULL) {
			pthread_cond_wait(&cond, &mtx);
		}
		p = head;
		head = head->n_next;
		printf("Got %d from front of queue\n", p->n_number);
		free(p);
	}
	pthread_mutex_unlock(&mtx);
	pthread_cleanup_pop(0);
	return 0;
}

int main(void) {
	pthread_t tid;
	int i;
	struct node *p;
	pthread_create(&tid, NULL, thread_func, NULL);
	for (i = 0; i < 10; i++) {
		p = (struct node*)malloc(sizeof(struct node));
		p->n_number = i;
		pthread_mutex_lock(&mtx);
		p->n_next = head;
		head = p;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mtx);
		sleep(1);
	}
	printf("thread1 wannaend the cancel thread2.\n");
	pthread_cancel(tid);
	pthread_join(tid, NULL);
	printf("Alldone--exiting\n");
	return 0;
}
