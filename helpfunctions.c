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

int		check_dir(char *filename, t_flags *new)
{
	if ((ft_strcmp(filename, ".") != 0 &&
		ft_strcmp(filename, "..") != 0 && filename[0] != '.') ||
		(new->a_flag == 1 && ft_strcmp(filename, ".") != 0 &&
		ft_strcmp(filename, "..") != 0 && filename[0] == '.'))
		return (1);
	else
		return (0);
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

int		count_not_alpha(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (ft_isalpha(str[i]) == 0)
			count++;
		i++;
	}
	return (count);
}

char	*remove_not_alpha(char *str)
{
	char	*tmp;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(str) - count_not_alpha(str);
	tmp = (char*)malloc(len * sizeof(char) + 1);
	while (str[i] != '\0')
	{
		if (ft_isalpha(str[i]) == 1)
			tmp[j++] = str[i];
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}
