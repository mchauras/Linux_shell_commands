#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){

    FILE *fp1, *fp2, *fopen();
	int ca, cb;

    if (argc!=3){
        fprintf(stderr, "Insufficient arguments!\n");
        fprintf(stderr, "Usage: compare file1 file2\n");
        exit(1);
    }

	fp1=fopen(argv[1],"r");
	fp2=fopen(argv[2],"r") ;

	if (fp1==NULL){
        fprintf(stderr,"Cannot open %s\n",argv[1]);
		exit(1);
	}
	else if(fp2==NULL){
        fprintf(stderr,"Cannot open %s\n",argv[2]);
		exit(1);
	}
	else {
	    ca=getc( fp1 ) ;
		cb=getc( fp2 ) ;

		while(ca!=EOF && cb!=EOF && ca==cb){
			ca=getc( fp1 ) ;
			cb=getc( fp2 ) ;
		}

		if(ca==cb)
			printf("Files are identical \n");
		else if (ca!=cb)
			printf("Files differ \n");

		fclose(fp1);
		fclose(fp2);
	}

	return 0;
}
