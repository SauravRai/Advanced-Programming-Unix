#include<stdio.h>
#include "apue.h"
 static volatile sig_atomic_t sigflag; /* set nonzero by sig handler */
static sigset_t newmask, oldmask, zeromask;
static void
sig_usr(int signo)
{
sigflag = 1;
} 
static void charatatime(char *);
   int main(void)
 {
   pid_t pid;
   TELL_WAIT();
 
  if ((pid = fork()) < 0) 
   {
    err_sys("fork error");
   }
 
  else if (pid == 0) 
    {
     charatatime("output from child\n");
     TELL_PARENT(getppid());
    }
    else
      {
      WAIT_CHILD();
     charatatime("output from parent\n");
      } 
    exit(0);
 }

  static void charatatime(char *str)
 {
  char *ptr;
  int c;
  setbuf(stdout, NULL);
   /* set unbuffered */
  for (ptr = str; (c = *ptr++) != 0; )
  putc(c, stdout);
 }

void TELL_WAIT(void)
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
void TELL_PARENT(pid_t pid)
 {
  kill(pid, SIGUSR2);
 }
/* tell parent we’re done */
void WAIT_PARENT(void)
 {
  while (sigflag == 0)
  sigsuspend(&zeromask);
  sigflag = 0;
 /* and wait for parent */
 /* Reset signal mask to original value */
 if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
  err_sys("SIG_SETMASK error");
 }
  void TELL_CHILD(pid_t pid)
 {
   kill(pid, SIGUSR1);
 }
 void WAIT_CHILD(void)
 {
  while (sigflag == 0)
  sigsuspend(&zeromask);
  sigflag = 0;
/* and wait for child */
/* Reset signal mask to original value */
  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
   err_sys("SIG_SETMASK error");
 }
