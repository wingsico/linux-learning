#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <syslog.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/stat.h>
int main() {
	pid_t child1, child2;
	int i;
	child1 = fork();
	if (child1 > 0) {
		exit(0);
	} else if (child1 < 0) {
		perror("创建子进程失败");
		exit(1);
	}
	setsid();
	chdir("/");
	umask(0);
	for (i = 0; i < NOFILE; ++i) {
		close(i);
	}
	openlog("例6-10程序信息", LOG_PID, LOG_DAEMON);
	child2 = fork();
	if (child2 == -1) {
		perror("创建子进程失败");
		exit(1);
	} else if (child2 == 0) {
		syslog(LOG_INFO, "第二子进程暂停5秒！");
		sleep(5);
		syslog(LOG_INFO, "第二子进程结束运行。");
		exit(0);
	} else {
		waitpid(child2, NULL, 0);
		syslog(LOG_INFO, "第一子进程在等待第二子进程结束后，也结束运行。");
		closelog();
		while (1) {
			sleep(10);
		}
	}
}
