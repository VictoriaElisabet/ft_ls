/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

int  count_files(char *path)
{
  struct dirent *test2;
  DIR *dir;
  int i;

  i = 0;
  dir = opendir(path);
    if(!(dir))
    {
        ft_printf("ft_ls: cannot access '%s' : ", path);
        perror("");
        exit(EXIT_FAILURE);
    }
    while((test2 = readdir(dir)) != NULL)
    {
      i++;
    }
    if(closedir(dir) == -1)
    {
      strerror(errno);
      exit(EXIT_FAILURE);
    }
    return(i);
}

void  print_files(t_file **filearr, unsigned int total, t_flags *new)
{
  int i;

  i = 0;
  if(new->l_flag == 1)
    ft_printf("total %d\n", total);
  while(filearr[i] != NULL)
   {
    if (ft_strcmp(filearr[i]->filename, ".") != 0 && ft_strcmp(filearr[i]->filename, "..") != 0)
    {
      if(new->l_flag == 1)
        ft_printf("%s %d %s %s %ld %s %s\n", filearr[i]->permissions, filearr[i]->links, filearr[i]->uid, filearr[i]->guid, filearr[i]->size, filearr[i]->time, filearr[i]->filename);
      else
        ft_printf("%s\n", filearr[i]->filename);

    }
    if (new->a_flag == 1 && (ft_strcmp(filearr[i]->filename, ".") == 0 || ft_strcmp(filearr[i]->filename, "..") == 0))
    {
      if(new->l_flag == 1)
        ft_printf("%s %d %s %s %ld %s %s\n", filearr[i]->permissions, filearr[i]->links, filearr[i]->uid, filearr[i]->guid, filearr[i]->size, filearr[i]->time, filearr[i]->filename);
      else
        ft_printf("%s\n", filearr[i]->filename);
    }
    i++;
   }
   ft_printf("\n");
}

int check_path(char *path)
{
  int len;

  len = ft_strlen(path);
  if(path[len - 1] == '/')
    return(0);
  else
    return(-1);
}

void    testfunc(char *basepath, t_flags *new)
{
  t_list *head;
  t_list *sort;

  head = NULL; 
  create_arr(basepath, new);
  if(new->R_flag == 1)
  {
    get_path_list(&head, basepath);
  //sort = sort_path_list(head);
  //måste också had ifall listan ska sort enlig mod date eller enligt rev date. kan använda stat på pathen för att få mod time 
  if(new->t_flag == 1)
    sort = sort_path_time_list(head);
  else
    sort = sort_path_list(head);
  if(new->r_flag == 1)
    sort = sort_rev_path_list(head);
  while(sort != NULL)
  {
    testfunc(sort->path, new);
    sort = sort->next;
  }
  destroy_list(head);
  }
}

int main(int argc, char **argv)
{
  int i;
  int j;
  t_flags new;
  char* tmp;

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
          j = 1;
          while(argv[i][j] != '\0')
          {
            if(argv[i][j] == 'l')
              new.l_flag = 1;
            else if(argv[i][j] == 'R')
              new.R_flag = 1;
            else if(argv[i][j] == 'r')
              new.r_flag = 1;
            else if(argv[i][j] == 't')
              new.t_flag = 1;
            else if(argv[i][j] == 'a')
              new.a_flag = 1;
            else
              break ;
            j++;
          }
          ft_printf("l %d R %d r %d t %d a %d %s\n", new.l_flag, new.R_flag, new.r_flag, new.t_flag, new.a_flag, argv[i]);
         
        }
        else
        {
           
           if(check_path(argv[i]) != 0)
           {
              if(!(tmp = ft_strjoin(argv[i], "/")))
              {
                strerror(errno);
                exit(EXIT_FAILURE);
              }
             testfunc(tmp, &new);
             free(tmp);
           }
           else
            testfunc(argv[i], &new);
        }
        i++;
        
      }
    }
  }
}