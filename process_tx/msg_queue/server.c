#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define IPC_KEY 0x12345678 
//下面两个宏，用于我们赋值我们传输的数据块类型
#define TYPE_S 1
#define TYPE_C 2
struct msgbuf {
  long mtype;       /* message type, must be > 0 */
  char mtext[1024];    /* message data */
};

int main()
{
  int msgid=-1;
  //ftok
  //    //key_t ftok(const char *pathname, int proj_id);
  //        //ftok通过文件的inode节点号和一个proj_id计算出一个key值
  //            //缺点：如果文件被删除，或者替换，那么将打开的不是同一个消息队列
  //
  //1.创建消息队列            
  msgid=msgget(IPC_KEY,IPC_CREAT | 0664);
  if(msgid<0){
    perror("msgget error");
    return -1;
  }
  while(1){
    //2.接收数据
    //struct msgbuf这个结构体需要我们自己定义
    struct msgbuf buf;
    //msgrcv：默认阻塞的获取数据
    //msgid:操作句柄
    //
    //buf：接收数据的结构体，自己定义
    //1024 用于指定接收的数据的最大长度，不包含mtype
    //TYPE_C 用于指定接收的数据类型
    //msgflag 0默认
    //    MSG_NOERROR 当数据长度超过指定长度，则截断数据
    msgrcv(msgid,&buf,1024,TYPE_C,0);
    printf("client say:%s",buf.mtext);
    //发送数据
    memset(&buf,0x00,sizeof(struct msgbuf));
    buf.mtype=TYPE_S;
    fgets(buf.mtext, 1024, stdin);
    msgsnd(msgid,&buf,1024,0);
  }
  msgctl(msgid,IPC_RMID,NULL);       
  return 0;
}
