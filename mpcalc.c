/***************SIMPLE PROGRAM SHOWING SIGNAL SIGCHLD IN MULTIPURPOSE CALCULATOR**********************/
#include "apue.h"
#include <sys/wait.h>
#include <math.h>
#include <signal.h>

static int pidArray[10], i = 0; 

static void sig_usr(int signo)
        /* argument is signal number */
 {
     printf("\n");
    switch(signo)
       {
         case SIGCHLD:
       printf("Received SIGCHLD from signal number %d:\n",signo);
       break;
         default:
       err_dump("received signal %d\n", signo);
        return;
       }
 }

void copyarray( int pidArray[], int n)
{
	int j,k = 0;
	
	for(j = 0, k = 0; j<i;)
	{
		if(j == n)
			j++;
		else
			pidArray[k++] = pidArray[j++];
	}
	i -= 1;
}

int main(void)
{
	int status;
	int a, b, c, d,j,k,count = 0;
	double result1, result2;
	char choice = 'y', option = 'y';
	pid_t pid;	/* automatic variable on the stack */
	
	while ( choice == 'y' && count < 10)
	{
		printf("Enter the value of a:");
		scanf("%d", &a);
		printf("Enter the value of b:");
		scanf("%d", &b);
		printf("Enter the value of c:");
		scanf("%d", &c);
		printf("Enter the value of d:");
		scanf("%d", &d);
		
		if ((pid = fork()) < 0)
		{
			err_sys("fork error");
		} 
		else if (pid == 0) /* child */
		{	
			result1 = pow(a,b);
			result2 = pow(c,d);
			sleep(30);
			
			if ( result1 == result2)
				exit(0);
			if ( result1 > result2)
				exit(1);
			if ( result1 < result2)
				exit(2);
		}
			//parent process:
			printf("Child's process ID: %d \n", pid);
		        pidArray[i++] = pid;
			printf("Do you want to check the status of the previous comparison?(y/n):");
			getchar();
			option = getchar();
			if(option == 'y')
			{
				for(j = 0; j < i; j++)
				{
					if ((pid = waitpid(pidArray[j], &status, WNOHANG)) < 0)
						err_sys("waitpid error");
					
					if(pid == 0)
					{
						printf("Child process with pid %d is still running.\n",pidArray[j]);
					}
					else if (WIFEXITED(status))
					{
			         printf("normal termination, exit status = %d for process %d\n", WEXITSTATUS(status), pidArray[j]);
						
							if(WEXITSTATUS(status) == 0)
								printf("Both expressions are equal for %d\n", pidArray[j]);
					else if(WEXITSTATUS(status) == 1)
						printf("Expression 1 is greater than expression 2 for process %d\n", pidArray[j]);
							else if(WEXITSTATUS(status) == 2)
							printf("Expression 1 is lesser than expression 2 for process %d\n",pidArray[j]);
							copyarray(pidArray,j);
					}
					else if (WIFSIGNALED(status))
					{
						printf("abnormal termination, signal number = %d for process %d\n", 
							   WTERMSIG(status),pidArray[j],
								#ifdef WCOREDUMP
								WCOREDUMP(status) ? " (core file generated)" : "");
						#else
						"");
					#endif
					copyarray(pidArray,j);
					}
					else if(WIFSTOPPED(status))
						printf("child stopped, signal number = %d\n",WSTOPSIG(status));
				}
			}
				
			printf("Do you wish to continue(y/n): ");
			getchar();
			choice = getchar();
			
			++count;
			printf("\n");
	}
	
	for( k = 0; k < i; k++)
	{	
		printf("Waiting for the child process %d to complete its process\n", pidArray[k]);
	         if(signal(SIGCHLD,sig_usr)==SIG_ERR)
                          {
                              err_sys("can't catch SIGCHLD\n");
                          }
                if ((pid = waitpid(pidArray[k], &status, 0)) < 0)
			err_sys("waitpid error");
		if (WIFEXITED(status))
		{
			printf("normal termination, exit status = %d for process %d\n", WEXITSTATUS(status), pidArray[k]);
			
			if(WEXITSTATUS(status) == 0)
				printf("Both expressions are equal for %d\n\n", pidArray[k]);
			else if(WEXITSTATUS(status) == 1)
				printf("Expression 1 is greater than expression 2 for process %d\n\n", pidArray[k]);
			else if(WEXITSTATUS(status) == 2)
				printf("Expression 1 is lesser than expression 2 for process %d\n\n",pidArray[k]);
		}
	}
	exit(0);
}
