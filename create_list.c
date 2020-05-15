/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

void	get_path_list(t_list **head, char *basepath, t_flags *new)
{
	DIR				*dir;
	struct dirent	*list;
	struct stat		buf;
	char			*tmp;
	char			*path;

	if (!(dir = opendir(basepath)))
	{
		ft_printf("ft_ls: cannot access '%s' : ", basepath);
		print_error(errno);
	}
	while ((list = readdir(dir)) != NULL)
	{
		if (!(path = ft_strjoin(basepath, list->d_name)))
			print_error(errno);
		if (stat(path, &buf) == -1)
			print_error(errno);
		if ((S_ISDIR(buf.st_mode) && ft_strcmp(list->d_name, ".") != 0 &&
			ft_strcmp(list->d_name, "..") != 0 && list->d_name[0] != '.') || (new->a_flag == 1 && S_ISDIR(buf.st_mode) && ft_strcmp(list->d_name, ".") != 0 &&
			ft_strcmp(list->d_name, "..") != 0 && list->d_name[0] == '.'))
		{
			if (!(tmp = ft_strjoin(path, "/")))
				print_error(errno);
			push(head, tmp);
			free(tmp);
		}
		free(path);
	}
	//if readdir e NULL å errno e int noll så exit me error men i vilket skede ska errno sättas till noll.
	if (closedir(dir) == -1)
		print_error(errno);
}

void	push(t_list **head, char *path)
{
	t_list *temp;

	if (!(temp = (t_list*)malloc(sizeof(t_list))))
		print_error(errno);
	if (!(temp->path = ft_strdup(path)))
		print_error(errno);
	temp->next = *head;
	*head = temp;
}

void	destroy_list(t_list *head)
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

/*t_list *ft_create_elem(char *path)
{
    t_list *temp;

    //ft_printf("pat %s\n", path);
	temp = (t_list*)malloc(sizeof(t_list));
	temp->path = path;
	temp->next = NULL;
	return (temp);
}*/

/*void append(t_list *head, char *path)
{
    t_list *cursor;
	t_list *new;

	cursor = head;
	while (cursor->next != NULL)
    {
		cursor = cursor->next;
    }
	new = ft_create_elem(path);
	cursor->next = new;
}

t_list   *create_path_list(t_list **head, char *path)
{

    if (!*head)
    {
		*head = ft_create_elem(path);
    }
	//else
    //{
		append(*head, path);
    //}
   // print_list(*head);
    return(*head);
    //ft_printf("%s\n", path);

}

void print_list(t_list *head) 
{
    t_list *current;
    
    current = head;
	ft_printf("hii");
    while (current != NULL) 
    {
        ft_printf("path %s\n", current->path);
        current = current->next;
    }
}*/
