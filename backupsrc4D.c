/************SIMPLE PROGRAM WHERE FILES GETS COPIED FROM SOURCE TO DESTINATION DIRECTORY**************************/
/***************************************AUTHOR:SAURAV RAI 15012 **************************************************/
#include "apue.h"
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h>
#define BUFFSIZE    4096

void direc_rec( char source[], char destination[] );
int main(int argc, char *argv[])
   {
   
      if (argc != 3)
       err_quit("usage:./output <source> <destination>");   

      char src[100],dest[100];
      strcpy(src,argv[1]);
      strcpy(dest,argv[2]);
      direc_rec(src,dest);
       return(0);
    }



void direc_rec( char source[],char destination[] )

{  
     struct stat statbuf;
     struct dirent *dirp;
     DIR *dp;
     char *ptr;
     int n, size;
       char buf[BUFFSIZE];
        int fdin,fdout;
        char tempdest[60];
     strcpy(tempdest,destination);
       if( lstat( source, &statbuf) < 0)
          err_sys( " stat buff error ");
       if (S_ISREG(statbuf.st_mode) )
         {
            printf(" DESTINATION : %s\n",destination);
            printf(" REGULAR FILE : %s\n",source );
               if ( (fdin = open( source,O_RDWR, 00755) ) < 0)
                  err_sys("source file open  error: ");
               else printf("THE SOURCE FILE IS OPENED\n");
                    if ( (fdout = open(destination,O_CREAT|O_RDWR , 00755) ) < 0)
                       err_sys("file creat error");
                   else printf("THE DESTINATION FILE IS OPENED\n");
                      while ((size = read(fdin, buf,1)) > 0)
                       {
                        // printf(" read from file : %s",buf);
                           if (write(fdout, buf, size) != size)
                            err_sys("write error");
                       }
                return;
         }

    
     else if( S_ISDIR(statbuf.st_mode )  )
    {
          
          printf(" Directory : %s\n",source );
           n = strlen( source );
            source[n++] = '/';
            source[n] = 0;
              if ((dp = opendir(source)) == NULL)
               err_sys(" Can't open directory ");
              if ( -1 == mkdir( destination, 0777) )
               err_sys(" mkdir error ");
                while( (dirp = readdir( dp )) != NULL)
                 {
                   if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
                      continue;
                         strcat(destination,"/");
                         strcat(destination,dirp->d_name);
                         strcpy( &source[n], dirp->d_name );
                         direc_rec( source,destination );// recursive call to direc_rec
                         strcpy(destination,tempdest);
               }

            source[n-1] = 0;

        

            if (closedir(dp) < 0)

                err_ret("can’t close directory %s", source);

        return;

    }

    return;

}

        


