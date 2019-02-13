/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 19:31:43 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/13 20:34:48 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		render_arg(t_env *e, t_dlist *ptr, int x, int y)
{
	t_arg	*arg;
	char	*res;

	arg = (t_arg *)ptr->content;
	move(x, y);
	ft_dprintf(2, "%s%s%s", BOLD, PREFIX_STR, EOC);
	if (arg->selected)
	{
		res = tgetstr("mr", NULL);
		tputs(res, 1, putchar_int);
	}
	if (ptr == e->cursor)
	{
		res = tgetstr("us", NULL);
		tputs(res, 1, putchar_int);
	}
	ft_dprintf(2, "%s%s\n", arg->color, arg->name);
	res = tgetstr("me", NULL);
	tputs(res, 1, putchar_int);
	return (0);
}

int		process_render_arg_ptr(t_env *e, int title_rendered, t_dlist *to_render)
{
	t_xy	xy;
	int		i;
	int		j;
	t_dlist	*ptr;

	j = 0;
	ptr = e->args;
	xy.x = e->center.w_border;
	while (j < e->center.nb_columns)
	{
		i = 0;
		xy.y = title_rendered * (TITLE_TOP + H_TITLE + TITLE_BOTTOM);
		while (i < e->center.nb_lines &&
			j * e->center.nb_lines + i < e->nb_args)
		{
			if (ptr == to_render)
				return (render_arg(e, ptr, xy.x, xy.y));
			xy.y++;
			i++;
			ptr = ptr->next;
		}
		xy.x += e->arg_max_len + e->center.arg_x_padding;
		j++;
	}
	return (0);
}

int		render_arg_ptr(t_env *e, t_dlist *to_render)
{
	if (!can_render(e))
		return (0);
	else
		return (process_render_arg_ptr(e, can_render_title(e), to_render));
}

int		render_args(t_env *e, int title_rendered)
{
	int		i;
	int		j;
	t_xy	xy;
	t_dlist *ptr;

	j = 0;
	ptr = e->args;
	xy.x = e->center.w_border;
	while (j < e->center.nb_columns)
	{
		i = 0;
		xy.y = title_rendered * (TITLE_TOP + H_TITLE + TITLE_BOTTOM);
		while (i < e->center.nb_lines &&
					j * e->center.nb_lines + i < e->nb_args)
		{
			if (render_arg(e, ptr, xy.x, xy.y))
				return (1);
			xy.y += 1;
			i++;
			ptr = ptr->next;
		}
		xy.x += e->arg_max_len + e->center.arg_x_padding;
		j++;
	}
	return (0);
}
