/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_arrow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 02:37:59 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/05 03:25:06 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		is_eligible_as_right(t_env *env, t_arg *arg_iter,
			t_arg *arg)
{
	if (arg_iter->y == arg->y && arg_iter->x == arg->x + 1)
		return (1);
	else if (arg_iter->x == 0 && arg_iter->y == arg->y + 1
			&& ((env->center.nb_lines == 1)
				|| (env->center.nb_lines > 1
					&& arg->x != 0)))
		return (1);
	else if (arg->y == env->center.nb_lines - 1
			&& arg_iter->y == env->center.nb_lines - 1
			&& arg_iter->x == 0)
		return (1);
	return (0);
}

int		update_head_right(t_env *env)
{
	t_dlist	*ptr;
	t_arg	*arg;
	t_arg	*arg_iter;

	arg = (t_arg *)env->cursor->content;
	ptr = env->cursor->next;
	while (ptr != env->cursor)
	{
		arg_iter = (t_arg *)(ptr->content);
		if (is_eligible_as_right(env,
					arg_iter, arg))
		{
			env->cursor = ptr;
			return (0);
		}
		ptr = ptr->next;
	}
	return (1);
}

int		process_right(t_env *env)
{
	t_dlist *prev_cursor_ptr;

	prev_cursor_ptr = env->cursor;
	if (!update_head_right(env))
	{
		render_arg_ptr(env, prev_cursor_ptr);
		render_arg_ptr(env, env->cursor);
		return (0);
	}
	return (1);
}
