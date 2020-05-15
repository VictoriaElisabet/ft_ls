/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"
//lägg till swap funct
t_list	*sort_path_time_list(t_list *head)
{
	t_list		*begin;
	t_list		*current;
	char		*tmp;
	struct stat	temp1;
	struct stat	temp2;

	begin = head;
	while (head)
	{
		current = head->next;
		while (current)
		{
			if (stat(head->path, &temp1) == -1)
				print_error(errno);
			if (stat(current->path, &temp2) == -1)
				print_error(errno);
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
