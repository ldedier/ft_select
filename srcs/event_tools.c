/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 19:48:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/13 20:01:03 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		dist_to_start(t_dlist *ptr, t_env *e)
{
	t_dlist	*ptr2;
	int		i;

	i = 0;
	ptr2 = ptr;
	while (ptr2 != e->args)
	{
		ptr2 = ptr2->next;
		i++;
	}
	return (i);
}

int		dist_to_start_inv(t_dlist *ptr, t_env *e)
{
	t_dlist	*ptr2;
	int		i;

	i = 0;
	ptr2 = ptr;
	while (ptr2 != e->args)
	{
		ptr2 = ptr2->prev;
		i++;
	}
	return (i);
}

void	suppr_current(t_env *e, int *stop)
{
	t_dlist *ptr;
	t_dlist *new_cursor;

	if (e->cursor == e->args->prev)
		new_cursor = e->cursor->prev;
	else
		new_cursor = e->cursor->next;
	ptr = e->cursor;
	e->cursor->prev->next = e->cursor->next;
	e->cursor->next->prev = e->cursor->prev;
	if (ptr == e->args)
		e->args = e->args->next;
	free(ptr->content);
	free(ptr);
	ptr = NULL;
	if (!(--e->nb_args))
	{
		*stop = NO_PRINT;
		e->args = NULL;
	}
	else
		e->cursor = new_cursor;
	update_center(e);
	render(e);
}
