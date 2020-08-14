/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/08/14 16:09:23 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

char	*set_time(long int ftime)
{
	char	*time_str;
	time_t	today;
	char	*date;
	char	*year;

	today = time(NULL);
	if (ftime - today > 15778476 || ftime - today < -15778476)
	{
		if (!(date = ft_strsub(ctime(&ftime), 4, 7)))
			print_error(errno);
		if (!(year = ft_strsub(ctime(&ftime), 19, 5)))
			print_error(errno);
		if (!(time_str = ft_strjoin(date, year)))
			print_error(errno);
		free(date);
		free(year);
	}
	else
	{
		if (!(time_str = ft_strsub(ctime(&ftime), 4, 12)))
			print_error(errno);
	}
	return (time_str);
}

void	set_file_attr(char *perm_str, struct stat *buf)
{
	if (S_ISDIR(buf->st_mode))
		perm_str[0] = 'd';
	else if (S_ISLNK(buf->st_mode))
		perm_str[0] = 'l';
	else if (S_ISBLK(buf->st_mode))
		perm_str[0] = 'b';
	else if (S_ISCHR(buf->st_mode))
		perm_str[0] = 'c';
	else
		perm_str[0] = '-';
}

char	*set_file_perm(struct stat *buf)
{
	char *perm_str;

	if (!(perm_str = (char*)malloc(10 * sizeof(char) + 1)))
		print_error(errno);
	set_file_attr(&perm_str[0], buf);
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
	if (buf->st_mode & S_ISUID)
		perm_str[3] = perm_str[3] == '-' ? 'S' : 's';
	if (buf->st_mode & S_ISGID)
		perm_str[3] = perm_str[3] == '-' ? 'S' : 's';
	if (buf->st_mode & S_ISVTX)
		perm_str[9] = perm_str[9] == '-' ? 'T' : 't';
	return (perm_str);
}

char	*set_linked_name(char *path, struct stat *buf)
{
	char	*tmp;
	ssize_t	len;

	tmp = NULL;
	if ((tmp = (char*)malloc(buf->st_size * sizeof(char) + 1)))
	{
		if ((len = readlink(path, tmp, buf->st_size)) < 0)
		{
			free(tmp);
			ft_printf("./ft_ls: cannot read symbolic link '%s': %s\n",
			path, strerror(errno));
			return (NULL);
		}
		else
			tmp[len] = '\0';
	}
	return (tmp);
}

void	set_flags(char *argv, int *flags)
{
	int i;
	int n;

	i = 1;
	n = 0;
	while (argv[i] != '\0')
	{
		if ((n = ft_strindex("alrRt", argv[i])) == -1)
		{
			ft_printf("./ft_ls: invalid option -- '%c'\n", argv[i]);
			ft_printf("Try 'ls --help' for more information\n");
			exit(EXIT_FAILURE);
		}
		*flags |= 1 << n;
		i++;
	}
}
