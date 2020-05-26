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

void	check_argv(char **argv, int *flags)
{
	int		i;
	char	*tmp;

	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_strncmp(argv[i], "-", 1) == 0)
			set_flags(argv[i], flags);
		else
		{
			if (check_path(argv[i]) != 0)
			{
				if (!(tmp = ft_strjoin(argv[i], "/")))
					print_error(errno);
				recursive_list(tmp, flags);
				free(tmp);
			}
			else
				recursive_list(argv[i], flags);
		}
		i++;
	}
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
