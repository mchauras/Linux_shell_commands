/*
****change directory****
currently supports-
cd ~ changes directory to default directory
cd ..
cd full path
cd any directory in currently working directory
reports error if any
*/
#include <stdio.h>
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

void change_dir(char path[]){

   if (!strcmp(path, ".." )){
       path=curr_path();
       int path_l=strlen(path);

       if(noslash(path)==1) strcpy(path,"/\0");
       else{
           for(;path_l>0;path_l--)
           if(path[path_l]=='/'){
               path[path_l]='\0';
               break;
            }
        }
   }

   if(!strcmp(path, "~" ))
       strcpy(path,getenv("HOME"));

   if(chdir(path))
    puts(strerror(errno));

}
