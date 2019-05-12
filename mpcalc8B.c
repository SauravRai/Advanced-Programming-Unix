//SIMPLE PROGRAM OF MULTICALCULATOR
//AUTHOR SAURAV RAI
//REG NO 15012
#include "apue.h"
#include <sys/wait.h>
#include <math.h>
#include <signal.h>

static int pidArray[10], i = 0; 

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
	int a, b, c, d, count = 0;
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
			
			printf("Child's process ID: %d \n", pid);
			pidArray[i++] = pid;
			printf("DO YOU WISH TO CHECK PREVIOUS COMPARISION? 'y' or 'n':\n");
			getchar();
			option = getchar();
			if(option == 'y')
			{
				for(int j = 0; j < i; j++)
				{
					if ((pid = waitpid(pidArray[j], &status, WNOHANG)) < 0)
						err_sys("waitpid error");
					
 		          if(pid == 0)//child
			     {
			    printf("CHILD PROCESS WITH pid %d STILL RUNNING.\n",pidArray[j]);
                             }
		          else if (WIFEXITED(status))
          	     {
			printf("NORMAL TERMINATION, EXIT STATUS = %d FOR PROCESS %d\n", WEXITSTATUS(status), pidArray[j]);
						
				if(WEXITSTATUS(status) == 0)
		                printf("a^b = c^d  FOR PROCESS %d\n", pidArray[j]);
				 else if(WEXITSTATUS(status) == 1)
			          printf("a^b > c^d FOR PROCESS  %d\n", pidArray[j]);
				else if(WEXITSTATUS(status) == 2)
				printf("a^b < c^d  FOR PROCESS  %d\n",pidArray[j]);
				 copyarray(pidArray,j);
			 	}
					else if (WIFSIGNALED(status))
					{
						printf("ABNORMAL TERMINATION, SIGNAL NUMBER = %d FOR PROCESS %d\n", 
							   WTERMSIG(status),pidArray[j],
								#ifdef WCOREDUMP
								WCOREDUMP(status) ? " (core file generated)" : "");
						#else
						"");
					#endif
					copyarray(pidArray,j);
					}
					else if(WIFSTOPPED(status))
						printf("CHILD STOPPED, SIGNAL NUMBER = %d\n",WSTOPSIG(status));
				}
			}
				
			printf("DO YOU WANT TO CONTINUE: 'y' or 'n'\n");
			getchar();
			choice = getchar();
			
			++count;
			printf("\n");
	}
	
	for(int k = 0; k < i; k++)
	{	
		printf("WAITING FOR CHILD PROCESS %d TO COMPLETE\n", pidArray[k]);
		
		if ((pid = waitpid(pidArray[k], &status, 0)) < 0)
			err_sys("waitpid error");
		if (WIFEXITED(status))
		{
			printf("NORMAL TERMINATION, EXIT STATUS = %d FOR PROCESS %d\n", WEXITSTATUS(status), pidArray[k]);
			
			if(WEXITSTATUS(status) == 0)
				printf("a^b = c^d  FOR PROCESS %d\n\n", pidArray[k]);
			else if(WEXITSTATUS(status) == 1)
				printf("a^b > c^d  FOR PROCESS %d\n\n", pidArray[k]);
			else if(WEXITSTATUS(status) == 2)
				printf("a^b < c^d  FOR PROCESS %d\n\n",pidArray[k]);
		}
	}
	exit(0);
}
