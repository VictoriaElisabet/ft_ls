#include<stdio.h>
#include "./libft/libft.h"
#include "ft_ls.h"

/*void sort_arr(t_file **arr)
{
  int i;
  int j;
  char *tmp;

  i = 0;
  j = 0;
  while(arr[i] != NULL)
  {
    j = i;
    while(arr[j + 1] != NULL)
    {
      if(ft_strcmp(arr[i], arr[j + 1]) > 0)
      {
       tmp = arr[i];
        arr[i] = arr[j + 1];
        arr[j + 1] = tmp; 
      }
      j++;
    }
    i++;
  }

}*/
t_file *set_file_struct(t_file *file, struct dirent *new)
{
    
    file->filename = new->d_name;
    return(file);
    
}

void create_arr(char *path, int count)
{
  t_file **filearr;
  struct dirent *test3;
  //struct stat buf;
  t_file file;
  DIR *dir;
  int i;

  i = 0;
  filearr = (t_file**)malloc(count * sizeof(t_file*) + 1);
  dir = opendir(path);
    if(!(dir))
    {
        ft_printf("ft_ls: cannot access '%s' : ", path);
        perror("");
        exit(1);
    }
    ft_printf("%s:\n", path);

    while((test3 = readdir(dir)) != NULL)
    {
      //printf("%s %d", test2->d_name, i);
     filearr[i] = (t_file*)malloc(sizeof(t_file));
     
     filearr[i] = set_file_struct(&file, test3);
   // ft_printf("%s %d", filearr[i]->filename, i);
      i++;
    }
    //filearr[i]= NULL;
    //sort_arr(filearr);
    i = 0;
    //ft_printf("%s ", filearr[i]->filename);
   while(filearr[i] != NULL)
   {
     ft_printf("%s %d", filearr[i]->filename, i);
      i++;
   }
   ft_printf("\n");

}
void  count_files(char *path)
{
 //char *filearr[26];
  struct dirent *test2;
  //struct stat buf;
  DIR *dir;
  int i;

  i = 0;
  dir = opendir(path);
    if(!(dir))
    {
        ft_printf("ft_ls: cannot access '%s' : ", path);
        perror("");
        exit(1);
    }
    //ft_printf("%s:\n", path);

    while((test2 = readdir(dir)) != NULL)
    {
      //printf("%s %d", test2->d_name, i);
     //filearr[i] = test2->d_name;
     //ft_printf("%s %d", filearr[i], i);
      i++;
    }
    create_arr(path, i);
    //filearr[i]= NULL;
    /*sort_arr(filearr);
    i = 0;
   while(filearr[i] != NULL)
   {
      ft_printf("%s ", filearr[i]);
      i++;
   }
   ft_printf("\n");*/




}

int    testfunc(char *basepath)
{
    struct dirent *test;
    struct stat buf;
    char *path;
    DIR *dir;

 // path = basepath;
  dir = opendir(basepath);
  
    if(!(dir))
    {
        ft_printf("ft_ls: cannot access '%s' : ", basepath);
        perror("");
        exit(1);
    }
    count_files(basepath);
    while((test = readdir(dir)) != NULL)
    {
     path = ft_strjoin(basepath, test->d_name); // malloc?
   //  ft_printf("p = %s\n", path);
      
      if(stat(path, &buf) == -1)
        {
          perror("");
          exit(1);
        }
      
      //printf("%s %d\n", test->d_name, buf.st_mode);
        
        if(S_ISDIR(buf.st_mode) && (ft_strcmp(test->d_name, ".") != 0 && ft_strcmp(test->d_name, "..") != 0))
        {
       path = ft_strjoin(path, "/");
       //ft_printf("%s\n", path);
       //create_arr(path);
          
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
void set_flag_struct(t_flags *new)
{
  new->l_flag = 0;
  new->R_flag = 0;
  new->a_flag = 0;
  new->r_flag = 0;
  new->t_flag = 0;

}

int main(int argc, char **argv)
{
  int i;
  int j;
  t_flags new;

  i = 1;
  j = 0;
  set_flag_struct(&new);
  if(argc > 1)
  {
    if(ft_strcmp(argv[0], "./ft_ls") == 0)
    {
      while(argv[i] != NULL)
      {
        if(ft_strncmp(argv[i], "-", 1) == 0)
        {
          j = 0;
          while(argv[i][j] != '\0')
          {
            if(argv[i][j] == 'l')
              new.l_flag = 1;
            if(argv[i][j] == 'R')
              new.R_flag = 1;
            if(argv[i][j] == 'r')
              new.r_flag = 1;
            if(argv[i][j] == 't')
              new.t_flag = 1;
            if(argv[i][j] == 'a')
              new.a_flag = 1;
            j++;
          }
         
        }
        
        else
        {
           ft_printf("l %d R %d r %d t %d a %d %s\n", new.l_flag, new.R_flag, new.r_flag, new.t_flag, new.a_flag, argv[i]);
          testfunc(argv[i]);
        }
        i++;
        
      }
    }
  }
}