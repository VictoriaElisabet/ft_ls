/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpfunctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

void	print_error(int errnum)
{
	ft_printf("%s\n", strerror(errnum));
	exit(EXIT_FAILURE);
}

int		check_a_flag(char *filename, t_flags *new)
{
	if ((ft_strcmp(filename, ".") != 0 && ft_strcmp(filename, "..") != 0) ||
		(new->a_flag == 1 && (ft_strcmp(filename, ".") == 0 ||
		ft_strcmp(filename, "..") == 0)))
		return (1);
	else
		return (0);
}

int		check_path(char *path)
{
	int len;

	len = ft_strlen(path);
	if (path[len - 1] == '/')
		return (0);
	else
		return (-1);
}
