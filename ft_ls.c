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
#include <stdio.h>

void sort_arr_name(t_file **arr)
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

void sort_mod_arr_name(t_file **arr)
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

void sort_rev_arr_name(t_file **arr)
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

char *set_time(long int time)
{
  char *time_str;

  if(!(time_str = ft_strsub(ctime(&time), 4, 12)))
  {
    ft_putstr("Malloc failed or errno ENOMEM?");
    exit(1);
  }
  else
    return(time_str);

}
char *set_file_perm(struct stat *buf)
{
  char *perm_str;

  perm_str = (char*)malloc(10 * sizeof(char) + 1);
  if(S_ISDIR(buf->st_mode))
    perm_str[0] = 'd';
  else if (S_ISLNK(buf->st_mode))
    perm_str[0] = 'l';
  else
    perm_str[0] = '-';
  perm_str[1] = (buf->st_mode & S_IRUSR) ? 'r' : '-';
  perm_str[2] = (buf->st_mode & S_IWUSR) ? 'w' : '-';
  perm_str[3] = (buf->st_mode & S_IXUSR) ? 'x' : '-';
  perm_str[4] = (buf->st_mode & S_IRGRP) ? 'r' : '-';
  perm_str[5] = (buf->st_mode & S_IWGRP) ? 'w' : '-';
  perm_str[6] = (buf->st_mode & S_IXGRP) ? 'x' : '-';
  perm_str[7] = (buf->st_mode & S_IROTH) ? 'r' : '-';
  perm_str[8] = (buf->st_mode & S_IWOTH) ? 'w' : '-';
  perm_str[9] = (buf->st_mode & S_IXOTH) ? 'x' : '-';
  perm_str[10] = '\0';
  return (perm_str);

}

void set_file_struct(t_file *file, struct dirent *fileinfo, struct stat *buf)
{
    struct passwd *userid;
    struct group *groupid;
    userid = getpwuid(buf->st_uid);
    groupid = getgrgid(buf->st_gid);
    file->permissions = set_file_perm(buf);
    file->links = buf->st_nlink;
    file->uid = userid->pw_name;
    file->guid = groupid->gr_name;
    file->size = buf->st_size;
    file->time = set_time(buf->st_mtime);
    file->filename = fileinfo->d_name;
    file->mod_time = buf->st_mtime;
}

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
        exit(1);
    }
    while((test2 = readdir(dir)) != NULL)
    {
      i++;
    }
    closedir(dir);
    return(i);
}
void  print_files(t_file **filearr, t_flags *new)
{
  int i;

  i = 0;
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
void  destroy_filearr(t_file **filearr)
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

  i = 0;
  dir = opendir(path);
    if(!(dir))
    {
        ft_printf("ft_ls: cannot access '%s' : ", path);
        perror("");
        exit(1);
    }
    ft_printf("%s:\n", path);
    filearr = (t_file**)malloc(count_files(path) * sizeof(t_file*) + 1);
    while((test3 = readdir(dir)) != NULL)
    {
      tmp = ft_strjoin(path, test3->d_name);
      lstat(tmp, &buf);
      filearr[i] = (t_file*)malloc(sizeof(t_file));
      set_file_struct(filearr[i], test3, &buf);
      free(tmp);
      i++;
    }
    closedir(dir);
    filearr[i]= NULL;
    new->t_flag == 1 ? sort_mod_arr_name(filearr) : sort_arr_name(filearr);
    if(new->r_flag == 1)
      sort_rev_arr_name(filearr);
    // sort arr name måste också ha med ifall det ska sorteras enlig mod date och reverse
   // new->r_flag == 1 ? sort_rev_arr_name(filearr) : sort_arr_name(filearr);
    print_files(filearr, new);
    destroy_filearr(filearr);
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

void  get_path_list(t_list **head, char *basepath)
{
  DIR *dir;
  struct dirent *list;
  struct stat buf;
  char *tmp;
  char *path;

  dir = opendir(basepath);
  if(!(dir))
  {
    ft_printf("ft_ls: cannot access '%s' : ", basepath);
    perror("");
    exit(1);
  }
  while((list = readdir(dir)) != NULL)
  {
    path = ft_strjoin(basepath, list->d_name); 
    if(stat(path, &buf) == -1)
    {
        perror("");
        exit(1);
    }
    if(S_ISDIR(buf.st_mode) && (ft_strcmp(list->d_name, ".") != 0 && ft_strcmp(list->d_name, "..") != 0 && ft_strcmp(list->d_name, ".git") != 0))
    {
      tmp = ft_strjoin(path, "/");
      push(head, tmp);
      free(tmp);
    }
    free(path);
  }
  closedir(dir);
}

void  destroy_list(t_list *head)
{
   t_list *tmp;
   while (head != NULL)
    {
      
       tmp = head;
       head = head->next;
       free(tmp->path);
       free(tmp);
    }
}

t_list  *sort_path_list(t_list *head)
{
	t_list	*begin;
	t_list	*current;
  char *tmp;

	begin = head;
	while (head)
	{
		current = head->next;
		while (current)
		{
			if (ft_strcmp(head->path, current->path) > 0)
			{
				tmp = head->path;
        head->path = current->path;
        current->path = tmp; 
			}
			current = current->next;
		}
		head = head->next;
	}
	return (begin);
}

t_list  *sort_rev_path_list(t_list *head)
{
	t_list	*begin;
	t_list	*current;
  char *tmp;

	begin = head;
	while (head)
	{
		current = head->next;
		while (current)
		{
				tmp = head->path;
        head->path = current->path;
        current->path = tmp; 
			  current = current->next;
	  }
		head = head->next;
	}
	return (begin);
}

t_list  *sort_path_time_list(t_list *head)
{
	t_list	*begin;
	t_list	*current;
  char *tmp;
  struct stat temp1;
  struct stat temp2;

	begin = head;
	while (head)
	{
		current = head->next;
		while (current)
		{
      stat(head->path, &temp1);
      stat(current->path, &temp2);
			if (temp1.st_mtime < temp2.st_mtime)
			{
				tmp = head->path;
        head->path = current->path;
        current->path = tmp; 
			}
			current = current->next;
		}
		head = head->next;
	}
	return (begin);
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
          ft_printf("hii");
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
             tmp = ft_strjoin(argv[i], "/");
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