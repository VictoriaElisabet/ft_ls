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

typedef struct	s_file
{
    char *filename;
	//void	*next;
}				t_file;

typedef struct	s_flags
{
    int l_flag;
    int R_flag;
    int r_flag;
    int t_flag;
    int a_flag;
	//void	*next;
}				t_flags;



#include <dirent.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>


#endif