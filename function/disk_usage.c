/*disk usage*/
#include <stdio.h>
#include <sys/statvfs.h>

int main(int argc, char *argv[],char *envp[]){

 char *filename= "/home/anuj/shell_history.txt";
 struct statvfs buf;
 if(!statvfs(filename,&buf)) {
   unsigned long blksize,blocks,freeblks,disk_size,used,free;
   blksize=buf.f_bsize;
   blocks=buf.f_blocks;
   freeblks=buf.f_bfree;
   disk_size=blocks*blksize;
   free=freeblks*blksize;
   used=disk_size - free;
   printf("Disk usage: %lu bytes\t Free space: %lu bytes\n",used,free);
 }
 else {
   printf("Couldn't get file system statistics!!\n");
 }


 return 0;
}
