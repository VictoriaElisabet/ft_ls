/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/08/12 18:13:48 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

void	print_error(int errnum)
{
	ft_printf("%s\n", strerror(errnum));
	exit(EXIT_FAILURE);
}

void	recursive_list(char *basepath, int *flags)
{
	t_list	*head;
	t_list	*sort;
	char	*tmp;
	char	*tmp1;

	head = NULL;
	tmp = NULL;
	tmp1 = NULL;
	create_arr(basepath, flags);
	if (*flags & RE_FLAG)
	{
		get_path_list(&head, basepath, flags, tmp1);
		(*flags & T_FLAG) ? (sort = sort_path_time_list(head, tmp)) :
			(sort = sort_path_list(head));
		if (*flags & R_FLAG)
			sort = sort_rev_path_list(head);
		while (sort != NULL)
		{
			ft_printf("\n%s:\n", sort->path);
			recursive_list(sort->path, flags);
			sort = sort->next;
		}
		destroy_list(head);
	}
}

int		main(int argc, char **argv)
{
	int flags;

	flags = 0;
	if (argc > 1)
		check_argv(argv, &flags);
	else
		recursive_list("./", &flags);
	return (0);
}
