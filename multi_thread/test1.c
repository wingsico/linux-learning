#include<stdio.h>
#include<unistd.h>/*#包含<unistd.h>*/
#include<sys/types.h>/*#包含<sys/types.h>*/
void main() {
  int ret, i;
  for(i = 0; i < 2; i++) {
    ret = fork();
    ret = fork();
  }
 // printf("Process %d is exiting now \r\n", getpid());
  printf("Process %d is exiting now, the value of i is %d\n", getpid(), i);
}
