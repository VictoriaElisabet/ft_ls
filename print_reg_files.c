/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_reg_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/08/11 11:32:07 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

void	print_reg_list(t_file **filearr, int *flags)
{
	int i;
	int size[4];

	i = 0;
	set_maxlen(filearr, size, flags);
	while (filearr[i] != NULL)
	{
		print_list(filearr[i], size);
		i++;
	}
}

void	create_reg_arr(t_file **filearr, t_list *sort, int *flags)
{
	struct stat	buf;
	int			i;

	i = 0;
	while (sort != NULL)
	{
		if (lstat(sort->path, &buf) == -1)
		{
			ft_printf("ft_ls: cannot access '%s': ", sort->path);
			perror("");
		}
		if (!(filearr[i] = (t_file*)malloc(sizeof(t_file))))
			print_error(errno);
		set_file_struct(filearr[i], sort->path, &buf, sort->path);
		sort = sort->next;
		i++;
	}
	print_reg_list(filearr, flags);
	destroy_filearr(filearr);
}

int		count_reg_files(t_list *reg_files)
{
	int i;

	i = 0;
	while (reg_files != NULL)
	{
		i++;
		reg_files = reg_files->next;
	}
	return (i);
}

void	print_reg_files(t_list *reg_files, int *flags)
{
	t_list		*sort;
	char		*tmp;
	t_file		**filearr;

	tmp = NULL;
	(*flags & T_FLAG) ? (sort = sort_path_time_list(reg_files, tmp)) :
		(sort = sort_path_list(reg_files));
	if (*flags & R_FLAG)
		sort = sort_rev_path_list(reg_files);
	if (*flags & L_FLAG)
	{
		if (!(filearr = (t_file**)
		malloc(count_reg_files(sort) * sizeof(t_file*) + 1)))
			print_error(errno);
		create_reg_arr(filearr, sort, flags);
	}
	else
	{
		while (sort != NULL)
		{
			ft_printf("%s\n", sort->path);
			sort = sort->next;
		}
	}
}
