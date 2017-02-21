#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){

    int c,nc,nlines;
    char filename[120];
    FILE *fp,*fopen();

    if (argc==1){
        fprintf(stderr, "No input files\n");
        fprintf(stderr, "Usage: count [-l] [-w] file\n");
        exit(1);
    }

    nlines = 0 ;
    nc = 0;

    if((strcmp("-l",argv[1])==0)||(strcmp("-w",argv[1])==0))
        strcpy(filename, argv[2]) ;
    else
        strcpy(filename, argv[1]);

    fp=fopen(filename,"r");
    if(fp==NULL){
        fprintf(stderr,"Cannot open %s\n",filename);
        exit(1);
    }

    c=getc(fp) ;
    while (c!=EOF){
        if(c=='\n')
           nlines++ ;
        nc++ ;
        c=getc(fp);
    }

    fclose( fp );

    if(strcmp(argv[1],"-w")==0)
        printf("%s: %d characters \n", filename, nc );
    else if (strcmp(argv[1],"-l")==0)
        printf("%s: %d lines \n", filename, nlines );
    else
        printf("%s: %d characters  %d lines\n", filename, nc, nlines );

    return 0;
}
