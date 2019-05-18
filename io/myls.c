#include <sys/types.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <term.h>
#include <curses.h>
#include <math.h>

#define max_dirs_num 10
#define max_dirs_name_length 256
#define path_max 4096
#define file_name_max 256
#define max_usr_name 32

typedef struct ChildDir {
  char name[file_name_max];
  struct ChildDir* next;
} ChildDir;

char* dirs[max_dirs_num];
char options[4];
char all_options[4] = { 'R', 'a', 'l' };
int optc = 0;
int dirc = 0;
int l, R, a;
char r_flag;
char l_flag;

int getLongestFilenameLength(DIR*);
int getLongestGrpBit(DIR*);
int getLongestUsrBit(DIR*);
int getMaxSizeBit(DIR*);
char getFileType(mode_t);
int getPermission(mode_t, char[]);
int getDirBlocks(DIR*);
int isOpt(char*);
int isInclude(char, char*);
void handleArgv(int,char**);
void ls(char*, char*);
int getTimeStr(time_t, char[]);
int getMaxLinkBit(DIR*);
int isAbsPath(char*);
char* join(char*,char*);
void appendChildDir(ChildDir *dirs, char *name);
int getUsername(uid_t, char[]);
int getGrpname(gid_t, char[]);
int getTerminalWidth();
int getFileCount(DIR*); 

int main(int argc, char* argv[]) {
  handleArgv(argc, argv);
  for(int i = 0; i < dirc; i++) {
    ls(dirs[i], "");
  }
  
  if(!l) {
    printf("\n");
  }
}

void ls(char* path, char* parent) {
  char abs_path[path_max];
  char real_path[path_max];
  DIR * dir;
  struct dirent* ptr;
  struct stat buf;
  char perm[10];
  struct tm* ctime; 
  ChildDir* child_dir, *start;
  char username[max_usr_name];
  char grpname[max_usr_name];

  child_dir = (ChildDir *)malloc(sizeof(ChildDir));
  child_dir->next = NULL;
  if (!l) {
    printf("%c", l_flag);
    l_flag = '\n';
  } 
  if (R || dirc > 1) {
    printf("%c", r_flag);
    r_flag = '\n';
    strcpy(real_path,join(parent, path));
    if (isAbsPath(real_path)) {
      realpath(real_path, abs_path);
      printf("%s:\n", abs_path);
    } else {
      printf("%s:\n", real_path);
    }
  }
  const int time_strl = 14;
  char time_str[time_strl];
  if ((dir = opendir(path)) == NULL) {
    printf("myls: cannot access '%s': No such file or directory or permission denied. \n", path);
    exit(0);
  }

  chdir(path);
  int maxLinkBit = 0;
  int maxSizeBit = 0;
  int longestGrpBit = 0;
  int longestUsrBit = 0;
  int longestFilenameLength = getLongestFilenameLength(dir);
  int cols = (int)ceil(getTerminalWidth() / (double)(longestFilenameLength+2));
  const int strl = 50;
  char printstr[strl];
  char fileType = '-';
  char nlprintstr[10];
  int fileCount = getFileCount(dir);
  snprintf(nlprintstr, 9, "%%-%ds  ", longestFilenameLength);
  
  if (l) {
    maxSizeBit = getMaxSizeBit(dir);
    longestGrpBit = getLongestGrpBit(dir);
    longestUsrBit = getLongestUsrBit(dir);
    maxLinkBit = getMaxLinkBit(dir);
    snprintf(printstr, strl - 1, "%%c%%s %%%dld %%-%ds %%-%ds %%%dld %%s %%s\n", maxLinkBit, longestUsrBit, longestGrpBit, maxSizeBit);
    printf("total %d\n", getDirBlocks(dir));
  }
  
  int filec = 0;
  while((ptr = readdir(dir)) != NULL) {
    if (!a && (ptr->d_name[0] == '.')) {
      continue;
    }
    filec++;
    lstat(ptr->d_name, &buf);
    fileType = getFileType(buf.st_mode); 
    if (l) {
      getPermission(buf.st_mode, perm);
      getTimeStr(buf.st_mtime,time_str);
      getUsername(buf.st_uid, username);
      getGrpname(buf.st_gid, grpname);
      // "%c%s %ld %-s\t%-s %ld\next"
      printf(printstr, fileType, perm, buf.st_nlink, username, grpname, buf.st_size, time_str, ptr->d_name);
    } else {
      if (fileCount * longestFilenameLength < getTerminalWidth()) {
        printf("%s  ", ptr->d_name);
      } else {    
      printf(nlprintstr, ptr->d_name);
      }
      if (filec % (cols-1) == 0 && filec != fileCount) {
        printf("\n");
      } 
    }
    if (R) {
      if (fileType == 'd' && strcmp(ptr->d_name, "..") && strcmp(ptr->d_name, ".")) {
        appendChildDir(child_dir, ptr->d_name);  
      }
    }
  }
  for(start = child_dir->next; start != NULL; start = start->next) {
    ls(start->name, real_path);
  }

  chdir("..");
  closedir(dir);
}

