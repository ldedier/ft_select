/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:58:32 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/24 19:17:47 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	process_render_title(t_env *e, int y)
{
	move((e->winsize.ws_col - W_TITLE) / 2, y++);
	ft_dprintf(2, RED"  __  _                       _              _   "EOC);
	move((e->winsize.ws_col - W_TITLE) / 2, y++);
	ft_dprintf(2,
			MAGENTA" / _|| |                     | |            | |  "EOC);
	move((e->winsize.ws_col - W_TITLE) / 2, y++);
	ft_dprintf(2, YELLOW"| |_ | |_          ___   ___ | |  ___   ___ | |_ "EOC);
	move((e->winsize.ws_col - W_TITLE) / 2, y++);
	ft_dprintf(2,
			GREEN"|  _|| __|        / __| / _ \\| | / _ \\ / __|| __|"EOC);
	move((e->winsize.ws_col - W_TITLE) / 2, y++);
	ft_dprintf(2, CYAN"| |  | |_         \\__ \\|  __/| ||  __/| (__ | |_ "EOC);
	move((e->winsize.ws_col - W_TITLE) / 2, y++);
	ft_dprintf(2,
			L_BLUE"|_|   \\__|        |___/ \\___||_| \\___| \\___| \\__|"EOC);
	move((e->winsize.ws_col - W_TITLE) / 2, y++);
	ft_dprintf(2, BLUE"           ______                                "EOC);
	move((e->winsize.ws_col - W_TITLE) / 2, y++);
	ft_dprintf(2, BLUE"          |______|                               "EOC);
}

int		render_title(t_env *e)
{
	int		y;
	char	*res;

	y = TITLE_TOP;
	res = tgetstr("mb", NULL);
	tputs(res, 1, putchar_int);
	process_render_title(e, y);
	res = tgetstr("me", NULL);
	tputs(res, 1, putchar_int);
	return (0);
}

int		render(t_env *e)
{
	int rendered_title;

	if (e->args == NULL)
		return (0);
	clear_all();
	if (e->arg_max_len + e->center.w_border + 1 > e->winsize.ws_col)
		return (render_insufficient_width(e));
	else if (e->winsize.ws_row < e->center.nb_lines + 1)
		return (render_insufficient_height(e));
	else
	{
		rendered_title = can_render_title(e);
		if (rendered_title)
			render_title(e);
		return (render_args(e, rendered_title));
	}
}
