/********************************Modified Program to avoid Race condition**************************************************/
#include<stdio.h>
#include "apue.h"
  static volatile sig_atomic_t sigflag; /* set nonzero by sig handler */
  static sigset_t newmask, oldmask, zeromask;
  static void
     sig_usr(int signo)//used for the signal function...
   {
     sigflag = 1;
   } 
static void charatatime(char *);
   int main(void)
 {
   pid_t pid;
   int status;
   TELL_WAIT();//set up things for TELL_xxx and WAIT_xxx
   if ((pid = fork()) < 0) 
   {
    err_sys("fork error");
   }
    else if (pid == 0)
     {
     WAIT_PARENT(); /* parent goes first */
     charatatime("output from child\n");
     }
     else 
     {
     charatatime("output from parent\n");
      TELL_CHILD(pid);
     }
    waitpid(pid,&status,0);//wait for child to complete 
     exit(0);
 }

 static void
   charatatime(char *str)
 {
   char *ptr;
   int c;
   setbuf(stdout, NULL);
     /* set unbuffered */
    for (ptr = str; (c = *ptr++) != 0; )
    {
    putc(c, stdout);
    //sleep(1);
    }
 }

   void TELL_WAIT(void)//TELL_WAIT FUNCTION
 {
   if (signal(SIGUSR1, sig_usr) == SIG_ERR)
     err_sys("signal(SIGUSR1) error");
   if (signal(SIGUSR2, sig_usr) == SIG_ERR)
    err_sys("signal(SIGUSR2) error");
   sigemptyset(&zeromask);
   sigemptyset(&newmask);
   sigaddset(&newmask, SIGUSR1);
   sigaddset(&newmask, SIGUSR2);
  /* Block SIGUSR1 and SIGUSR2, and save current signal mask */
   if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
     err_sys("SIG_BLOCK error");
 }

 void TELL_PARENT(pid_t pid)//TELL_PARENT FUNCTION
  {
    kill(pid, SIGUSR2);
  }

/* tell parent we’re done */

 void WAIT_PARENT(void) //WAIT_PARENT FUNCTION
  {
   while (sigflag == 0)
   sigsuspend(&zeromask);
   sigflag = 0;
   /* and wait for parent */
   /* Reset signal mask to original value */
   if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    err_sys("SIG_SETMASK error");
 }


 void  TELL_CHILD(pid_t pid)//TELL CHILD FUNCTION
 {
  kill(pid, SIGUSR1);
 }


void  WAIT_CHILD(void)//WAIT_CHILD FUNCTION
 {
  while (sigflag == 0)
  sigsuspend(&zeromask);
  sigflag = 0;
   /* and wait for child */
   /* Reset signal mask to original value */
  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
   err_sys("SIG_SETMASK error");
 }


