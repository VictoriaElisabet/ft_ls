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

void	recursive_list(char *basepath, t_flags *new)
{
	t_list	*head;
	t_list	*sort;
	char	*tmp;
	char	*tmp1;

	head = NULL;
	tmp = NULL;
	tmp1 = NULL;
	create_arr(basepath, new);
	if (new->rec_flag == 1)
	{
		get_path_list(&head, basepath, new, tmp1);
		if (new->t_flag == 1)
			sort = sort_path_time_list(head, tmp);
		else
			sort = sort_path_list(head);
		if (new->r_flag == 1)
			sort = sort_rev_path_list(head);
		while (sort != NULL)
		{
			recursive_list(sort->path, new);
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

void	check_argv(char **argv, t_flags *new)
{
	int		i;
	char	*tmp;

	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_strncmp(argv[i], "-", 1) == 0)
			fill_flag_struct(argv[i], new);
		else
		{
			if (check_path(argv[i]) != 0)
			{
				if (!(tmp = ft_strjoin(argv[i], "/")))
					print_error(errno);
				recursive_list(tmp, new);
				free(tmp);
			}
			else
				recursive_list(argv[i], new);
		}
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_flags new;

	set_flag_struct(&new);
	if (argc > 1)
	{
		if (ft_strcmp(argv[0], "./ft_ls") == 0)
			check_argv(argv, &new);
	}
	else
		recursive_list("./", &new);
}
