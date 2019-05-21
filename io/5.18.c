#include <stdio.h>
#include <time.h>
#include <linux/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
char *wday[] = {"日", "一", "二", "三", "四", "五", "六"};
void list (char *name, int suojin) {
	DIR *dirname;
	struct dirent *content;
	struct stat sb;
	struct tm *ctime;
	int i;
	if ((dirname = opendir(name)) == NULL) {
		printf("该目录不存在\n");
		return;
	}
	chdir(name);
	while ((content = readdir(dirname)) != NULL) {
		for (i = 0; i < suojin; i++) {
			putchar('\t');
		}
		if (content->d_type == 4) {
			printf("目录\t");
		} else if (content->d_type == 8) {
			printf("文件\t");
		} else {
			printf("其他\t");
		}
		stat(content->d_name, &sb);
		ctime = gmtime(&sb.st_mtime);
		printf("%d年%d月%d日 星期%s %d:%d:%d\t", ctime->tm_year + 1900, 1 + ctime->tm_mon, ctime->tm_mday, wday[ctime->tm_wday], ctime->tm_hour, ctime->tm_min, ctime->tm_sec);
		printf("%ld\t", sb.st_size);
		printf("%s\n", content->d_name);
		if (content->d_type == 4 && strcmp(content->d_name, "..") && strcmp(content->d_name, ".")) {
			list(content->d_name, suojin + 1);
		}
	}
	closedir(dirname);
	chdir("..");
}

int main(int argc, char *argv[]) {
	char name[256];
	printf("类型\t最后修改时间\t\t\t大小\t文件名\n");
	printf("******************************************************\n");
	if (argc == 1) {
		printf("Enter directory name:");
		scanf("%s", name);
		list(name, 0);
	} else {
		list(argv[1], 0);
	}
}
