/***************************************LS PROGRAM************************************************/
/*NAME   :SAURAV RAI
  REG NO :15012 
  CLASS  :II MSc MATHS
*/
#include<stdio.h>
#include "apue.h"
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>
#include<unistd.h> // for the use of getopt 
#include<time.h>   //for time
#include <pwd.h>   //This is for changing uid and gid into names
#include <grp.h>
#include <ctype.h>


#define MAXSIZE 250

//PROTOTYPE OF ALL THE FUNCTIONS USED CODE:
 char *userNameFromId(uid_t uid);
 char *   groupNameFromId(gid_t gid);
 static void list_dir (const char * dir_name);
 void show_dir_content(char * path);

//THIS IS THE MAIN PROGRAM: 
 int main(int argc, char *argv[])
  {
   char fullpath[100]; //To get the current working directory:
      if(getcwd(fullpath ,sizeof(fullpath))!=NULL)
       {
         
       } 
       else
       {
        exit(1);
       }
   unsigned mtime,ctim;     //Declaring all the variables 
   int arrayIndex=0,i;
   char time[25];       
   int n, option;
   DIR *dp;
     struct dirent *dirp;   //The two strucures in the directory
     struct stat statbuf;
    char temppath[100];
   strcpy(temppath,fullpath);
                           //SETTING ALL THE FLAGS:
   int aflag=0;
   int Aflag=0;
   int iflag=0;
   int lflag=0;
   int nflag=0;
   int Rflag=0;
   int dflag=0;
   int sflag=0;
   int tflag=0;
   int cflag=0;
   int total=0;
      struct node
    {
        char filename[40];
        int m_time;
    };   
    struct node node[50];
   
     struct nod
    {
        char filename[40];
        int c_time;
    };
   struct nod nod[50];
     struct filenode
    {
      char filename[40];
     };
   struct filenode filenode[50];
  
  //FUNCTION USED TO GET MODIFICATION TIME: 
  unsigned mod_Time (char filename [])
 {
    struct stat fileStat;
    int fd=0;
    if ( ( fd = open (filename , O_RDONLY) ) == -1)
    {
        err_sys ( "open %s",filename );
        exit (1) ;
    }

    if(fstat(fd, &fileStat)<0) return 1;

        close(fd);
    return fileStat.st_mtim.tv_sec;
 }

   //FUNCTION USED TO GET LAST STATUS CHANGED TIME
    unsigned c_Time (char filename [])
 {
    struct stat fileStat;
    int fd=0;
    if ( ( fd = open (filename , O_RDONLY) ) == -1)
    {
        err_sys ( "open %s",filename );
        exit (1) ;
    }
   if(fstat(fd, &fileStat)<0) return 1;

        close(fd);
    return fileStat.st_ctim.tv_sec;
 }
   
  //FUNCTION USED FOR SORTING USING MODIFICATION TIME   
  void SortMe(struct node list[40], int s)
        {
            int i, j;
             struct node temp;

           for (i = 0; i < s - 1; i++)
            {
            for (j = 0; j < (s - 1-i); j++)
              {
               if (list[j].m_time < list[j + 1].m_time)
               {
                 temp = list[j];
                 list[j] = list[j + 1];
                 list[j + 1] = temp;
               }
            }
         } 
      }
  
 //FUNCTION USED FOR SORTING USING TIME OF LAST FILE STATUS CHANGED 
  void SortMe1(struct nod list[40], int s)
         {
              int i, j;
               struct nod temp;
  
             for (i = 0; i < s - 1; i++)
              {
              for (j = 0; j < (s - 1-i); j++)
                {
                 if (list[j].c_time < list[j + 1].c_time)
                 {
                   temp = list[j];
                   list[j] = list[j + 1];
                   list[j + 1] = temp;
                }
             }
          }
       }

 //FUNCTION USED FOR SORTING USING TIME OF LAST STATUS CHANGED 
  void sort_filename(struct filenode list[100] ,int n)
    {
      struct filenode temp;
       int i, j;
	   for (i = 0; i < n ; i++)
             {
              for (j = i+1; j < n; j++)
           {             
            if (strcmp(list[i].filename,list[j].filename) > 0)
               { 
               strcpy(temp.filename, list[j].filename);
	       strcpy(list[j].filename,list[i].filename);
               strcpy(list[i].filename,temp.filename);
               }
              }
        }   
  }
   if(strcmp(argv[1],"-ls")==0 || strcmp(argv[1],"-sl")==0)
        { 
          if((dp=opendir(fullpath))==NULL)
           err_sys("Can't open %s ", fullpath);
             while((dirp = readdir(dp))!= NULL)
              {
                if(lstat(dirp->d_name,&statbuf)<0)
                  {
                    fprintf(stderr,"cannot get stst info for %s\n",dirp->d_name);
                  }
                else
                 {
                   if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0 )
                    continue;
                //File Permissions:
                printf("%u ",(statbuf.st_blocks)/2);
                printf( (S_ISDIR(statbuf.st_mode)) ?  "d" : "-");//WE are using condtional operator
                printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
                printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
                printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
                printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
                printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
                printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
                printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
                printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
                printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");
                printf("%d ",statbuf.st_nlink);//Number of links
                printf("%s ",userNameFromId(statbuf.st_uid));//user name
                printf("%s ",groupNameFromId(statbuf.st_gid));//group name 
                printf("%d ",statbuf.st_size);//File size
                strcpy(time,ctime(&statbuf.st_mtim));
                time[strlen(time)-1]='\0';
                printf("%s ",time);//Last modification time 
                printf("%s ",dirp->d_name);//File name
                printf("\n");
                total=(statbuf.st_blocks/2)+total ;
                 }
           }
            printf("total %d\n",total);
            closedir(dp);
        }      
  //USE OF GETOPT IN BUILT FUNCTION IN THE COMMAND LINE ARGUMENT 
  else 
     if(strcmp(argv[1],"-il")==0 || strcmp(argv[1],"-li")==0)
      {
        if((dp=opendir(fullpath))==NULL)
           err_sys("Can't open %s ", fullpath);
             while((dirp = readdir(dp))!= NULL)
              {
                if(lstat(dirp->d_name,&statbuf)<0)
                  {
                    fprintf(stderr,"cannot get stst info for %s\n",dirp->d_name);
                  }
                else
                 {
                   if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0 )
                    continue;
                //File Permissions:
                printf("%u  ",statbuf.st_ino);
                printf( (S_ISDIR(statbuf.st_mode)) ?  "d" : "-");//WE are using condtional operator
                printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
                printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
                printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
                printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
                printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
                printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
                printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
                printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
                printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");
                printf("%d ",statbuf.st_nlink);//Number of links
                printf("%s ",userNameFromId(statbuf.st_uid));//user name
                printf("%s ",groupNameFromId(statbuf.st_gid));//group name 
                printf("%d ",statbuf.st_size);//File size
                strcpy(time,ctime(&statbuf.st_mtim));
                time[strlen(time)-1]='\0';
                printf("%s ",time);//Last modification time 
                printf("%s ",dirp->d_name);//File name
                printf("\n");
                total=(statbuf.st_blocks/2)+total ;
                 }
           }
            printf("total %d\n",total);
            closedir(dp);
       } 
   else
     if(strcmp(argv[1],"-tR")==0 || strcmp(argv[1],"-Rt")==0)
     {
    
      if ((dp = opendir(fullpath))==NULL)
                err_sys("can’t open %s", fullpath);
            strcpy( temppath, fullpath);
            while ((dirp = readdir(dp)) != NULL)
            {

                 if ( strcmp(dirp->d_name,".") == 0 || strcmp(dirp->d_name,"..") == 0 )
                    continue;
                mtime = mod_Time( strcat(strcat(fullpath,"/"),dirp->d_name));
                 strcpy( fullpath,temppath);
                 strcpy(node[arrayIndex].filename , dirp->d_name);
                 node[arrayIndex].m_time = mtime;
                ++arrayIndex;

            }
             SortMe( node, arrayIndex);
             // after sorting
             for( i= 0 ; i < arrayIndex ; ++i)
               printf("%s  ", node[i].filename);

                printf("\n");
                closedir(dp);
      } 
    else
       if(strcmp(argv[1],"-tc")==0 || strcmp(argv[1],"-ct")==0)
      {
        if ((dp = opendir(fullpath))==NULL)
                err_sys("can’t open %s", fullpath);
            strcpy( temppath, fullpath);
            while ((dirp = readdir(dp)) != NULL)
            {
                 if ( strcmp(dirp->d_name,".") == 0 || strcmp(dirp->d_name,"..") == 0 )
                    continue;
                ctim = c_Time( strcat(strcat(fullpath,"/"),dirp->d_name));


                 strcpy( fullpath,temppath);
                 strcpy(nod[arrayIndex].filename , dirp->d_name);
                 nod[arrayIndex].c_time = ctim;
                ++arrayIndex;

            }
             SortMe1( nod, arrayIndex);
             // after sorting
             for( i= 0 ; i < arrayIndex ; ++i)
                printf("%s  ", nod[i].filename);

                printf("\n");
                closedir(dp);
 

       }
  else {
     while((option=getopt(argc,argv,"aAilnRdstc"))!=-1)
     {
 
     switch(option)
      {
       
      case 'a':
           aflag=1; 
           if ((dp = opendir(fullpath)) == NULL)
            err_sys("can’t open %s", fullpath);
             while ((dirp = readdir(dp)) != NULL)
              {
                strcpy(filenode[arrayIndex].filename,dirp->d_name);
		++arrayIndex;
              }

             sort_filename(filenode,arrayIndex);
       
            for (i = 0; i < arrayIndex ; i++)
            { 
              printf("%s  ", filenode[i].filename);
                
            }
            printf("\n");
          
            closedir(dp);
            break;
         
        case 'A':
            Aflag=1;
            if ((dp = opendir(fullpath)) == NULL)
           err_sys("can’t open %s", fullpath);
            while ((dirp = readdir(dp)) != NULL)
             {
              if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
              continue;
              strcpy(filenode[arrayIndex].filename,dirp->d_name);
             ++arrayIndex;
             } 
     
            sort_filename(filenode,arrayIndex);
              for (i = 0; i < arrayIndex ; i++)
            {
              printf("%s  ", filenode[i].filename);
                
            }
              printf("\n");
            closedir(dp);
           break;

       case 'i':
              iflag=1;
              if((dp=opendir(fullpath))==NULL)
              err_sys("Can't open %s ", fullpath);
		while((dirp = readdir(dp)) != NULL)
                 {
                     if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0 )
                    continue;
                      if(lstat(dirp->d_name,&statbuf)<0)
                      {fprintf(stderr,"cannot get stat info for %s\n",dirp->d_name);}
                     else
                        { 
   
                            strcpy(filenode[arrayIndex].filename,dirp->d_name);
                           ++arrayIndex;
                         }
                 }
                sort_filename(filenode,arrayIndex);
              for (i = 0; i < arrayIndex ; i++)
            {
              printf("%u %s  ",statbuf.st_ino,filenode[i].filename);

            }
 
                 printf("\n");
            closedir(dp);
           break;
     
       case 's':
             sflag=1;
             if((dp=opendir(fullpath))==NULL)
              err_sys("Can't open %s ", fullpath);
                while((dirp = readdir(dp)) != NULL)
                 {
                   if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0 )
                    continue;
                     if(lstat(dirp->d_name,&statbuf)<0)
                      {fprintf(stderr,"cannot get stat info for %s\n",dirp->d_name);}
                     else
                        {
                       
                          printf("%u %s  ",(statbuf.st_blocks)/2,dirp->d_name);
          
                        }
                        total=(statbuf.st_blocks/2)+total ;  
                  }
               printf("\n");  
              printf("total %d\n",total);
           closedir(dp);
           break;
         
       case 'R':
              Rflag=1;
              printf(".:\n");
              show_dir_content(fullpath);
            break;

       case 'd':
            dflag=1;
           printf(".\n");
            break;  
   
       case 'l':
           lflag=1; 
          if((dp=opendir(fullpath))==NULL)
           err_sys("Can't open %s ", fullpath); 
             while((dirp = readdir(dp))!= NULL)
              {
                if(lstat(dirp->d_name,&statbuf)<0)
                  {
                    fprintf(stderr,"cannot get stst info for %s\n",dirp->d_name);
                  }
                else
                 {
                   if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0 )
                    continue;
                //File Permissions:
                printf( (S_ISDIR(statbuf.st_mode)) ?  "d" : "-");//WE are using condtional operator
                printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
                printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
                printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
                printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
                printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
                printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
                printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
                printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
                printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");
                printf("%d ",statbuf.st_nlink);//Number of links
                printf("%s ",userNameFromId(statbuf.st_uid));//user name
                printf("%s ",groupNameFromId(statbuf.st_gid));//group name 
                printf("%d\t ",statbuf.st_size);//File size
                strcpy(time,ctime(&statbuf.st_mtim));
                time[strlen(time)-1]='\0';
                printf("%s ",time);//Last modification time 
                printf("%s ",dirp->d_name);//File name
                printf("\n");     
                total=(statbuf.st_blocks/2)+total ;
                 }
           } 
            printf("total %d\n",total);
            closedir(dp);
            break;

       case 'n':
               nflag=1;
               if((dp=opendir(fullpath))==NULL)
             err_sys("Can't open %s ", fullpath);
             // File Permissions,directories inside this this directory,User id,Group id,File size,Last modificationtime Name of the file
             while((dirp = readdir(dp))!= NULL)
              {
                if(lstat(dirp->d_name,&statbuf)<0)
                  {
                    fprintf(stderr,"cannot get stst info for %s\n",dirp->d_name);
                  }
                else
                 {
                   if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0 )
                    continue;
                //  File Permissions: 
                printf( (S_ISDIR(statbuf.st_mode)) ?  "d" : "-");//WE are using condtional operator
                printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
                printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
                printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
                printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
                printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
                printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
                printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
                printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
                printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");
                printf("%d ",statbuf.st_nlink);//Number of links
                printf("%d ",statbuf.st_uid);//user id
                printf("%d ",statbuf.st_gid);//group id 
                printf("%d ",statbuf.st_size);//File size
                strcpy(time,ctime(&statbuf.st_mtim));
                time[strlen(time)-1]='\0';
                printf("%s ",time);//Last modification time 
                printf("%s ",dirp->d_name);//File name
                printf("\n");
                total=(statbuf.st_blocks/2)+total ;
              }
             }
            printf("total %d\n",total);
            closedir(dp);
            break;
    case 't'://sort by modification time
           tflag=1;
 
            if ((dp = opendir(fullpath))==NULL)
                err_sys("can’t open %s", fullpath);
            strcpy( temppath, fullpath);
            while ((dirp = readdir(dp)) != NULL)
            {

                 if ( strcmp(dirp->d_name,".") == 0 || strcmp(dirp->d_name,"..") == 0 )
                    continue;
                mtime = mod_Time( strcat(strcat(fullpath,"/"),dirp->d_name));
                 strcpy( fullpath,temppath);
                 strcpy(node[arrayIndex].filename , dirp->d_name);
                 node[arrayIndex].m_time = mtime;
                ++arrayIndex;

            }
             SortMe( node, arrayIndex);
             // after sorting
             for( i= 0 ; i < arrayIndex ; ++i)
               printf("%s  ", node[i].filename);

                printf("\n");
                closedir(dp);
                break;
    case 'c'://sort by time of last status changed:
            cflag=1;

            if ((dp = opendir(fullpath))==NULL)
                err_sys("can’t open %s", fullpath);
            strcpy( temppath, fullpath);
            while ((dirp = readdir(dp)) != NULL)
            {
                 if ( strcmp(dirp->d_name,".") == 0 || strcmp(dirp->d_name,"..") == 0 )
                    continue;
                ctim = c_Time( strcat(strcat(fullpath,"/"),dirp->d_name));
                  
                     
                 strcpy( fullpath,temppath);
                 strcpy(nod[arrayIndex].filename , dirp->d_name);
                 nod[arrayIndex].c_time = ctim;
                ++arrayIndex;

            }
             SortMe1( nod, arrayIndex);
             // after sorting
             for( i= 0 ; i < arrayIndex ; ++i)
                printf("%s  ", nod[i].filename);

                printf("\n");
                closedir(dp);
                break;
 
      
          default:
          printf("ERROR");
  
                    
      }
    }    
    }          
  }

   /*Return name corresponding to 'uid', or NULL on error */
                 char *userNameFromId(uid_t uid)
                   {
                   struct passwd *pwd;
                   pwd = getpwuid(uid);
                    return (pwd == NULL) ? NULL : pwd->pw_name;
                    
                     }
                
                /* Return name corresponding to 'gid', or NULL on error */
                   char *   groupNameFromId(gid_t gid)
                  {
                   struct group *grp;
                   grp = getgrgid(gid);
                     return (grp == NULL) ? NULL : grp->gr_name;
                  }
   
       void show_dir_content(char * path)
      {
           DIR * d = opendir(path); 
            if(d==NULL) return; 
             struct dirent * dir; 
                  while ((dir = readdir(d)) != NULL) // if we were able to read somehting from the directory
              {
               
              if(dir-> d_type!= DT_DIR  ) // if the type is not directory
                {  
                   printf("%s  ",dir->d_name);
                 } 
                
            else
              if(dir -> d_type == DT_DIR && strcmp(dir->d_name,"makefile")!=0  && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0)
               {
               printf("\n\n./%s:\n", dir->d_name); // print its name 
               char d_path[255]; // here I am using sprintf which is safer than strcat
               sprintf(d_path, "%s %s/",path,  dir->d_name);
               show_dir_content(d_path); // recall with the new path
              }
              
            } 
          printf("\n");
     closedir(d); // finally close the directory
   }

