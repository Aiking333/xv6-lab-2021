

#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"
// const int N=1e3+10;
#define N 1e3

void child(int pipe_left[2]){
    close(pipe_left[1]);
    // close(pip_right[0]);
    int  ans;
    int bytes_read=read(pipe_left[0],&ans,sizeof(ans));
    if(bytes_read>0)
    printf("prime %d\n",ans);
    else{
        exit(0);
    }
    int pipe_right[2];
    pipe(pipe_right);
    if(fork()==0){
        // printf("%d",getpid());
         child(pipe_right);
    }
    else{
        // close(pipe_left[1]);
        close(pipe_right[0]);
    int tt;
    while(read(pipe_left[0],&tt,sizeof(ans))==sizeof(int)){
        // printf("%d\n",tt);
        if(tt%ans!=0){
            write(pipe_right[1],&tt,sizeof(int));
        }
    }
    
   
    close(pipe_left[0]);
    close(pipe_right[1]);
    wait((int *)0);
    exit(0);
    }
    
}
int main()
{
    // int q[1000];
    // printf("________________");
    int pipe_left[2];
    // int pip_right[2];
    pipe(pipe_left);
    // pipe(pip_right);
   int pid;
   pid=fork();
   if(pid==0){
        child(pipe_left);
   }
   else{
    close(pipe_left[0]);
    for(int i=2;i<=35;i++){
        // close(pip_right[0]);
        write(pipe_left[1],&i,sizeof(int));
    }
    close(pipe_left[1]);
    // close(pip_right[1]);
    wait(0);
   }

  exit(0);
}