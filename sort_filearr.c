/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_filearr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
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
			if (!(str1 = ft_string_tolower(remove_not_alpha(arr[i]->filename)))
			||
			!(str2 = ft_string_tolower(remove_not_alpha(arr[j + 1]->filename))))
				print_error(errno);
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
