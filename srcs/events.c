/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 18:42:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/13 20:01:46 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	process_escape_sequence_2(t_env *e, char *buffer, int *stop)
{
	t_dlist *ptr;

	if (buffer[1] == 91 && buffer[2] == 72 && can_render(e))
	{
		ptr = e->cursor;
		e->cursor = e->args;
		render_arg_ptr(e, e->cursor);
		render_arg_ptr(e, ptr);
	}
	else if (buffer[1] == 91 && buffer[2] == 70 && can_render(e))
	{
		ptr = e->cursor;
		e->cursor = e->args->prev;
		render_arg_ptr(e, e->cursor);
		render_arg_ptr(e, ptr);
	}
	else if (!buffer[1] && !buffer[2])
		*stop = NO_PRINT;
}

void	process_escape_sequence(t_env *e, char *buffer, int *stop)
{
	if (buffer[1] == 91 && buffer[2] == 66 && can_render(e))
	{
		e->cursor = e->cursor->next;
		render_arg_ptr(e, e->cursor);
		render_arg_ptr(e, e->cursor->prev);
	}
	else if (buffer[1] == 91 && buffer[2] == 65 && can_render(e))
	{
		e->cursor = e->cursor->prev;
		render_arg_ptr(e, e->cursor);
		render_arg_ptr(e, e->cursor->next);
	}
	else if (buffer[1] == 91 && buffer[2] == 67 && can_render(e))
		process_right(e);
	else if (buffer[1] == 91 && buffer[2] == 68 && can_render(e))
		process_left(e);
	else
		process_escape_sequence_2(e, buffer, stop);
}

void	process_shift_sequence(t_env *e, char *buffer)
{
	if (buffer[1] == 50 && buffer[2] == 66 && can_render(e))
	{
		e->cursor = e->cursor->next->next;
		render_arg_ptr(e, e->cursor);
		render_arg_ptr(e, e->cursor->prev->prev);
	}
	else if (buffer[1] == 50 && buffer[2] == 65 && can_render(e))
	{
		e->cursor = e->cursor->prev->prev;
		render_arg_ptr(e, e->cursor);
		render_arg_ptr(e, e->cursor->next->next);
	}
	else if (buffer[1] == 50 && buffer[2] == 67 && can_render(e))
	{
		process_right(e);
		process_right(e);
	}
	else if (buffer[1] == 50 && buffer[2] == 68 && can_render(e))
	{
		process_left(e);
		process_left(e);
	}
}

int		process_keys(t_env *e)
{
	char	buffer[3];
	int		stop;

	stop = 0;
	while (!stop)
	{
		read(0, buffer, 3);
		if (buffer[0] == 27)
			process_escape_sequence(e, buffer, &stop);
		if (buffer[0] == 59)
			process_shift_sequence(e, buffer);
		if (buffer[0] == 9)
			process_shift_all(e);
		else if (buffer[0] == 32)
			select_current(e);
		else if (buffer[0] == 127 || buffer[0] == 126)
			suppr_current(e, &stop);
		else if (buffer[0] == 10)
			stop = PRINT;
	//	ft_dprintf(2,"%d %d %d\n ", buffer[0], buffer[1], buffer[2]);
		ft_bzero(buffer, sizeof(buffer));
	}
	return (stop);
}
