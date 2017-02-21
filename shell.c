/*
works in silent and user(interative) mode
*/

#include "parse.h"       //contains funtion defination for parser
#include "directory.h"   //contains funtion defination for changing directory [cd]
#include "com_his.h"     //contains funtion defination for saving and displaying command history
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>

#define BUFFER_SIZE 1<<16
#define ARR_SIZE 1<<16


int mode;
pid_t pid;

void handle_signal(int signo){
    kill(pid,signo);
}

void handle_signal2(int signo){
    char c;
	printf("\nAre you sure?(y/n):");
	c=getchar();
	if(c=='y'||c=='Y')
    exit(0);

}

int main(int argc, char *argv[], char *envp[]){

    mode=0;
    signal(SIGTSTP, handle_signal2);
    signal(SIGINT, handle_signal);

    if(argc==3 && !strcmp(argv[1],"silent")){   //syntax:  ./program <silent> <filename>
        fputs("\nStarting in silent mode...\n",stdout);
        mode=1;
    }
    else
    fputs("\nStarting in user mode...\n",stdout);


    char buffer[BUFFER_SIZE];  //stores input from terminal
    char tmp[BUFFER_SIZE];     //for command history
    char *args[ARR_SIZE];      //for tokenised input

    int *ret_status;           //return status for child process
    size_t no_args;            //number of arguments

    FILE *fp;

    if(mode==1){
        if((fp=fopen(argv[2],"rb"))==NULL){
            fputs(strerror(errno),stdout);   //error reporting if fopen fails
            exit(1);
        }
    }

    while(1){


        if(mode) {
            if(!feof(fp))
            fgets(buffer,80,fp);
        }
        else {
            printf("\n%s@%s$ ",getenv("LOGNAME"),curr_path());
            fgets(buffer, BUFFER_SIZE, stdin);
        }
        strcpy(tmp,buffer);
        parser(buffer, args, ARR_SIZE, &no_args);

        if (no_args==0) continue;
        if (no_args)    comm_save(tmp);
        if (!strcmp(args[0], "exit" )) exit(0);
        if (!strcmp(args[0], "cd" ) && no_args==2) { change_dir(args[1]);continue; }
        if (!strcmp(args[0], "cd" ) && no_args==1) continue;
        if (!strcmp(args[0], "history" )) { history(); continue; }

        if((pid = fork())<0){
            perror("main shell: fork");
            exit(1);
        }

        if (pid){
           if(strcmp(args[no_args-1],"&")!=0)
            {
            printf("Waiting for child (%d)\n", pid);
            waitpid(pid,ret_status,0);
            printf("Child (%d) finished\n", pid);
            }

        }
        else {

             if(no_args>=3){
               if(strcmp(args[no_args-2],"redirect")==0){

               FILE *fp=fopen(args[no_args-1],"a+");
               if(fp==NULL) perror("main: error");
               int file=open(args[no_args-1],O_APPEND | O_WRONLY);
               if(file<0){
                  perror("main shell: open failed");
               }
               if(dup2(file,1)<0){
                 perror("main shell: dup2 failed");
               }
               args[no_args-2]=NULL;
               args[no_args-1]=NULL;
             }
        }

        if( execvp(args[0], args)) {
            puts(strerror(errno));
            exit(127);
        }
    }
  }
  return 0;
}
