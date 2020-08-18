/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/08/14 18:03:12 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

int		pathcmp(char *hpath, char *cpath)
{
	char	*str1;
	char	*str2;

	str1 = ft_string_tolower(ft_strdup(hpath));
	str2 = ft_string_tolower(ft_strdup(cpath));
	if (ft_strcmp(str1, str2) > 0)
	{
		free(str1);
		free(str2);
		return (1);
	}
	else
	{
		free(str1);
		free(str2);
		return (0);
	}
}

int		sort_path_time(t_list *head, t_list *current, struct stat *temp1,
struct stat *temp2)
{
	if (temp1->st_mtime < temp2->st_mtime)
		return (1);
	else if (temp1->st_mtime == temp2->st_mtime)
	{
		if (temp1->st_mtim.tv_nsec < temp2->st_mtim.tv_nsec)
			return (1);
		else if (pathcmp(head->path, current->path) == 1)
			return (1);
	}
	return (0);
}

t_list	*sort_path_time_list(t_list *head, char *tmp)
{
	t_list		*begin;
	t_list		*current;
	struct stat	temp1;
	struct stat	temp2;

	begin = head;
	while (head != NULL)
	{
		current = head->next;
		while (current != NULL)
		{
			if ((stat(head->path, &temp1)) != -1 &&
			(stat(current->path, &temp2)) != -1)
				if (sort_path_time(head, current, &temp1, &temp2) == 1)
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

t_list	*sort_rev_path_list(t_list *head)
{
	t_list	*begin;
	t_list	*current;
	char	*tmp;

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

t_list	*sort_path_list(t_list *head)
{
	t_list	*begin;
	t_list	*current;
	char	*tmp;

	begin = head;
	while (head)
	{
		current = head->next;
		while (current)
		{
			if (pathcmp(head->path, current->path) == 1)
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
