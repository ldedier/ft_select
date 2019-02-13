/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 19:49:29 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/13 20:24:37 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		is_all_selected(t_env *e)
{
	t_dlist *ptr;
	t_arg	*arg;
	int		i;

	ptr = e->args;
	i = 0;
	while (i < e->nb_args)
	{
		arg = (t_arg *)ptr->content;
		if (!arg->selected)
			return (0);
		i++;
		ptr = ptr->next;
	}
	return (1);
}

void	select_all_value(t_env *e, int val)
{
	t_dlist	*ptr;
	t_arg	*arg;
	int		i;

	ptr = e->args;
	i = 0;
	while (i < e->nb_args)
	{
		arg = (t_arg *)ptr->content;
		if (arg->selected != val)
		{
			arg->selected = val;
			render_arg_ptr(e, ptr);
		}
		i++;
		ptr = ptr->next;
	}
}

void	select_current(t_env *e)
{
	t_arg *arg;

	arg = (t_arg *)e->cursor->content;
	arg->selected = !arg->selected;
	render_arg_ptr(e, e->cursor);
}

void	process_shift_all(t_env *e)
{
	if (!can_render(e))
		return ;
	if (is_all_selected(e))
		select_all_value(e, 0);
	else
		select_all_value(e, 1);
}
