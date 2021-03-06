/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_reg_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/08/12 12:11:29 by vgrankul         ###   ########.fr       */
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
		if (lstat(sort->path, &buf) != -1)
		{
			if (!(filearr[i] = (t_file*)malloc(sizeof(t_file))))
				print_error(errno);
			set_file_struct(filearr[i], sort->path, &buf, sort->path);
		}
		else
		{
			ft_printf("ft_ls: cannot access '%s': ", sort->path);
			print_error(errno);
		}
		sort = sort->next;
		i++;
	}
	filearr[i] = NULL;
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
	sort = sort_path_list(reg_files);
	if (*flags & T_FLAG)
		sort = sort_path_time_list(reg_files, tmp);
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
