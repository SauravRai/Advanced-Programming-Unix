/*************************************This is a simple program to show the implementation of logfile**************************************/
#include<stdio.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include"apue.h"
  int main(int argc,char *argv[])
     {
       int size,fd,fd1,l1,l2,l3,index;
       char name[20];
       char tel_num[20];
       char another = 'y';
       if(argc !=2)
        err_quit("a single argument(the directory name is required");
       if((fd=open(argv[1],O_CREAT|O_RDWR,0666) )<0) 
          err_sys("can't open %s ",argv[1]);
       printf("Enter the size of the file\n:");
       scanf("%d",&size);
	 if(lseek(fd,size*40,SEEK_SET) == -1)
          err_sys("A lseek error");// A hole is created of size "size*40"
         if(write(fd,"EOF",3)!= 3)
                  err_sys("error");
       if (( fd1 = open("logfile.txt",O_RDWR|O_CREAT,0666)) < 0)
          err_sys("The file is not able to open");
      
        time_t rawtime;
        struct tm * timeinfo;

     while(another=='y')
        {
          int choice;
          char buff[50];
          char entry[100] =" ";
          printf("ENTER THE FOLLOWING OPTION : \n\n\t 1.WRITE IN THE TELBOOK \n\t 2.SEARCH IN THE TELBOOK \n\t 3.DEFAULT \n\t 4.EXIT \n");
          scanf("%d",&choice);
          if(choice>4)
            {
             printf("You have entered a wrong option\n");
            }
          switch(choice)
             {
               case 1://WRITE IN THE TELBOOK
		     printf("Enter the index where you want to enter your information\n");
                     scanf("%d",&index);
                      if(index > size)
                        {
                          printf("Sorry! the given index is beyond the size of the file\n");
                          exit(4); 
                       }
                     if(lseek(fd,(index-1)*40,0) == -1)
         	      err_sys("lseek error");
                     printf("Enter the name of a person\n");
                     scanf("%s",name);
                     l1=strlen(name)-1;
                      while(l1++<20)
                        {
                          name[l1]=' ';
                 
                        }
                   if(write(fd,name,20)!=20)
                      err_sys("error");
                     printf("Enter the telephone number\n");
                     scanf("%s",tel_num);
                     l2=strlen(tel_num)-1;
                      while(l2++<20)
                        {
                          name[l2]=' ';
                 
                        }
                      if(write(fd,tel_num,20)!=20)
                      err_sys("error");
           
                     if (( fd1 = open("logfile.txt",O_RDWR|O_APPEND,0666)) < 0)
                     err_sys("The file is not able to open");
                     time(&rawtime);
                     timeinfo = localtime(&rawtime);
                     strcat(entry,argv[1]);
                     strcat(entry," WRITE ON ");
                     strcat(entry,asctime(timeinfo));
                     write(fd1,entry,strlen(entry));
                     write(fd1,"\n",1);
                     break;
               case 2://READ IN THE TELBOOK
                     printf("Enter the index where you want to display the content of telbook\n");
                     scanf("%d",&index);
                  
                     if(index > size)
                        {
                          printf("INDEX BEYOND THE SIZE OF THE FILE OR WRONG INPUT\n");
                          exit(1); 
                       }
                     if( ( fd = open(argv[1],O_CREAT|O_RDWR,0755) ) < 0)
                       err_sys("The file is not able to open");
                      if(lseek(fd,(index-1)*40,SEEK_SET) == -1)
                        err_sys("lseek error");
                       if(read(fd,buff,40) == -1)
                          err_sys("read error"); 
                          l3=strlen(buff);
                        if(l3==0)
                         {
                           printf("There is no content to show in the telbook\n");
                         }
                        else
                         { 
                           printf("The name and telephone of the person in the telbook is:: %s \n ",buff);
                         }
                       if (( fd1 = open("logfile.txt",O_RDWR|O_APPEND,0666)) < 0)
                         err_sys("The file is not able to open");
                     time(&rawtime);
                     timeinfo = localtime(&rawtime);
                     strcat(entry,argv[1]);
                     strcat(entry," IS READ ON ");
                     strcat(entry,asctime(timeinfo));
                     write(fd1,entry,strlen(entry));
                     write(fd1,"\n",1);
                        break;

               case 3:
                      printf("Sorry ! You have entered a wrong option\n");
                     break;
               case 4:
                      exit(1);
          }
              
              printf("\t DO YOU WISH TO MENU y/n \n");
              fflush(stdin);
              getchar();
              scanf("%c",&another);
        }
        
          return 0;
   }                    






	











 



 
       
       
