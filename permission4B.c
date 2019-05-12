/************* SIMPLE PROGRAM ILLUSTRATING USE OF UMASK FOR GIVING PERMISSION TO USER,GROUP AND OTHERS********/
#include "apue.h"
#include <fcntl.h>
#define RWRWRW (S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH)
int main(int argc,char *argv[]  )
{
  int fd;
    if(argc != 2)
      err_sys("Error! enter only one argument");
        umask(0);
      // Create a directory with all the permissions"read , write and execute "  
    
      if (fd=(creat(argv[1], RWRWRW) < 0))
      err_sys("creat error for file %s",argv[1]);
    exit(0);
}