void appendChildDir(ChildDir *dirs, char *name) {
  ChildDir* dir;
  ChildDir* pre;
  pre = dirs;
  while(pre->next != NULL) {
    pre = pre->next;
  }

  dir = (ChildDir *) malloc(sizeof(ChildDir));
  strcpy(dir->name,name);
  dir->next = pre->next;
  pre->next = dir;
}

char* join(char *s1, char *s2) {
  int c = 0;
  if (strlen(s1) == 0) {
    return s2;
  }
  if (s1[strlen(s1)-1] != '/') {
    c = 1;
  }
  char *result = malloc(strlen(s1)+strlen(s2)+1 + c);
  if (result == NULL) exit (1);

  strcpy(result, s1);
  if (c == 1) { 
    strcat(result, "/");
  }
  strcat(result, s2);

  return result;
}
int getTerminalWidth() {

struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}
int isAbsPath(char *path) {
  if (path[0] == '/' || path[0] == '~') {
    return 1;
  }
  return 0;
}

int getUsername(uid_t uid, char name[]) {
   struct passwd *pwd = getpwuid(uid);
    snprintf(name, max_usr_name - 1, "%d", uid);
    if (pwd != NULL) {
      strcpy(name, pwd->pw_name);
    }

}

int getGrpname(gid_t gid, char name[]) {
    struct group *grp = getgrgid(gid);
    snprintf(name, max_usr_name - 1, "%d", gid);
    if (grp != NULL) {
      strcpy(name, grp->gr_name);
    }
    return 1;
}

int getTimeStr(time_t mtime, char str[]) {
  struct tm* ctime;
  const int len = 14;
  char temp[len];
  char* mons[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}; 
  ctime = localtime(&mtime);
  snprintf(temp, len-1, "%s %2d %02d:%02d", mons[ctime->tm_mon], ctime->tm_mday, ctime->tm_hour, ctime->tm_min);
  strcpy(str, temp);
  return 1;
}
int getLongestFilenameLength(DIR* d) {
 struct dirent *de;
  struct stat buf;
  long int max = 0;

  while((de = readdir(d)) != NULL) {
    if (strlen(de->d_name) > max) {
      max = strlen(de->d_name);
    }
  }
  rewinddir(d);

  return max;
}

int getFileCount(DIR* d) {
  struct dirent *de;
  struct stat buf;
  long int count = 0;

  while((de = readdir(d)) != NULL) {
    if (!a && (de->d_name[0] == '.')) {
    continue;
    }
    count++;
  }
   rewinddir(d);

  return count;
}
int getMaxLinkBit(DIR* d) {
  struct dirent *de;
  struct stat buf;
  int count = 0;
  long int max = 0;

  while((de = readdir(d)) != NULL) {
    lstat(de->d_name, &buf);
    if (!a && (de->d_name[0] == '.')) {
      continue;
    }
    if (buf.st_nlink > max) {
      max = buf.st_nlink;
    }
  }
  rewinddir(d);

  while(max!=0) {
    max/=10;
    count++;
  }

  return count;
}

