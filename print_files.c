/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/08/12 18:18:17 by vgrankul         ###   ########.fr       */
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

void	print_list(t_file *filearr, int size[4])
{
	if (filearr->linked_name != NULL && (filearr->permissions[0] == 'c' ||
	filearr->permissions[0] == 'b'))
		ft_printf("%s %*d %*s %*s %*d,%*d %s %s -> %s\n",
		filearr->permissions, size[0], filearr->links, size[2], filearr->uid,
		size[3], filearr->guid, 4, filearr->major, 4, filearr->minor,
		filearr->time, filearr->filename, filearr->linked_name);
	else if (filearr->linked_name == NULL && (filearr->permissions[0] == 'c' ||
	filearr->permissions[0] == 'b'))
		ft_printf("%s %*d %*s %*s %*d,%*d %s %s\n",
		filearr->permissions, size[0], filearr->links, size[2],
		filearr->uid, size[3], filearr->guid, 4, filearr->major,
		4, filearr->minor, filearr->time, filearr->filename);
	else if (filearr->linked_name != NULL)
		ft_printf("%s %*d %*s %*s %*ld %s %s -> %s\n",
		filearr->permissions, size[0], filearr->links, size[2],
		filearr->uid, size[3], filearr->guid, size[1], filearr->size,
		filearr->time, filearr->filename, filearr->linked_name);
	else
		ft_printf("%s %*d %*s %*s %*ld %s %s\n", filearr->permissions,
		size[0], filearr->links, size[2], filearr->uid, size[3], filearr->guid,
		size[1], filearr->size, filearr->time, filearr->filename);
}

void	print_files(t_file **filearr, unsigned int total, int *flags)
{
	int i;
	int size[4];

	i = 0;
	set_maxlen(filearr, size, flags);
	if (filearr[2] != NULL && (*flags & L_FLAG))
		ft_printf("total %d\n", total);
	else if (check_a_flag(filearr[i]->filename, flags) == 1 &&
	(*flags & L_FLAG))
		ft_printf("total %d\n", total);
	while (filearr[i] != NULL)
	{
		if (check_a_flag(filearr[i]->filename, flags) == 1)
		{
			if (*flags & L_FLAG)
				print_list(filearr[i], size);
			else
				ft_printf("%s\n", filearr[i]->filename);
		}
		i++;
	}
}
