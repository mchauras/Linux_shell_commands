/*
****parser****
recieves buffer from command line
and tokenise buffer on the basis space,newline,tab
*/
#include <stdio.h>

void parser(char *buffer, char** args,size_t args_size, size_t *nargs)
{
    char *buf_args[args_size];
    char **cp;
    char *wbuf;
    size_t i, j;

    wbuf=buffer;
    buf_args[0]=buffer;
    args[0] =buffer;           //currently wbuf,buf_args[0],args[0] all points to buffer

    for(cp=buf_args; (*cp=strsep(&wbuf, " \n\t")) != NULL ;){   //strsep() tokenize buffer depending upon delimiters passed to it
        if ((*cp != '\0') && (++cp >= &buf_args[args_size]))
         break;

    }

    for (j=i=0; buf_args[i]!=NULL; i++){
        if(strlen(buf_args[i])>0)        //checks for length of each token
            args[j++]=buf_args[i];       //copies them args array
    }

    *nargs=j;             //total number of arguments
    args[j]=NULL;         //0 to j-1 valid arguments ; jth argument is marked null for execution purpose
}
