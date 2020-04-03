#include<stdio.h>
#include "./libft/libft.h"
#include "ft_ls.h"
void  create_arr(char *path)
{
 char *filearr[sizeof(t_file)];
  struct dirent *test2;
  //struct stat buf;
  DIR *dir;
  int i;

  i = 0;
  dir = opendir(path);
  *filearr = NULL;
    if(!(dir))
    {
        ft_printf("ft_ls: cannot access '%s' : ", path);
        perror("");
        exit(1);
    }
    while((test2 = readdir(dir)) != NULL)
    {
      filearr[i] = test2->d_name;
      i++;
     //ft_printf("%s\n", test2->d_name);
    }
    filearr[i] = NULL;
    i = 0;
   while(filearr[i] != NULL)
   {
      ft_printf("%s ", filearr[i]);
      i++;
   }
   ft_printf("\n");




}

int    testfunc(char *basepath)
{
    struct dirent *test;
    struct stat buf;
    char *path;
    DIR *dir;

  path = basepath;
  dir = opendir(path);
    if(!(dir))
    {
        ft_printf("ft_ls: cannot access '%s' : ", path);
        perror("");
        exit(1);
    }
    //ft_printf("jo %s\n", pathname);
    create_arr(path);
    while((test = readdir(dir)) != NULL)
    {
     
     path = ft_strjoin(basepath, test->d_name); // malloc?
    // ft_printf("p = %s\n", path);
      
      if(stat(path, &buf) == -1)
        {
          perror("");
          exit(1);
        }
      
      //printf("%s %d\n", test->d_name, buf.st_mode);
        
        if(S_ISDIR(buf.st_mode) && (ft_strcmp(test->d_name, ".") != 0 && ft_strcmp(test->d_name, "..") != 0))
        {
         // ft_printf("hii %s\n", test->d_name);
       path = ft_strjoin(path, "/");
       //create_arr(path);
          //printf("path %s\n", path);
          testfunc(path);
         
       //testfunc(test->d_name, NULL);
        }
        //
      //  else
        // ft_printf("%s\n", test->d_name);

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