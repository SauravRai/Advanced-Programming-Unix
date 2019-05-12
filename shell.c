/********SIMPLE PROGRAM FOR SHOWING THE SIGINT SIGNAL IN SHELL PROGRAM
AUTHOR: SAURAV RAI
REG NO: 15012
*************************/
//VARIOUS HEADER USED:
#include  <stdio.h>
#include  <sys/types.h>
#include"apue.h"
#include<signal.h>
#include <sys/wait.h>

//PROTOTYPE DECLARATION:
void pr_exit(int status);
void prt();
static void sig_usr(int signo)
        /* argument is signal number */
 {
     printf("\n");
    switch(signo)
   {
     case SIGINT://ALL TERMINATES WHILE GIVING SIGNAL INFORMATION:
           printf("Received SIGINT from signal number %d :\n",signo);
           break;
     default:
     err_dump("received signal %d\n", signo);
     return;
   }
 }
//PARSE FUNTION:
void  parse(char *LINE, char **ARGV)
{
     while (*LINE != '\0') {        // TILL THE END OF THE LINE
          while (*LINE == ' ' || *LINE == '\t' || *LINE == '\n')
               *LINE++ = '\0';      // REPLACE IT WITH THE NULL VALUE    
          *ARGV++ = LINE;           // THE ARGUMENT POSITION IS SAVED     
          while (*LINE != '\0' && *LINE != ' ' && *LINE != '\t' && *LINE != '\n') 
               LINE++;             /* SKIP THE ARGUMENT    */
     }
     *ARGV = '\0';                 /*MARKING THE END OF ARGUMENT LIST  */
}

//THE EXECUTE FUNCTION:
void  exec(char **argv)
{
     pid_t  pid;
     int    status;

     if ((pid = fork()) < 0) 
       {     
          printf("forking child process failed\n");
          exit(1);
       }
      else if (pid == 0)
             {          //Child process: 
                 sleep(10);
               if (execvp(*argv, argv) < 0)
                 {     /* execute the command  */
                   printf("ERROR: Kindly enter proper command\n");
                   exit(1);
                 }
             }
      else
          {            // parent process
             if(signal(SIGINT,sig_usr)== SIG_ERR)
           { 
            err_sys("can't catch SIGINT\n");
           }     
            printf("THE PROCESS ID IS:%d\n",pid);  
              while (wait(&status) != pid)
               {     /* execute the command  */
                 
      
               }
         // if(signal(SIGINT,sig_usr)== SIG_ERR)
         //  { 
         //   err_sys("can't catch SIGINT\n");
         //  }     
     pr_exit(status); // Function for showing status...     
      } 
 }


   void prt()
{  
   char add[200],curr[200];
   gethostname(add,1000);     //GETTING THE USERNAME AND SYSTEM NAME
   getcwd(curr,1000);          //GETTING THE CURRENT WORKING DIRECTORY
   printf( "%s:%s/Saurav:$ ",add,curr); 
 }

//THE MAIN FUNCTION:
int  main(void)
{
     char  line[1024];             // Character array of the input line                 
     char  *argv[64];              // Character array of the command line argument      
       printf("***************WELCOME TO SAURAV'S SHELL***************\n"); 
       printf("Please enter your command:\n");  
   while (1)
       {
          // repeat until we are done 
	 // if(signal(SIGINT,sig_usr)== SIG_ERR)
         //  { 
        //    err_sys("can't catch SIGINT\n");
        //   }     
          prt();                  //CALL THE PROMPT FUNCTION:
          gets(line);
          printf("\n");
          parse(line, argv);       ///parse the line ..call the parse function
          if (strcmp(argv[0], "exit") == 0)//if it is an exit    
               exit(0);            // then exit if it is
          exec(argv);              // Otherwise execute the command 
      }
}

//ALL THE STATUS POSSIBLE
  void pr_exit(int status)
 {
  if (WIFEXITED(status))
    printf("normal termination, exit status = %d\n\n", WEXITSTATUS(status));
  else if (WIFSIGNALED(status))
    {
     printf("\nabnormal termination\n");
     printf("Received SIGINT from signal number = %d\n\n",  WTERMSIG(status));
    }  
 else if (WIFSTOPPED(status))
     printf("\nchild stopped, signal number = %d\n\n",WSTOPSIG(status));
}
