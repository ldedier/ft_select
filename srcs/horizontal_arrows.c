/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_arrows.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 19:46:45 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/13 20:02:14 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_dlist	*get_right_from_cursor(t_env *e)
{
	t_dlist *ptr;
	int		i;
	int		dist;

	i = 0;
	ptr = e->cursor;
	if (ptr != e->args && dist_to_start(ptr, e) < e->center.nb_lines)
		return (e->args);
	else
		dist = e->center.nb_lines;
	while (i < dist)
	{
		ptr = ptr->next;
		i++;
	}
	return (ptr);
}

t_dlist	*get_left_from_cursor(t_env *e)
{
	t_dlist *ptr;
	int		i;
	int		dist;

	i = 0;
	ptr = e->cursor;
	if (dist_to_start_inv(ptr, e) < e->center.nb_lines)
		return (e->args->prev);
	else
		dist = e->center.nb_lines;
	while (i < dist)
	{
		ptr = ptr->prev;
		i++;
	}
	return (ptr);
}

int		process_right(t_env *e)
{
	t_dlist *ptr;

	ptr = e->cursor;
	e->cursor = get_right_from_cursor(e);
	render_arg_ptr(e, e->cursor);
	render_arg_ptr(e, ptr);
	return (0);
}

int		process_left(t_env *e)
{
	t_dlist *ptr;

	ptr = e->cursor;
	e->cursor = get_left_from_cursor(e);
	render_arg_ptr(e, e->cursor);
	render_arg_ptr(e, ptr);
	return (0);
}