int getMaxSizeBit(DIR* d) {
  struct dirent *de;
  struct stat buf;
  int count = 0;
  long int max = 0;

  while((de = readdir(d)) != NULL) {
    lstat(de->d_name, &buf);
    if (!a && (de->d_name[0] == '.')) {
      continue;
    }
    if (buf.st_size > max) {
      max = buf.st_size;
    }
  }
  rewinddir(d);

  while(max!=0) {
    max/=10;
    count++;
  }

  return count;
}

int getLongestGrpBit(DIR* d) {
  struct dirent *de;
  struct stat buf;
  int length = 0;
  int temp = 0;
  while((de = readdir(d)) != NULL) {
    lstat(de->d_name, &buf);
    if (!a && (de->d_name[0] == '.')) {
      continue;
    }
    char name[max_usr_name];
    getGrpname(buf.st_uid, name);
    temp = strlen(name);

    if (temp > length) {
      length = temp;
    }
  }
  rewinddir(d);
  return length;
}
int getLongestUsrBit(DIR* d) {
  struct dirent *de;
  struct stat buf;
  int length = 0;
  int temp = 0;

  while((de = readdir(d)) != NULL) {
    lstat(de->d_name, &buf);
    if (!a && (de->d_name[0] == '.')) {
      continue;
    }
    char name[max_usr_name];
    getUsername(buf.st_uid, name);
    temp = strlen(name);
    if (temp > length) {
      length = temp;
    }
  }
  rewinddir(d);
  return length;
}
void handleArgv(int argc, char** argv) {
  char copt;
  for(int i = 1; i < argc; i++) {
    if (isOpt(argv[i])) {
      int j = 1;
      for(;j < strlen(argv[i]); j++) {
        copt = argv[i][j];
        if (!isInclude(copt, all_options)) {
          printf("myls: invalid option -- '%c'\n", copt);
          exit(1);
        }
        if (!isInclude(copt, options)) {
          options[optc++] = copt;
        }
      }
    } else {
      dirs[dirc++] = argv[i];
    }
  }

  if (dirc == 0) {
    dirs[dirc++] = ".";
  }

  l = isInclude('l', options);
  R = isInclude('R', options);
  a = isInclude('a', options);
}

int getDirBlocks(DIR *d) {
  struct dirent *de;
  struct stat buf;
  int exists;
  int totalSize = 0;

  for (de = readdir(d); de != NULL; de = readdir(d)) {
    lstat(de->d_name, &buf);
    if (!a && (de->d_name[0] == '.')) {
      continue;
    }
    totalSize += buf.st_blocks;

  }
  rewinddir(d);
  return totalSize/2;
}

int isOpt(char *opt) {
  int ret = opt[0] == '-' ? 1 : 0;
  return ret;
}

int isInclude(char inc, char *str) {
  int i = 0;
  while(str[i] != '\0') {
    if (inc == str[i]) return 1;
    i++;
  }
  return 0;
}

int getPermission(mode_t mode, char strPerm[]) {
  mode_t perm = S_IRUSR;
  char temp[10] = {'-','-','-',
    '-','-','-',
    '-','-','-','\0'};
  char RWX[4] = {'-','r','w','x'};
  int i;
  int j;
  for (i = 0; i < 4; i++){
    for (j = 1; j <= 3; j++){
      if ((perm & mode) != 0){
        temp[(i*3)+j-1] = RWX[j];
      }
      perm = perm >> 1;
    }
  }
  strcpy(strPerm, temp);
  return 1;
}

char getFileType(mode_t mode) {
  if(S_ISREG(mode)) return '-';
  if(S_ISDIR(mode)) return 'd';
  if(S_ISCHR(mode)) return 'c';
  if(S_ISBLK(mode)) return 'b';
  if(S_ISFIFO(mode)) return 'p';

#ifdef S_ISLNK
  if(S_ISLNK(mode)) return 'l';
#endif

#ifdef S_ISSOCK
  if(S_ISSOCK(mode)) return 's';
#endif
  return '-';
}
