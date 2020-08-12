/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_filearr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2020/08/12 16:02:17 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

void	swap_files(t_file **arr, int i, int j)
{
	t_file *tmp;

	tmp = arr[i];
	arr[i] = arr[j + 1];
	arr[j + 1] = tmp;
}

void	sort_arr_name(t_file **arr)
{
	int		i;
	int		j;
	char	*str1;
	char	*str2;

	i = 0;
	j = 0;
	while (arr[i] != NULL)
	{
		j = i;
		while (arr[j + 1] != NULL)
		{
			str1 = ft_strdup(arr[i]->filename);
			str2 = ft_strdup(arr[j + 1]->filename);
			if (ft_strcmp(str1, str2) > 0)
				swap_files(arr, i, j);
			free(str1);
			free(str2);
			j++;
		}
		i++;
	}
}

void	sort_mod_arr_name(t_file **arr)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (arr[i] != NULL)
	{
		j = i;
		while (arr[j + 1] != NULL)
		{
			if (arr[i]->mod_time < arr[j + 1]->mod_time)
				swap_files(arr, i, j);
			j++;
		}
		i++;
	}
}

void	sort_rev_arr_name(t_file **arr)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (arr[i] != NULL)
	{
		j = i;
		while (arr[j + 1] != NULL)
		{
			swap_files(arr, i, j);
			j++;
		}
		i++;
	}
}
