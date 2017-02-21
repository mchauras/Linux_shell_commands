#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>


int main(int argc,char *argv[]){

    char str[2],filename[120];;

    if(argc==1){
        fprintf(stderr, "No input files\n");
        fprintf(stderr, "Usage: erase [-s] file\n");
        exit(1);
    }

    if((strcmp("-s",argv[1])==0)){
        strcpy(filename,argv[2]) ;
    }
    else{
        strcpy(filename,argv[1]);
        printf("\nDelete %s ?(Y/N)",argv[1]);
        gets(str);
    }

    if((toupper(*str)=='Y' )||(strcmp("-s",argv[1])==0))
      if(remove(filename))
        puts(strerror(errno));
      else
        printf("\nDelete successful!");

    return 0;
}
