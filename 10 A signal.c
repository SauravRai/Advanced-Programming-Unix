/*************************SIMPLE PROGRAM FOR SIGNAL HANDLING********************************
/***AUTHOR : SAURAV RAI
    REG NO : 15012
    II MSc ****/
#include<stdio.h>
#include "apue.h"
#include<fcntl.h>
static void sig_usr(int);
char filename[50];

void removefile();
      /* one handler for both signals */
int main(int argc ,char *argv[])
{

 //strcpy(filename,argv[1]);
   FILE * fd; 
 if(argc!= 2)
  {
    printf("Please enter required number of arguments\n");
    err_quit("usage: ls directory_name");
  }
  printf("The file is successfully created\n");
  printf("The process id is %d\n",getpid());

  strcpy(filename,argv[1]);
   if((fd=fopen(filename,"w")) < 0) 
    err_sys("The file cannot be open\n");

  //6 different types which continues to execute even after being caught also
  if (signal(SIGUSR1, sig_usr) == SIG_ERR)
    {
     err_sys("can’t catch SIGUSR1\n");
    }
  if (signal(SIGUSR2, sig_usr) == SIG_ERR)
   {
    err_sys("can’t catch SIGUSR2\n");
   }
   if(signal(SIGCHLD,sig_usr)==SIG_ERR)
   {
    err_sys("can't catch SIGCHLD\n");
   }
 
   if(signal(SIGALRM,sig_usr)==SIG_ERR)
   {
    err_sys("can't catch SIGALRM\n");
   }

   if(signal(SIGCONT,sig_usr)==SIG_ERR)
   {
    err_sys("can't catch SIGCHLD\n");
   }

   if(signal(SIGPIPE,sig_usr)==SIG_ERR)
   {
    err_sys("can't catch SIGCHLD\n");
   }


  //first category:: 6 types which terminates after being caught
   if(signal(SIGINT,sig_usr)== SIG_ERR)
   {
    err_sys("can't catch SIGINT\n");
   }
  if(signal(SIGABRT,sig_usr)==SIG_ERR)
   {
     err_sys("can't catch SIGABRT\n");
   } 
  if(signal(SIGFPE,sig_usr)==SIG_ERR)
   {
     err_sys("can't catch SIGFPE\n");
   }

  if(signal(SIGQUIT,sig_usr)==SIG_ERR)
   {
     err_sys("can't catch SIGQUIT\n");
   }
  if(signal(SIGSEGV,sig_usr)==SIG_ERR)
   {
     err_sys("can't catch SIGABRT\n");
   }
  if(signal(SIGTERM,sig_usr)==SIG_ERR)
   {
     err_sys("can't catch SIGTERM\n");
   }
for ( ; ; )//infinte loop
  pause();
 return;
 }


void removefile()
  {
   if( (remove(filename)) == 0)
     printf("The file is completely removed\n ");
   else
     printf("The file is not closed yet\n");
  return;
   }
static void sig_usr(int signo)
        /* argument is signal number */
 {
     printf("\n");
    switch(signo)
   {
     case SIGUSR1://THIS SET OF SIGNALS CONTINUES AFTER BEING CAUGHT ALSO
      printf("Received SIGUSR1 from signal number %d:\n",signo);
       break;
     case SIGUSR2:
     printf("Received SIGUSR2 from signal number %d:\n",signo);
       break;
     case SIGCHLD:
       printf("Received SIGCHLD from signal number %d:\n",signo);
       break;
     case SIGALRM:
       printf("Received SIGALRM from signal number %d:\n",signo);
       break;
     case SIGCONT:
       printf("Received SIGCONT from signal number %d:\n",signo);
       break;
     case SIGPIPE:
       printf("Received SIGPIPE from signal number %d:\n",signo);
       break;
     case SIGINT://ALL TERMINATES WHILE GIVING SIGNAL INFORMATION:
      printf("Received SIGINT from signal number %d:\n",signo);
      removefile();
      exit(0);
     case SIGABRT:
       printf("Received SIGABRT from signal number %d:\n",signo);
       removefile();
       exit(0);
     case SIGFPE:
       printf("Received SIGFPE from signal number %d:\n",signo);
       removefile();
       exit(0);     
    case SIGQUIT:
       printf("Received SIGQUIT from signal number %d:\n",signo);
       removefile();
       exit(0);
    case SIGSEGV:
       printf("Received SIGSEGV from signal number %d:\n",signo);
       removefile();
       exit(0);
    case SIGTERM:
       printf("Received SIGTERM from signal number %d:\n",signo);
       removefile();
       exit(0);

   default:
     err_dump("received signal %d\n", signo);
     return;
    }
  }
