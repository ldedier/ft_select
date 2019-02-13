/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:58:32 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/13 20:23:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		max_col_drawn(t_env *e)
{
	int		i;
	int		j;
	int		max;

	max = -1;
	j = 0;
	while (j < e->center.nb_columns)
	{
		i = 0;
		while (i < e->center.nb_lines &&
			j * e->center.nb_lines + i < e->nb_args)
		{
			if (max < j)
				max = j;
			i++;
		}
		j++;
	}
	return (max + 1);
}

int		can_render_title(t_env *e)
{
	return (e->winsize.ws_col > W_TITLE &&
				e->winsize.ws_row >
					e->center.nb_lines + H_TITLE + TITLE_TOP + TITLE_BOTTOM);
}

int		can_render(t_env *e)
{
	return (e->arg_max_len + e->center.w_border + 1 <= e->winsize.ws_col &&
				e->winsize.ws_row > e->center.nb_lines);
}

void	update_center(t_env *e)
{
	int c;

	e->center.nb_columns = ft_clamp(1, (e->winsize.ws_col) /
			((e->arg_max_len + 1)), e->nb_args);
	if (e->center.nb_columns > 1)
		e->center.arg_x_padding = (double)(e->winsize.ws_col -
				((e->center.nb_columns * e->arg_max_len))) / (double)
			(e->center.nb_columns - 1);
	if (e->center.nb_columns > 0)
		e->center.nb_lines = ft_round((double)e->nb_args /
				(double)e->center.nb_columns);
	c = max_col_drawn(e);
	e->center.w_border = ft_max(0, (e->winsize.ws_col -
			((c * e->arg_max_len) + (c) * e->center.arg_x_padding)) / 2.0);
}
