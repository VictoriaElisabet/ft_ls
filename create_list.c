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

void	get_path_list(t_list **head, char *basepath, int *flags, char *tmp)
{
	DIR				*dir;
	struct dirent	*list;
	struct stat		buf;
	char			*path;

	if (!(dir = opendir(basepath)))
	{
		ft_printf("ft_ls: cannot access '%s' : ", basepath);
		print_error(errno);
	}
	while ((list = readdir(dir)) != NULL)
	{
		if (!(path = ft_strjoin(basepath, list->d_name)) ||
				lstat(path, &buf) == -1)
			print_error(errno);
		if (S_ISDIR(buf.st_mode) && check_dir(list->d_name, flags) == 1)
		{
			!(tmp = ft_strjoin(path, "/")) ? print_error(errno) :
				push(head, tmp);
			free(tmp);
		}
		free(path);
	}
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
