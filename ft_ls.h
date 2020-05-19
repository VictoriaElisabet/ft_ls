/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:24:05 by vgrankul          #+#    #+#             */
/*   Updated: 2020/02/27 13:01:07 by vgrankul         ###   ########.fr       */
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

typedef struct	s_list
{
	char			*path;
	struct s_list	*next;
}				t_list;

typedef struct	s_file
{
	char	*permissions;
	int		links;
	char	*uid;
	char	*guid;
	int		size;
	char	*time;
	char	*filename;
	long	mod_time;
	char	*linked_name;
}				t_file;

typedef struct	s_flags
{
	int l_flag;
	int rec_flag;
	int r_flag;
	int t_flag;
	int a_flag;
}				t_flags;

int				count_files(char *path);
int				check_a_flag(char *filename, t_flags *new);
int				check_path(char *path);
int				count_not_alpha(char *str);
int				check_dir(char *filename, t_flags *new);

void			print_list(t_list *head);
void			append(t_list *head, char *path);
void			push(t_list **head, char *path);
void			create_arr(char *path, t_flags *new);
void			get_path_list(t_list **head, char *basepath, t_flags *new,
				char *tmp);
void			destroy_list(t_list *head);
void			set_file_struct(t_file *file, struct dirent *fileinfo,
				struct stat *buf, char *path);
void			print_files(t_file **filearr, unsigned int total, t_flags *new);
void			set_flag_struct(t_flags *new);
void			print_error(int errnum);
void			sort_arr_name(t_file **arr);
void			sort_mod_arr_name(t_file **arr);
void			sort_rev_arr_name(t_file **arr);
void			fill_flag_struct(char *argv, t_flags *new);

t_list			*create_path_list(t_list **head, char *path);
t_list			*ft_create_elem(char *path);
t_list			*sort_path_time_list(t_list *head, char *tmp);
t_list			*sort_rev_path_list(t_list *head);
t_list			*sort_path_list(t_list *head);

char			*remove_not_alpha(char *str);

#endif
