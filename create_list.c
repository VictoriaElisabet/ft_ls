/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:28:19 by vgrankul          #+#    #+#             */
/*   Updated: 2019/10/31 13:49:20 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"
#include <stdio.h>

t_list *ft_create_elem(char *path)
{
    t_list *temp;

    //ft_printf("pat %s\n", path);
	temp = (t_list*)malloc(sizeof(t_list));
	temp->path = path;
	temp->next = NULL;
	return (temp);
}
void    push(t_list **head, char *path)
{
    t_list *temp;
    
	temp = (t_list*)malloc(sizeof(t_list));
	temp->path = ft_strdup(path);
	temp->next = *head;
    *head = temp;

}
void append(t_list *head, char *path)
{
    t_list *cursor;
	t_list *new;

	cursor = head;
	while (cursor->next != NULL)
    {
		cursor = cursor->next;
    }
	new = ft_create_elem(path);
	cursor->next = new;
}

t_list   *create_path_list(t_list **head, char *path)
{

    if (!*head)
    {
		*head = ft_create_elem(path);
    }
	//else
    //{
		append(*head, path);
    //}
   // print_list(*head);
    return(*head);
    //ft_printf("%s\n", path);

}

void print_list(t_list *head) 
{
    t_list *current;
    
    current = head;
    while (current != NULL) 
    {
        ft_printf("path %s\n", current->path);
        current = current->next;
    }
}