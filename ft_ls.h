/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:24:05 by vgrankul          #+#    #+#             */
/*   Updated: 2020/08/14 16:14:33 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <errno.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <stdio.h>
#include <sys/sysmacros.h>

# define A_FLAG		1
# define L_FLAG 	2
# define R_FLAG 	4
# define RE_FLAG	8
# define T_FLAG		16

typedef struct	s_list
{
	char			*path;
	struct s_list	*next;
}				t_list;

typedef struct	s_file
{
	char	*path;
	char	*permissions;
	int		links;
	char	*uid;
	char	*guid;
	long	size;
	char	*time;
	char	*filename;
	time_t	mod_time;
	char	*linked_name;
	int		minor;
	int		major;
}				t_file;

int				check_path(char *path);
int				count_not_alpha(char *str);
int				check_a_flag(char *filename, int *flags);
int				check_dir(char *filename, int *flags);
int				create_arr_data(t_file **filearr, char *path,
				int *flags, DIR *dir);
int				create_argv_list(t_list **begin, char **argv, int i,
				int *flags);
int				ft_strindex(char *str, int c);

void			push(t_list **head, char *path);
void			destroy_list(t_list *head);
void			set_file_struct(t_file *file, char *filename,
				struct stat *buf, char *path);
void			print_error(int errnum);
void			sort_arr_name(t_file **arr);
void			sort_mod_arr_name(t_file **arr);
void			sort_rev_arr_name(t_file **arr);
void			print_list(t_file *filearr, int size[4]);
void			set_flags(char *argv, int *flags);
void			print_files(t_file **filearr, unsigned int total, int *flags);
void			set_maxlen(t_file **filearr, int max_size[4], int *flags);
void			check_argv(char **argv, int *flags);
void			recursive_list(char *basepath, int *flags);
void			create_arr(char *path, int *flags);
void			get_path_list(t_list **head, char *basepath,
				int *flags, char *tmp);
void			sort_argv_list(t_list *head, int *flags, int i);
void			destroy_filearr(t_file **filearr);
void			print_reg_files(t_list *reg_files, int *flags);

t_list			*create_path_list(t_list **head, char *path);
t_list			*ft_create_elem(char *path);
t_list			*sort_path_time_list(t_list *head, char *tmp);
t_list			*sort_rev_path_list(t_list *head);
t_list			*sort_path_list(t_list *head);

char			*remove_not_alpha(char *str);
char			*set_time(long int time);
char			*set_file_perm(struct stat *buf);
char			*set_linked_name(char *path, struct stat *buf);

#endif
