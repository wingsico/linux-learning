#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#define err -1

const char *copy_path = "file2.txt";
const char *out_path = "testfile.txt";
const int max_buffer = 1024;
const char terminator = '#';

int main() {
  int cp, out, flag;
  char s[max_buffer];
  char buf[max_buffer];
  char c;
  out = open(out_path, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
  cp = open(copy_path, O_WRONLY | O_CREAT,  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
  if (out == err || cp == err) {
    return err;
  }

  int i = 0;
  while((c = getchar()) != terminator && i < max_buffer) {
    s[i++] = c;
  }
  s[i] = '\0';
  write(out, s, i+1);
  
  close(out);

  out = open(out_path, O_RDONLY);
 
  printf("\n");

  while ((flag = read(out, buf, sizeof(buf) - 1)) > 0) {
    buf[flag] = '\0';
    printf("%s", buf);    
    write(cp, buf, flag);
  }

  close(cp);
  close(out);

  return 0;
}
