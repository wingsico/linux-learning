#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#define MSG_TRY "try again\n"
#define MSG_TIMEOUT "timout\n"

int main(void) {
	char buf[10];
	int fd, n, i, j;
	fd = open("/dev/tty", O_RDONLY & ~O_NONBLOCK);
	if (fd < 0) {
		perror("open /dev/btty");
		exit(1);
	}
	for(i = 0; i < 5; i++) {
		n = read(fd, buf, 10);
		if(n >= 0)
			break;
		if(errno != EAGAIN) {
			perror("read /dev/tty");
			exit(1);
		}
		sleep(6);
		write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
	}
	if (i == 5)
		write(STDOUT_FILENO, MSG_TIMEOUT, strlen(MSG_TIMEOUT));
	else
		write(STDOUT_FILENO, buf, n);
		for(i = 0; i < 5; i++) {
			for(j = 0; j <= i; j++)
				printf("%2c", '*');
			printf("\n");
		}
		close(fd);
		return 0;
}
