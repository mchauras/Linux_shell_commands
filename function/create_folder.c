#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>


int main(int argc,char *argv[],char *envp[]){

    if(argc<2){
        fprintf(stderr, "Insufficient arguments!\n");
        fprintf(stderr, "Usage: make_folder foldername\n");
        exit(1);
    }
    else{
        mkdir(argv[1],0777);
        printf("the directory is successfully created\n");
    }

    return 0;
}
