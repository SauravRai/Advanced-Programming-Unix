//PROGRAM SHOWING RACE CONDITION
#include<stdio.h>
#include "apue.h"		
 static void charatatime(char *);
   int main(void)
  {
   pid_t pid;
     if ((pid = fork()) < 0) 
    {
     err_sys("fork error");
    }
     else if (pid == 0)//child
    {
     charatatime("output from child\n");
    }
     else
     {
      charatatime("output from parent\n"); //parent
     }
   exit(0);
 }
  static void charatatime(char *str)
 {  
    char *ptr;
    int c;
    setbuf(stdout, NULL); /* set unbuffered */
     for (ptr = str; (c = *ptr++) != 0; )
   {
     putc(c, stdout);
    //sleep(1); 
    }
  }
