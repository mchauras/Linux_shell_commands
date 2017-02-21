#include<stdio.h>
#include<stdlib.h>

int main(int argc ,char *argv[]){
    FILE *in ,*out;
    char ch;

    if(argc!=3){
        fprintf(stderr, "Insufficient arguments!\n");
        fprintf(stderr, "Usage: copy source_file destination_file\n");
        exit(1);
    }

    if((in=fopen(argv[1],"rb"))==NULL){
        fprintf(stderr,"Cannot open %s\n",argv[1]);
        exit(1);
    }

    if((out=fopen(argv[2],"w+b"))==NULL){
        fprintf(stderr,"Cannot open %s\n",argv[2]);
        exit(1);
    }

    while(!feof(in)){
        ch=getc(in);
        if(!feof(in))
        putc(ch,out);
    }

    fclose(in);
    fclose(out);

    return 0;
}
