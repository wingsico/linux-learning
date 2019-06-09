#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
int port = 8888;
int main() {
	int sockfd, i = 0, z;
	char buf[80], str1[80];
	struct sockaddr_in adr_server;
	FILE *fp;
	printf("打开文件......\n");
	fp = fopen("liu", "r");
	if (fp == NULL) {
		perror("打开文件失败");
		exit(1);
	}
	printf("连接服务端...\n");
	adr_server.sin_family = AF_INET;
	adr_server.sin_port = htons(port);
	adr_server.sin_addr.s_addr = htonl(INADDR_ANY);
	bzero(&(adr_server.sin_zero), 8);
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1) {
		perror("socket出错");
		exit(1);
	}
	printf("发送文件...\n");
	for (i = 0; i < 3; i++) {
		fgets(str1, 80, fp);
		printf("%d:%s", i, str1);
		sprintf(buf, "%d:%s", i, str1);
		z = sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&adr_server, sizeof(adr_server));
		if (z < 0) {
			perror("recvfrom出错");
			exit(1);
		}
	}
	printf("发送......\n");
	sprintf(buf, "stop\n");
	z = sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&adr_server, sizeof(adr_server));
	if (z < 0) {
		perror("snedto出错");
		exit(1);
	}
	fclose(fp);
	close(sockfd);
	exit(1);
}