#include "kernel/types.h"
#include"kernel/stat.h"
#include"user/user.h"
// #include <unistd.h>
int main(int argc ,char*argv[]){
  int pipefd[2];
  int pipfd2[2];
  pipe(pipfd2);
  pipe(pipefd);
  int pid;
  pid=fork();
//   int tt=1;
  if(pid==0){
    int id1=getpid();
    close(pipfd2[1]);
    close(pipefd[0]);  // 关闭读端
    
    int ans;
    int bytes_read=read(pipfd2[0],&ans,sizeof(ans));
    if(bytes_read>0)
    printf("%d: received ping\n",ans);
    // tt=0;
    write(pipefd[1], &id1,sizeof(int));
     close(pipfd2[0]);
     close(pipefd[1]);
  }
  else{
    int id2=getpid();
    close(pipfd2[0]);
     close(pipefd[1]);  // 关闭写端
     write(pipfd2[1],&id2,sizeof(int));
     int ans;
     int  bytes_read=read(pipefd[0],&ans,sizeof(ans));
    //  while(tt);
     if(bytes_read>0)
    printf("%d: received pong\n",ans);
    close(pipfd2[1]);
    close(pipefd[0]);
  }
  exit(0);

}