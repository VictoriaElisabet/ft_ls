/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filearr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

static void sort_arr_name(t_file **arr)
{
  int i;
  int j;
  t_file *tmp;

  i = 0;
  j = 0;
  while(arr[i] != NULL)
  {
    j = i;
    while(arr[j + 1] != NULL)
    {
      if(ft_strcmp(ft_string_tolower(arr[i]->filename), ft_string_tolower(arr[j + 1]->filename)) > 0)
      {
        tmp = arr[i];
        arr[i] = arr[j + 1];
        arr[j + 1] = tmp; 
      }
      j++;
    }
    i++;
  }
}

static void sort_mod_arr_name(t_file **arr)
{
  int i;
  int j;
  t_file *tmp;

  i = 0;
  j = 0;
  while(arr[i] != NULL)
  {
    j = i;
    while(arr[j + 1] != NULL)
    {
      if(arr[i]->mod_time < arr[j + 1]->mod_time)
      {
        tmp = arr[i];
        arr[i] = arr[j + 1];
        arr[j + 1] = tmp; 
      }
      j++;
    }
    i++;
  }
}

static void sort_rev_arr_name(t_file **arr)
{
  int i;
  int j;
  t_file *tmp;

  i = 0;
  j = 0;
  while(arr[i] != NULL)
  {
    j = i;
    while(arr[j + 1] != NULL)
    {
      tmp = arr[i];
      arr[i] = arr[j + 1];
      arr[j + 1] = tmp; 
      j++;
    }
    i++;
  }
}

static void  destroy_filearr(t_file **filearr)
{
  int i;

  i = 0;
  while(filearr[i] != NULL)
   {
     free(filearr[i]->time);
     free(filearr[i]->permissions);
   free(filearr[i]);
   i++;
   }
   free(filearr);
}

void create_arr(char *path, t_flags *new)
{
  t_file **filearr;
  struct dirent *test3;
  struct stat buf;
  DIR *dir;
  int i;
  char *tmp;
  unsigned int total;

  i = 0;
  total = 0;
  dir = opendir(path);
    if(!(dir))
    {
        ft_printf("ft_ls: cannot access '%s' : ", path);
        perror("");
        exit(1);
    }
    ft_printf("%s:\n", path);
    if(!(filearr = (t_file**)malloc(count_files(path) * sizeof(t_file*) + 1)))
    {
      strerror(errno);
      exit(EXIT_FAILURE);
    }
    while((test3 = readdir(dir)) != NULL)
    {
      if(!(tmp = ft_strjoin(path, test3->d_name)))
      {
        strerror(errno);
        exit(EXIT_FAILURE);
      }
      if(lstat(tmp, &buf) == -1)
      {
         strerror(errno);
        exit(EXIT_FAILURE);
      }
      if((ft_strcmp(test3->d_name, ".") != 0 && ft_strcmp(test3->d_name, "..") != 0) || 
        (new->a_flag == 1 && (ft_strcmp(test3->d_name, ".") == 0 || ft_strcmp(test3->d_name, "..") == 0)))
        total = total + buf.st_blocks;
      if(!(filearr[i] = (t_file*)malloc(sizeof(t_file))))
      {
        strerror(errno);
        exit(EXIT_FAILURE);
      }
      set_file_struct(filearr[i], test3, &buf);
      free(tmp);
      i++;
    }
    if(closedir(dir) == -1)
    {
    
         strerror(errno);
        exit(EXIT_FAILURE);
    }
    filearr[i]= NULL;
    new->t_flag == 1 ? sort_mod_arr_name(filearr) : sort_arr_name(filearr);
    if(new->r_flag == 1)
      sort_rev_arr_name(filearr);
    // sort arr name måste också ha med ifall det ska sorteras enlig mod date och reverse
   // new->r_flag == 1 ? sort_rev_arr_name(filearr) : sort_arr_name(filearr);
    print_files(filearr, total, new);
    destroy_filearr(filearr);
}

