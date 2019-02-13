/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 18:42:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/13 13:43:54 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	process_escape_sequence(t_env *e, char *buffer, int *stop)
{
	if (buffer[1] == 91 && buffer[2] == 66)
	{
		e->cursor = e->cursor->next;
		render_arg_ptr(e, e->cursor);
		render_arg_ptr(e, e->cursor->prev);
	}
	else if (buffer[1] == 91 && buffer[2] == 65)
	{
		e->cursor = e->cursor->prev;
		render_arg_ptr(e, e->cursor);
		render_arg_ptr(e, e->cursor->next);
	}
	else if (!buffer[1] && !buffer[2])
		*stop = NO_PRINT;
}

void	select_current(t_env *e)
{
	t_arg *arg;

	arg = (t_arg *)e->cursor->content;
	arg->selected = !arg->selected;
	render_arg_ptr(e, e->cursor);
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

int     process_keys(t_env *e)
{
	char	buffer[3];
	int		stop;

	stop = 0;
	while (!stop)
	{
		read(0, buffer, 3);
		if (buffer[0] == 27)
			process_escape_sequence(e, buffer, &stop);
		else if (buffer[0] == 32)
			select_current(e);
		else if (buffer[0] == 127 || buffer[0] == 126)
			suppr_current(e, &stop);
		else if (buffer[0] == 10)
			stop = PRINT;
		ft_bzero(buffer, sizeof(buffer));
	}
	return (stop);
}
