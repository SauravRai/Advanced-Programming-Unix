
/*********************************************THIS IS A SIMPLE PROGRAM FOR TELEPHONE BOOK***********************************************/
#include<stdio.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include "apue.h"
  int main()
     {
       int size,fd,l1,l2,l3,index;
       char name[20];
       char tel_num[20];
       char file_name[20];
       char another = 'y';
       printf("Enter the name of the file\n:");
       scanf("%s",file_name);
       printf("Enter the size of the file\n:");
       scanf("%d",&size);
        if( ( fd = open(file_name,O_CREAT|O_RDWR,00755) ) < 0)
          err_sys("The file is not able to open");
       if(lseek(fd,size*40,0) == -1)
         err_sys("lseek error");// A hole is created of size "size*40"
	if(write(fd,"EOF",3)!= 3)
                  err_sys("error");
      while(another=='y')
        {
          int choice;
          char buff[50];
          printf("ENTER THE FOLLOWING OPTION : \n\n\t 1.WRITE IN THE TELBOOK \n\t 2.SEARCH AND DISPLAY IN THE TELBOOK \n\t 3.DEFAULT \n");
          scanf("%d",&choice);
          if(choice>3)
            {
             printf("You have entered a wrong option\n");
            }
          switch(choice)
             {
               case 1:
		     printf("Enter the index where you want to enter your information\n");
                     scanf("%d",&index);
                      if(index > size)
                        {
                          printf("Sorry! the given index is beyond the size of the file\n");
                          exit(1); 
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
            
                    if(close(fd))
                         err_sys("The file is not closed yet\n");
                     break;
               case 2:
                     printf("Enter the index where you want to display the content of telbook\n");
                     scanf("%d",&index);
                     if(index > size)
                        {
                          printf("Sorry! the given index is beyond the size of the file\n");
                          exit(1); 
                       }
                     if( ( fd = open(file_name,O_CREAT|O_RDWR,00755) ) < 0)
                       err_sys("The file is not able to open");
                      if(lseek(fd,(index-1)*40,SEEK_SET) == -1)
                        err_sys("lseek error");
                       if(read(fd,buff,40) == -1)
                          err_sys("read error"); 
                          l3=strlen(buff)-1;
                        if(l3==0)
                         {
                           printf("There is no content to show in the telbook");
                         }
                        else
                         { 
                           printf("The name and telephone of the person in the telbook is:: %s \n ",buff);
                         }
                     break;

               case 3:
                      printf("Sorry ! You have entered a wrong option\n");
                     break;
          }
              
              printf("Do you wish to go to menu y/n \n");
              fflush(stdin);
              getchar();
              scanf("%c",&another);
        }
        
          return 0;
   }                    






	











 



 
       
       
