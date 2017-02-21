/*directory listing*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>


char *curr_path()
{
    char *buf,*path;
    size_t size;
    size=pathconf(".",_PC_PATH_MAX);
    buf=(char*)malloc((size_t)size);
    path=getcwd(buf,size);
    return path;
}


int noslash(char path[])
{
    int slash_count=0;
    int path_l=strlen(path);
    for( ; path_l>=0 ; path_l--)
       if(path[path_l]== '/' ) slash_count++;
    return slash_count;
}

int main (int argc, char *argv[], char *envp[])
{
    DIR * d;
    char  dir_name[100];
    if(argv[1]==NULL)
      strcpy(dir_name,".");
    else
      strcpy(dir_name,argv[1]);


    if(!strcmp(dir_name, "~" ))
       strcpy(dir_name,getenv("HOME"));
    else if(!strcmp(dir_name, ".." )){
       strcpy(dir_name,curr_path());
       int path_l=strlen(dir_name);

       if(noslash(dir_name)==1)
          strcpy(dir_name,"/\0");
       else{
            for(;path_l>0;path_l--)
            if(dir_name[path_l]=='/'){
               dir_name[path_l]='\0';
               break;
            }
       }
    }
    else{
          //DO NOTHING
      }



    /* Open the current directory. */

    d = opendir (dir_name);

    if (! d) {
        fprintf (stderr, "Cannot open directory '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
    while (1) {
        struct dirent * entry;

        entry = readdir (d);
        if (! entry) {
            break;
        }
        printf ("%s\n", entry->d_name);
    }
    /* Close the directory. */
    if (closedir (d)) {
        fprintf (stderr, "Could not close '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }

    return 0;
}
