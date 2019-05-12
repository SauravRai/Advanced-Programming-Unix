/******************SIMPLE PROGRAM FOR MULTI PROCESS CALCULATION**************************/
/***AUTHOR : SAURAV RAI
    REG NO : 15012
    II MSc MATHS
*********************/
#include<stdio.h>
#include "apue.h"
#include<math.h>
#include <sys/wait.h>
 int main(void)
{
   int a,b,c,d;
   int status;
   double pow1,pow2;
   pid_t pid;
   char option ='y';
   int count=1;
  /* While loop condition begins*/
  while (option=='y' && count < 11)
   { //while loop opens
   printf("Enter the values of a,b,c,d : \n");
   printf("a:");
   scanf("%d",&a);
   printf("b:");
   scanf("%d",&b);
   printf("c:");
   scanf("%d",&c);
   printf("d:");
   scanf("%d",&d);
    if ((pid = fork()) < 0) 
     {
      err_sys("fork error");
    }
   else if (pid == 0) //child
   {
       printf("COUNT :%d\n",count);
       pow1=pow(a,b);
       pow2=pow(c,d);   
      if(pow1 > pow2) 
         {
           printf("   The number %d to power %d is greater than %d to power %d \n ",a,b,c,d);
         }
       else if(pow1==pow2)
         {
          printf("   The two numbers are equal\n");
         } 
       else
        {
          printf("   The number %d to power %d is greater than %d to power %d \n ",c,d,a,b);
        }
          exit(0);
   }
   if ((pid = waitpid(pid, &status, 0)) < 0)//parent
     err_sys("waitpid error");
      count++;
   printf("  Do you wish to continue ? : 'y' or 'n':\n");
   getchar();//for flushing \n:
   option=getchar();
    }
  exit(0);
   }


