/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

static char	*set_time(long int time)
{
	char *time_str;

	if (!(time_str = ft_strsub(ctime(&time), 4, 12)))
		print_error(errno);
	return (time_str);
}

static char	*set_file_perm(struct stat *buf)
{
	char *perm_str;

	if (!(perm_str = (char*)malloc(10 * sizeof(char) + 1)))
		print_error(errno);
	if (S_ISDIR(buf->st_mode))
		perm_str[0] = 'd';
	else if (S_ISLNK(buf->st_mode))
		perm_str[0] = 'l';
	else
		perm_str[0] = '-';
	perm_str[1] = (buf->st_mode & S_IRUSR) ? 'r' : '-';
	perm_str[2] = (buf->st_mode & S_IWUSR) ? 'w' : '-';
	perm_str[3] = (buf->st_mode & S_IXUSR) ? 'x' : '-';
	perm_str[4] = (buf->st_mode & S_IRGRP) ? 'r' : '-';
	perm_str[5] = (buf->st_mode & S_IWGRP) ? 'w' : '-';
	perm_str[6] = (buf->st_mode & S_IXGRP) ? 'x' : '-';
	perm_str[7] = (buf->st_mode & S_IROTH) ? 'r' : '-';
	perm_str[8] = (buf->st_mode & S_IWOTH) ? 'w' : '-';
	perm_str[9] = (buf->st_mode & S_IXOTH) ? 'x' : '-';
	perm_str[10] = '\0';
	return (perm_str);
}

char		*set_linked_name(char *path, struct stat *buf)
{
	char *tmp;
	ssize_t len;

	if(!(tmp = (char*)malloc(buf->st_size * sizeof(char) + 1)))
		print_error(errno);
    if((len = readlink(path, tmp, sizeof(tmp) -1)) < 0)
    	print_error(errno);
	else
		tmp[len] = '\0';
    return(tmp);
}

void		set_file_struct(t_file *file, struct dirent *fileinfo,
				struct stat *buf, char *path)
{
	struct passwd	*userid;
	struct group	*groupid;

	if (!(userid = getpwuid(buf->st_uid)))
		print_error(errno);
	if (!(groupid = getgrgid(buf->st_gid)))
		print_error(errno);
	if(S_ISLNK(buf->st_mode))
		file->linked_name = set_linked_name(path, buf);
	else
		file->linked_name = NULL;
	file->permissions = set_file_perm(buf);
	file->links = buf->st_nlink;
	file->uid = userid->pw_name;
	file->guid = groupid->gr_name;
	file->size = buf->st_size;
	file->time = set_time(buf->st_mtime);
	file->filename = fileinfo->d_name;
	file->mod_time = buf->st_mtime;
}

void		set_flag_struct(t_flags *new)
{
	new->l_flag = 0;
	new->rec_flag = 0;
	new->a_flag = 0;
	new->r_flag = 0;
	new->t_flag = 0;
}

void		fill_flag_struct(char *argv, t_flags *new)
{
	int i;

	i = 1;
	while (argv[i] != '\0')
	{
		if (argv[i] == 'l')
			new->l_flag = 1;
		else if (argv[i] == 'R')
			new->rec_flag = 1;
		else if (argv[i] == 'r')
			new->r_flag = 1;
		else if (argv[i] == 't')
			new->t_flag = 1;
		else if (argv[i] == 'a')
			new->a_flag = 1;
		else
		{
			ft_printf("./ft_ls: invalid option -- '%c'\nTry 'ls --help' for more information\n", argv[i]);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
