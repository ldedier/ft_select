/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstpop_ptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 19:34:01 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/10 19:34:03 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_dlstpop_ptr(t_dlist **list)
{
	void	*content;
	t_dlist	*ptr;

	if (*list != NULL)
	{
		ptr = *list;
		content = ptr->content;
		(*list)->prev->next = (*list)->next;
		(*list)->next->prev = (*list)->prev;
		*list = (*list)->next;
		free(ptr);
		return (content);
	}
	return (NULL);
}
