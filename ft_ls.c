#include<stdio.h>
#include "./libft/libft.h"
#include "ft_ls.h"

/*void    readfunct(DIR *dir)
{
    struct stat buf;
    struct dirent *test;

    errno = 0;
    if(!(test = readdir(dir)))
    {
        if (errno != 0)
        {
            perror("");
            exit(2);
        }
        
    }
    stat(test->d_name, &buf);
   // if(test == NULL)
     //   return(0);
 //   else
    {
       if(S_ISDIR(buf.st_mode))
       {
           readfunct(dir);
        printf("directory%s\n", test->d_name);
       }
       else
       {   //  printf("directory%s\n", test->d_name);
        readfunct(dir);
        printf("%s\n", test->d_name);
       }
    }
    return(0);

}*/

int    testfunc(char *pathname)
{
    struct dirent *test;
    struct stat buf;
    char *path;
    DIR *dir;

  path = pathname;
  dir = opendir(path);
    if(!(dir))
    {
        ft_printf("ft_ls: cannot access '%s' : ", path);
        perror("");
        exit(1);
    }
    printf("jo %s\n", pathname);
    while((test = readdir(dir)) != NULL)
    {
     
     path = ft_strjoin(pathname, test->d_name); // malloc?
     ft_printf("p = %s\n", path);
      
      if(stat(path, &buf) == -1)
        {
          perror("");
          exit(1);
        }
      
      //printf("%s %d\n", test->d_name, buf.st_mode);
        
        if(S_ISDIR(buf.st_mode) && (ft_strcmp(test->d_name, ".") != 0 && ft_strcmp(test->d_name, "..") != 0))
        {
          printf("hii %s\n", test->d_name);
       path = ft_strjoin(path, "/");
          //printf("path %s\n", path);
          testfunc(path);
         
       //testfunc(test->d_name, NULL);
        }
        //else
         //ft_printf("%s\n", test->d_name);

    }
    closedir(dir);
    return (0);

}

int main(int argc, char **argv)
{
 /*struct stat buf;
    struct passwd *pws;
    stat("ls.c", &buf);
   pws = getpwuid(buf.st_uid);
   printf("%d %s\n", pws->pw_uid, ctime(&buf.st_atime));*/

 /*  DIR *dir;
   //struct dirent *sd;

    if (argc != 2)
        printf("more");
   if(!(dir = opendir(argv[1])))
   {
        ft_printf("ft_ls: cannot access '%s' : ", argv[1]);
        perror("");
   }
    else
        readfunct(dir);

  while((sd = readdir(dir)) != NULL)
   {
     printf("%s\n", sd->d_name);
   }
   */
  if (argc == 2)
  testfunc(argv[1]);
}