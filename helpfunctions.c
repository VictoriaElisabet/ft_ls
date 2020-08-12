/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpfunctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/08/12 15:16:29 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

int		ft_strindex(char *str, int c)
{
	int i;
	int counter;

	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (counter);
		counter++;
		i++;
	}
	return (-1);
}

int		check_dir(char *filename, int *flags)
{
	if ((ft_strcmp(filename, ".") != 0 &&
		ft_strcmp(filename, "..") != 0 && filename[0] != '.') ||
		((*flags & A_FLAG) && ft_strcmp(filename, ".") != 0 &&
		ft_strcmp(filename, "..") != 0 && filename[0] == '.'))
		return (1);
	else
		return (0);
}

int		check_a_flag(char *filename, int *flags)
{
	if ((ft_strcmp(filename, ".") != 0 && ft_strcmp(filename, "..") != 0
		&& filename[0] != '.') ||
		((*flags & A_FLAG) == 1 && (ft_strcmp(filename, ".") == 0 ||
		ft_strcmp(filename, "..") == 0 || filename[0] == '.')))
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
	if((tmp = (char*)malloc(len * sizeof(char) + 1)))
	{
		while (str[i] != '\0')
		{
			if (ft_isalpha(str[i]) == 1)
				tmp[j++] = str[i];
			i++;
		}
		tmp[j] = '\0';
	}
	return (tmp);
}
