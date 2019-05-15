#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
int main() {
	long int begin, sec, stop;
	struct timeval tv1, tv2;
	struct timezone tz;
	char tmp;
	begin = 0;
	stop = 0;
	sec = 0;
	system("clear");
	printf("计时器程序(单位s)\n");
	printf("输入b(begin)计时器开始计时\n");
	printf("输入w(watch)查看已经累计时间\n");
	printf("输入r(rest)重新开始计时\n");
	printf("输入s(stop)暂停计时器\n");
	printf("输入e(end)结束计时器\n");
	while(1) {
		scanf("%c", &tmp);
		if (tmp == 'b') {
			if (begin == 1 && stop == 0) {
				printf("计时器已经启动！\n");
			}
			if (begin == 0 && stop == 0) {
				printf("计时器启动\n");
				gettimeofday(&tv1, &tz);
				sec = 0;
				begin = 1;
			}
			if (stop == 1) {
				gettimeofday(&tv1, &tz);
				stop = 0;
				printf("暂停结束！\n");
			}
		}
		if (tmp == 'w') {
			if (stop == 0) {
				gettimeofday(&tv2, &tz);
				printf("已经计时%ld秒\n", sec + tv2.tv_sec - tv1.tv_sec);
			}
			if (stop == 1) {
				printf("已经计时%ld秒\n", sec);
			}
		}
		if (tmp == 's') {
			if (stop == 1) {
				printf("计时已经暂停！\n");
			}
			if (stop == 0) {
				gettimeofday(&tv2, &tz);
				sec = sec + tv2.tv_sec - tv1.tv_sec;
				printf("计时暂停，已经计时%ld秒\n", sec);
				stop = 1;
			}
		}
		if (tmp == 'r') {
			gettimeofday(&tv2, &tz);
			printf("已经计时%ld秒\n", sec + tv2.tv_sec - tv1.tv_sec);
			printf("计时器在5秒后被重置！\n");
			sleep(5);
			begin = 0;
			sec = 0;
			stop = 0;
			system("clear");
			printf("计时器程序(单位s)\n");
			printf("输入b(begin)计时器开始计时\n");
			printf("输入w(watch)查看已经累计时间\n");
			printf("输入r(rest)重新开始计时\n");
			printf("输入s(stop)暂停计时器\n");
			printf("输入e(end)结束计时器\n");
		}
		if (tmp == 'e') {
			break;
		}
	}
	return 0;
}
