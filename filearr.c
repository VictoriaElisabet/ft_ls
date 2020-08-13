/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filearr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/08/13 16:19:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

void		set_file_struct(t_file *file, char *filename,
				struct stat *buf, char *path)
{
	struct passwd	*userid;
	struct group	*groupid;

	if (S_ISBLK(buf->st_mode) || S_ISCHR(buf->st_mode))
	{
		file->minor = minor(buf->st_rdev);
		file->major = major(buf->st_rdev);
	}
	if (!(userid = getpwuid(buf->st_uid)))
		file->uid = ft_itoa(buf->st_uid);
	else
		file->uid = ft_strdup(userid->pw_name);
	if (!(groupid = getgrgid(buf->st_gid)))
		file->guid = ft_itoa(buf->st_gid);
	else
		file->guid = ft_strdup(groupid->gr_name);
	file->linked_name = S_ISLNK(buf->st_mode) ? set_linked_name(path, buf) :
	NULL;
	file->path = ft_strdup(path);
	file->permissions = set_file_perm(buf);
	file->links = buf->st_nlink;
	file->size = buf->st_size;
	file->time = set_time(buf->st_mtime);
	file->filename = ft_strdup(filename);
	file->mod_time = buf->st_mtime;
}

static int	count_files(char *path)
{
	struct dirent	*test2;
	DIR				*dir;
	int				i;

	i = 0;
	dir = opendir(path);
	if (dir)
	{
		while ((test2 = readdir(dir)) != NULL)
			i++;
		if (closedir(dir) == -1)
			print_error(errno);
	}
	return (i);
}

void		destroy_filearr(t_file **filearr)
{
	int i;

	i = 0;
	while (filearr[i] != NULL)
	{
		if (filearr[i]->linked_name != NULL)
			free(filearr[i]->linked_name);
		free(filearr[i]->time);
		free(filearr[i]->permissions);
		free(filearr[i]->uid);
		free(filearr[i]->guid);
		free(filearr[i]->filename);
		free(filearr[i]->path);
		free(filearr[i]);
		i++;
	}
	free(filearr);
}

int			create_arr_data(t_file **filearr, char *path, int *flags,
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
		if (lstat(tmp, &buf) != -1)
		{
			if (check_a_flag(test3->d_name, flags) == 1)
				total = total + buf.st_blocks;
			if (!(filearr[i] = (t_file*)malloc(sizeof(t_file))))
				print_error(errno);
			set_file_struct(filearr[i], test3->d_name, &buf, tmp);
			free(tmp);
		}
		i++;
	}
	filearr[i] = NULL;
	if (closedir(dir) == -1)
		print_error(errno);
	return (total);
}

void		create_arr(char *path, int *flags)
{
	t_file			**filearr;
	DIR				*dir;
	unsigned int	total;

	total = 0;
	if ((dir = opendir(path)) != NULL)
	{
		if (!(filearr = (t_file**)
		malloc(count_files(path) * sizeof(t_file*) + 1)))
			print_error(errno);
		total = create_arr_data(filearr, path, flags, dir);
		(*flags & T_FLAG) ? sort_mod_arr_name(filearr) : sort_arr_name(filearr);
		if (*flags & R_FLAG)
			sort_rev_arr_name(filearr);
		print_files(filearr, total, flags);
		destroy_filearr(filearr);
	}
}
