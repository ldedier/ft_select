/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 19:48:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/05 04:23:38 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

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
