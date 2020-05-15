/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filearr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

static void	destroy_filearr(t_file **filearr)
{
	int i;

	i = 0;
	while (filearr[i] != NULL)
	{
		if(filearr[i]->linked_name != NULL)
			free(filearr[i]->linked_name);
		free(filearr[i]->time);
		free(filearr[i]->permissions);
		free(filearr[i]);
		i++;
	}
	free(filearr);
}

int			create_arr_data(t_file **filearr, char *path, t_flags *new,
			DIR *dir)
{
	int				i;
	struct dirent	*test3;
	struct stat		buf;
	char			*tmp;
	unsigned int	total;

	i = 0;
	total = 0;
	while ((test3 = readdir(dir)) != NULL)
	{
		if (!(tmp = ft_strjoin(path, test3->d_name)))
			print_error(errno);
		if (lstat(tmp, &buf) == -1)
			print_error(errno);
		if (check_a_flag(test3->d_name, new) == 1)
			total = total + buf.st_blocks;
		if (!(filearr[i] = (t_file*)malloc(sizeof(t_file))))
			print_error(errno);
		set_file_struct(filearr[i], test3, &buf, tmp);
		free(tmp);
		i++;
	}
	if (closedir(dir) == -1)
		print_error(errno);
	filearr[i] = NULL;
	return (total);
}

void		create_arr(char *path, t_flags *new)
{
	t_file			**filearr;
	DIR				*dir;
	unsigned int	total;

	total = 0;
	if (!(dir = opendir(path)))
	{
		ft_printf("ft_ls: cannot access '%s': ", path);
		print_error(errno);
	}
	if(new->rec_flag == 1)
		ft_printf("%s:\n", path);
	if (!(filearr = (t_file**)malloc(count_files(path) * sizeof(t_file*) + 1)))
		print_error(errno);
	total = create_arr_data(filearr, path, new, dir);
	new->t_flag == 1 ? sort_mod_arr_name(filearr) : sort_arr_name(filearr);
	if (new->r_flag == 1)
		sort_rev_arr_name(filearr);
	print_files(filearr, total, new);
	destroy_filearr(filearr);
}
