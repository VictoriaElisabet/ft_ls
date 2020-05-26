/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

void	set_maxlen(t_file **filearr, int max_size[4], int *flags)
{
	int i;

	i = 0;
	max_size[0] = 0;
	max_size[1] = 0;
	max_size[2] = 0;
	max_size[3] = 0;
	while (filearr[i] != 0)
	{
		if (check_a_flag(filearr[i]->filename, flags) == 1)
			if (ft_count_digits(filearr[i]->links, 10) > max_size[0])
				max_size[0] = ft_count_digits(filearr[i]->links, 10);
		if (check_a_flag(filearr[i]->filename, flags) == 1)
			if (ft_count_digits(filearr[i]->size, 10) > max_size[1])
				max_size[1] = ft_count_digits(filearr[i]->size, 10);
		if (ft_strlen(filearr[i]->uid) > (size_t)max_size[2])
			max_size[2] = ft_strlen(filearr[i]->uid);
		if (ft_strlen(filearr[i]->guid) > (size_t)max_size[3])
			max_size[3] = ft_strlen(filearr[i]->guid);
		i++;
	}
}

void	print_list(t_file **filearr, int i, int size[4])
{
	if (filearr[i]->linked_name != NULL)
		ft_printf("%s %*d %*s %*s %*ld %s %s -> %s\n",
		filearr[i]->permissions, size[0],
		filearr[i]->links, size[2], filearr[i]->uid,
		size[3], filearr[i]->guid, size[1],
		filearr[i]->size, filearr[i]->time,
		filearr[i]->filename, filearr[i]->linked_name);
	else
		ft_printf("%s %*d %*s %*s %*ld %s %s\n", filearr[i]->permissions,
		size[0], filearr[i]->links, size[2],
		filearr[i]->uid, size[3], filearr[i]->guid,
		size[1], filearr[i]->size,
		filearr[i]->time, filearr[i]->filename);
}

void	print_files(t_file **filearr, unsigned int total, int *flags)
{
	int i;
	int size[4];

	i = 0;
	set_maxlen(filearr, size, flags);
	if (*flags & l_flag)
		ft_printf("total %d\n", total);
	while (filearr[i] != NULL)
	{
		if (check_a_flag(filearr[i]->filename, flags) == 1)
		{
			if (*flags & l_flag)
				print_list(filearr, i, size);
			else
				ft_printf("%s\n", filearr[i]->filename);
		}
		i++;
	}
	//ft_printf("\n");
}
