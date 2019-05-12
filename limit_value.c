#include"apue.h"
#include <errno.h>
#include <limits.h>
static void pr_sysconf(char *, int);
static void pr_pathconf(char *, char *, int);
int main(int argc, char *argv[])
 {
   if (argc != 2)
   err_quit("usage: a.out <dirname>");
   #ifdef ARG_MAX
     printf("ARG_MAX defined to be %ld\n", (long)ARG_MAX+0);
   #else
     printf("no symbol for ARG_MAX\n");
  #endif
  #ifdef _SC_ARG_MAX
     pr_sysconf("ARG_MAX =", _SC_ARG_MAX);
  #else
     printf("no symbol for _SC_ARG_MAX\n");
  #endif
 
 printf("This are the values of all the limits of SYSCONF\n "); 
 #ifdef CHILD_MAX
     printf("CHILD_MAX defined to be %ld\n", (long)CHILD_MAX+0);
   #else
     printf("no symbol for CHILD_MAX\n");
  #endif
  #ifdef _SC_CHILD_MAX
     pr_sysconf("CHILD_MAX =", _SC_CHILD_MAX);
  #else
     printf("no symbol for _SC_CHILD_MAX\n");
  #endif

#ifdef OPEN_MAX
     printf("OPEN_MAX defined to be %ld\n", (long)OPEN_MAX+0);
   #else
     printf("no symbol for OPEN_MAX\n");
  #endif
  #ifdef _SC_OPEN_MAX
     pr_sysconf("OPEN_MAX =", _SC_OPEN_MAX);
  #else
     printf("no symbol for _SC_OPEN_MAX\n");
  #endif
 #ifdef LOGIN_NAME_MAX
     printf("LOGIN_NAME_MAX defined to be %ld\n", (long)LOGIN_NAME_MAX+0);
   #else
     printf("no symbol for LOGIN_NAME_MAX\n");
  #endif
  #ifdef _SC_LOGIN_NAME_MAX
     pr_sysconf("LOGIN_NAME_MAX =", _SC_LOGIN_NAME_MAX);
  #else
     printf("no symbol for _SC_LOGIN_NAME_MAX\n");
  #endif
#ifdef CLK_TCK
     printf("Clock ticks defined to be %ld\n", (long)CLK_TCK+0);
   #else
     printf("no symbol for CLK_TCK\n");
  #endif
  #ifdef _SC_CLK_TCK
     pr_sysconf("CLK_TCK =", _SC_CLK_TCK);
  #else
     printf("no symbol for _SC_CLK_TCK\n");
  #endif
 
/* similar processing for all the rest of the sysconf symbols... */
 printf("This are the values of all  the limits of FPATHCONF and PATHCONF\n ");
 #ifdef LINK_MAX
     printf("LINK_MAX defined to be %ld\n", (long)LINK_MAX+0);
  #else
     printf("no symbol for LINK_MAX\n");
  #endif
  #ifdef LINK_MAX
    pr_pathconf("LINK_MAX =", argv[1], _PC_LINK_MAX);
  #else
    printf("no symbol for_PC_LINK_MAX\n");
  #endif
 
   #ifdef SYMLINK_MAX
     printf("SYMLINK_MAX defined to be %ld\n", (long)SYMLINK_MAX+0);
  #else
     printf("no symbol for SYMLINK_MAX\n");
  #endif
  #ifdef SYMLINK_MAX
    pr_pathconf("SYMLINK_MAX =", argv[1], _PC_SYMLINK_MAX);
  #else
    printf("no symbol for_PC_SYMLINK_MAX\n");
  #endif
 
#ifdef NAME_MAX
     printf("NAME_MAX defined to be %ld\n", (long)NAME_MAX+0);
  #else
     printf("no symbol for NAME_MAX\n");
  #endif
  #ifdef NAME_MAX
    pr_pathconf("NAME_MAX =", argv[1], _PC_NAME_MAX);
  #else
    printf("no symbol for_PC_NAME_MAX\n");
  #endif
 #ifdef PATH_MAX
     printf("PATH_MAX defined to be %ld\n", (long)PATH_MAX+0);
  #else
     printf("no symbol for PATH_MAX\n");
  #endif
  #ifdef PATH_MAX
    pr_pathconf("PATH_MAX =", argv[1], _PC_PATH_MAX);
  #else
    printf("no symbol for_PC_PATH_MAX\n");
  #endif
  
 exit(0);
 }
 static void
 pr_sysconf(char *mesg, int name)
  {
   long val;
    fputs(mesg, stdout);
    errno = 0;
   if ((val = sysconf(name)) < 0)
  
   if (errno != 0) 
     {
      if (errno == EINVAL)
      fputs(" (not supported)\n", stdout);
      else
      err_sys("sysconf error");
      }       else
       {
        fputs(" (no limit)\n", stdout);
       }
   else {
       printf(" %ld\n", val);
        }
   }
static void
pr_pathconf(char *mesg, char *path, int name)
{
  long val;
  fputs(mesg, stdout);
  errno = 0;
  if ((val = pathconf(path, name)) < 0)
   {
   if (errno != 0)
    {
  if (errno == EINVAL)
     fputs(" (not supported)\n", stdout);
  else
     err_sys("pathconf error, path = %s", path);
     }
    else
      {
       fputs(" (no limit)\n", stdout);
      }
    } else
       {
       printf(" %ld\n", val);
       }
 }
