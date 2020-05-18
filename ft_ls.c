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

int		count_files(char *path)
{
	struct dirent	*test2;
	DIR				*dir;
	int				i;

	i = 0;
	dir = opendir(path);
	if (!(dir))
	{
		ft_printf("ft_ls: cannot access '%s' : ", path);
		perror("");
		exit(EXIT_FAILURE);
	}
	while ((test2 = readdir(dir)) != NULL)
	{
		i++;
	}
	if (closedir(dir) == -1)
	{
		strerror(errno);
		exit(EXIT_FAILURE);
	}
	return (i);
}
int		count_maxlen(t_file **filearr)
{
	int max_len;
	int i;

	max_len = 0;
	i = 0;
	while(filearr[i] != NULL)
	{
		if(filearr[i]->size > max_len)
			max_len = filearr[i]->size;
		i++;
	}
	return (max_len);
}

void	print_files(t_file **filearr, unsigned int total, t_flags *new)
{
	int i;
	//int maxlen;
	//char *tmp;

	//maxlen = ft_count_digits(count_maxlen(filearr), 10);
	//i = 0;
	//get the bigges size and link? to set the padding
	i = 0;
	if (new->l_flag == 1)
		ft_printf("total %d\n", total);
	while (filearr[i] != NULL)
	{
		if (check_a_flag(filearr[i]->filename, new) == 1)
		{
			if (new->l_flag == 1)
			{
				//ft_printf("le %d\n", maxlen - ft_count_digits(filearr[i]->size, 10));
				//tmp = ft_strnew(maxlen - ft_count_digits(filearr[i]->size, 10) + 1);
				//tmp = ft_memset(tmp, ' ', ft_count_digits(filearr[i]->size, 10));
				if(filearr[i]->linked_name != NULL)
					ft_printf("%s %d %s %s %ld %s %s -> %s\n", filearr[i]->permissions,
					filearr[i]->links, filearr[i]->uid, filearr[i]->guid,
					filearr[i]->size, filearr[i]->time, filearr[i]->filename, filearr[i]->linked_name);
				else
					ft_printf("%s %d %s %s %ld %s %s\n", filearr[i]->permissions,
					filearr[i]->links, filearr[i]->uid, filearr[i]->guid,
					filearr[i]->size, filearr[i]->time, filearr[i]->filename);
				//free(tmp);
			}
			else
				ft_printf("%s\n", filearr[i]->filename);
		}
		i++;
	}
	ft_printf("\n");
}

void	testfunc(char *basepath, t_flags *new)
{
	t_list *head;
	t_list *sort;

	head = NULL;
	create_arr(basepath, new);
	if (new->rec_flag == 1)
	{
		get_path_list(&head, basepath, new);
		if (new->t_flag == 1)
			sort = sort_path_time_list(head);
		else
			sort = sort_path_list(head);
		if (new->r_flag == 1)
			sort = sort_rev_path_list(head);
		while (sort != NULL)
		{
			testfunc(sort->path, new);
			sort = sort->next;
		}
		destroy_list(head);
	}
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
			//ft_printf("l %d R %d r %d t %d a %d %s\n", new.l_flag, new.rec_flag, new.r_flag, new.t_flag, new.a_flag, argv[i]);
		else
		{
			if (check_path(argv[i]) != 0)
			{
				if (!(tmp = ft_strjoin(argv[i], "/")))
					print_error(errno);
				testfunc(tmp, new);
				free(tmp);
			}
			else
				testfunc(argv[i], new);
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
		testfunc("./", &new);
}
