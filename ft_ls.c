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

void	recursive_list(char *basepath, int *flags)
{
	t_list	*head;
	t_list	*sort;
	char	*tmp;
	char	*tmp1;

	head = NULL;
	tmp = NULL;
	tmp1 = NULL;
	create_arr(basepath, flags);
	if (*flags & RE_FLAG)
	{
		get_path_list(&head, basepath, flags, tmp1);
		(*flags & T_FLAG) ? (sort = sort_path_time_list(head, tmp)) :
			(sort = sort_path_list(head));
		if (*flags & R_FLAG)
			sort = sort_rev_path_list(head);
		while (sort != NULL)
		{
			ft_printf("\n");
			recursive_list(sort->path, flags);
			sort = sort->next;
		}
		destroy_list(head);
	}
}

int		check_path(char *path)
{
	int len;

	len = ft_strlen(path);
	if (path[len - 1] == '/')
		return (0);
	else
		return (-1);
}

void	create_argv_list(t_list **begin, char **argv, int i)
{
	DIR		*dir;
	char	*tmp;

	while (argv[i] != NULL)
	{
		if (!(dir = opendir(argv[i])))
		{
			ft_printf("ft_ls: cannot access '%s': ", argv[i]);
			perror("");
		}
		else
		{
			if (check_path(argv[i]) != 0)
			{
				if (!(tmp = ft_strjoin(argv[i], "/")))
					print_error(errno);
				push(begin, tmp);
				free(tmp);
			}
			else
				push(begin, argv[i]);
		}
		closedir(dir);
		i++;
	}
}

void	check_argv(char **argv, int *flags)
{
	int		i;
	t_list	*begin;
	t_list	*temp;

	i = 1;
	begin = NULL;
	while (argv[i] != NULL)
	{
		if (ft_strncmp(argv[i], "-", 1) == 0)
			set_flags(argv[i], flags);
		else
			break ;
		i++;
	}
	create_argv_list(&begin, argv, i);
	temp = begin;
	while (temp != NULL)
	{
		recursive_list(temp->path, flags);
		temp = temp->next;
	}
	destroy_list(begin);
}

int		main(int argc, char **argv)
{
	int flags;

	flags = 0;
	if (argc > 1)
	{
		if (ft_strcmp(argv[0], "./ft_ls") == 0)
			check_argv(argv, &flags);
	}
	else
		recursive_list("./", &flags);
}
