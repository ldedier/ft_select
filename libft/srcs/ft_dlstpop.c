/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstpop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 20:11:41 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/10 21:22:19 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int     ft_is_alone_node(t_dlist *dlist)
{
	int     length;
	t_dlist *ptr;
	int     first;

	ptr = dlist;
	first = 1;
	length = 0;
	while ((ptr != dlist && ptr != NULL) || (first && ptr != NULL))
	{
		if (++length > 1)
			return (0);
		ptr = ptr->next;
		first = 0;
	}
	return (length == 1);
}

void	ft_dlstpop(t_dlist **list)
{
	void	*content;
	t_dlist	*ptr;

	if (*list != NULL)
	{
		ptr = *list;
		content = ptr->content;
		(*list)->prev->next = (*list)->next;
		(*list)->next->prev = (*list)->prev;
		free(content);
		free(ptr);
		if (*list == (*list)->next)
			*list = NULL;
		else
			*list = (*list)->next;
	}
}
