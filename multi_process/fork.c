

#include <stdio.h>
#include <unistd.h>
int main()
{
  pid_t child1, child2;

  child1 = fork();
  child2 = fork();

  if (child1 == 0) {
    printf("我是子进程1\n");
    if (child2 == 0) {
      printf("66666");
    }
  }

  if (child2 == 0) {
    printf("我是子进程2\n");
    if (child1 == 0) {
      printf("ahahaha\n");
    }
  }
  return 0;
}

