/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/08/12 18:03:04 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

int		check_path(char *path)
{
	int len;

	len = ft_strlen(path);
	if (path[len - 1] == '/')
		return (0);
	else
		return (-1);
}

int		create_argv_list(t_list **begin, char **argv, int i, int *flags)
{
	struct stat		buf;
	t_list			*reg_files;

	reg_files = NULL;
	if (argv[i] == NULL)
		push(begin, "./");
	while (argv[i] != NULL)
	{
		if (lstat(argv[i], &buf) != -1)
		{
			if (!(S_ISDIR(buf.st_mode)))
				push(&reg_files, argv[i]);
			else
				push(begin, argv[i]);
		}
		else
			ft_printf("ft_ls: cannot access '%s': %s\n", argv[i], strerror(errno));
		
		i++;
	}
	if (reg_files != NULL)
		print_reg_files(reg_files, flags);
	if (reg_files != NULL && *begin != NULL)
		ft_printf("\n");
	destroy_list(reg_files);
	return (i);
}

void	sort_argv_list(t_list *head, int *flags, int i)
{
	t_list	*sort;
	char	*tmp;

	tmp = NULL;
	(*flags & T_FLAG) ? (sort = sort_path_time_list(head, tmp)) :
		(sort = sort_path_list(head));
	if (*flags & R_FLAG)
		sort = sort_rev_path_list(head);
	while (sort != NULL)
	{
		if (*flags & RE_FLAG || i > 1)
			ft_printf("%s:\n", sort->path);
		if (check_path(sort->path) != 0)
		{
			if (!(tmp = ft_strjoin(sort->path, "/")))
				print_error(errno);
			recursive_list(tmp, flags);
			free(tmp);
		}
		else
			recursive_list(sort->path, flags);
		if ((sort = sort->next) != NULL)
			ft_printf("\n");
	}
	destroy_list(head);
}

void	check_argv(char **argv, int *flags)
{
	int		i;
	t_list	*begin;

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
	i = create_argv_list(&begin, argv, i, flags) - i;
	sort_argv_list(begin, flags, i);
}
