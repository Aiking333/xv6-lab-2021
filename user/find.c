#include "kernel/types.h"
#include"kernel/stat.h"
#include"user/user.h"
#include "kernel/fs.h"
// #include<stdio.h>
// #include<string.h>
void sprint( char *p,char *a ,char *b){
  // char *a=aa;
  
  while(*a!='\0'){
     *p=*a;
    p++;
    a++;
  }
  *p='/';
  p++;
  while(*b!='\0'){
    *p=*b;
    p++;
    b++;
  }
  *p='\0';
  // return p;
}
char*
fmtname(char *path)
{
  // static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  // if(strlen(p) >= DIRSIZ)
    return p;
  // memmove(buf, p, strlen(p));
  // memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  // return buf;
 
}
void find(char *path,char *ans){
  // printf("_____\n");
   char buf[512], *p;
  int fd;
  int fdd;
  struct dirent de;
  struct stat st;
  struct stat stt;
  {
    /* data */
  };
  
  
  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }
switch(st.type){
  case 2:{
    if(strcmp(fmtname(path),ans)==0)
   printf("%s",fmtname(path));
   //  printf("%s %d %d %l\n", fmtname(path), st.type, st.ino, st.size);
    break;
  }
   
  case 1:{
    // printf("__________");
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    int cnt=1;
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
       cnt++;
      if(cnt<=3) continue;
     
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf("ls: cannot stat %s\n", buf);
        continue;
      }
      if(strcmp(fmtname(buf),ans)==0){
         printf("%s/%s\n",path,fmtname(buf));
      }
      else {
          // char f[512]=path+'/'+fmtname(buf);
         
          char f[512];
        sprint(f,path,fmtname(buf));
        // char an[512]="./.";
        // char at[512]="./..";
        // if(strcmp(at,f)==0) continue;
        // if(strcmp(an,f)==0) continue;
          //  memmove(f,path,strlen(path));
          //  memmove(f,"/",1);
          //  memmove(f,fmtname(buf),strlen(fmtname(buf)));
          // printf("%s",ans);
          //  printf("%s\n",f); 
          //  sprintf(f, "%s/%s", path, fmtname(buf));
           
          fdd = open(f, 0);
        
  fstat(fdd, &stt);
   
    // fprintf(2, "ls: cannot stat %s\n", path);
    if(stt.type!=1) {
       close(fdd);
    // return;
    continue;
    }
   close(fdd);
  
          find(f,ans);
          // printf("%d\n",strcmp(fmtname(buf),ans));
          // printf("%s _____ %s\n",fmtname(buf),ans);
      }
      // printf("%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
    }
    break;
  }
}

}

int main(int argc ,char*argv[]){
  //  printf("%s\n",argv[2]);
   find(".",argv[2]);
   exit(0);
}