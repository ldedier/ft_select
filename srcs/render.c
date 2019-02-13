/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:58:32 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/13 13:43:48 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		render_decreasing_width(t_env *e)
{
	if (e->winsize.ws_col >= 39)
		ft_dprintf(2, "going that way won't make things better");
	else if (e->winsize.ws_col >= 22)
		ft_dprintf(2, "this is the wrong way!");
	else if (e->winsize.ws_col >= 15)
		ft_dprintf(2, "what r u doing?");
	else if (e->winsize.ws_col >= 8)
		ft_dprintf(2, "really ?");
	else if (e->winsize.ws_col >= 3)
		ft_dprintf(2, "ಠ_ಠ");
	else if (e->winsize.ws_col >= 1)
		ft_dprintf(2, "益");
	return (0);
}

int		render_insufficient_width(t_env *e)
{
	if (e->winsize.ws_col >= 54 && e->arg_max_len - e->winsize.ws_col >= 5)
		ft_dprintf(2,
				"terminal width is not enough to display all arguments");
	else if (e->decreasing)
		return (render_decreasing_width(e));
	else
	{
		if (e->arg_max_len - e->winsize.ws_col < 5 && e->winsize.ws_col >= 15)
			ft_dprintf(2, "almost there...");
		else if (e->winsize.ws_col >= 21)
			ft_dprintf(2, "keep going this way!");
		else if (e->winsize.ws_col >= 11)
			ft_dprintf(2, "keep going!");
		else if (e->winsize.ws_col >= 4)
			ft_dprintf(2, "yes!");
		else if (e->winsize.ws_col >= 3)
			ft_dprintf(2, "yes");
	}
	return (0);
}

int		render_arg(t_env *e, t_dlist *ptr, int x, int y)
{
	t_arg	*arg;
	char	*res;

	arg = (t_arg *)ptr->content;
	move(x, y);
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
	ft_dprintf(2, "%s\n", arg->name);
	res = tgetstr("me", NULL);
	tputs(res, 1, putchar_int);
	return (0);
}

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
		while (i < e->center.nb_lines && j * e->center.nb_lines + i < e->nb_args)
		{
			if (max < j)
				max = j;
			i++;
		}
		j++;
	}
	return (max + 1);
}

int process_render_arg_ptr(t_env *e, int title_rendered, t_dlist *to_render)
{
	int		i;
	int		j;
	double	x_pos;
	int		y_pos;

	t_dlist *ptr;
	j = 0;
	ptr = e->args;
	x_pos = e->center.w_border;
	while (j < e->center.nb_columns)
	{
		i = 0;
		y_pos = title_rendered * (TITLE_TOP + H_TITLE + TITLE_BOTTOM);
		while (i < e->center.nb_lines && j * e->center.nb_lines + i < e->nb_args)
		{
			if (ptr == to_render)
				return (render_arg(e, ptr, x_pos, y_pos));
			y_pos += 1;
			i++;
			ptr = ptr->next;
		}
		x_pos += e->arg_max_len;
		x_pos += e->center.arg_x_padding;
		j++;
	}
	return (0);
}
int     render_arg_ptr(t_env *e, t_dlist *to_render)
{
	int title_rendered;

	if (e->arg_max_len + e->center.w_border + 1 > e->winsize.ws_col)
		return (0);
	else
	{
		title_rendered = 0;
		if (e->winsize.ws_col > W_TITLE && e->winsize.ws_row > H_TITLE)
			title_rendered = 1;
		return (process_render_arg_ptr(e, title_rendered, to_render));
	}
}

int render_args(t_env *e, int title_rendered)
{
	int		i;
	int		j;
	double	x_pos;
	int		y_pos;

	t_dlist *ptr;
	j = 0;
	ptr = e->args;
	x_pos = e->center.w_border;
	while (j < e->center.nb_columns)
	{
		i = 0;
		y_pos = title_rendered * (TITLE_TOP + H_TITLE + TITLE_BOTTOM);
		while (i < e->center.nb_lines && j * e->center.nb_lines + i < e->nb_args)
		{
			if (render_arg(e, ptr, x_pos, y_pos))
				return (1);
			y_pos += 1;
			i++;
			ptr = ptr->next;
		}
		x_pos += e->arg_max_len;
		x_pos += e->center.arg_x_padding;
		j++;
	}
	return (0);
}

void	process_render_title(t_env *e, int y)
{
	move((e->winsize.ws_col - W_TITLE) / 2 , y++);
	ft_dprintf(2, RED"  __  _                       _              _   "EOC);
	move((e->winsize.ws_col - W_TITLE) / 2 , y++);
	ft_dprintf(2,
			MAGENTA" / _|| |                     | |            | |  "EOC);
	move((e->winsize.ws_col - W_TITLE) / 2 , y++);
	ft_dprintf(2, YELLOW"| |_ | |_          ___   ___ | |  ___   ___ | |_ "EOC);
	move((e->winsize.ws_col - W_TITLE) / 2 , y++);
	ft_dprintf(2,
			GREEN"|  _|| __|        / __| / _ \\| | / _ \\ / __|| __|"EOC);
	move((e->winsize.ws_col - W_TITLE) / 2 , y++);
	ft_dprintf(2, CYAN"| |  | |_         \\__ \\|  __/| ||  __/| (__ | |_ "EOC);
	move((e->winsize.ws_col - W_TITLE) / 2 , y++);
	ft_dprintf(2,
			L_BLUE"|_|   \\__|        |___/ \\___||_| \\___| \\___| \\__|"EOC);
	move((e->winsize.ws_col - W_TITLE) / 2 , y++);
	ft_dprintf(2, BLUE"           ______                                "EOC);
	move((e->winsize.ws_col - W_TITLE) / 2 , y++);
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
	int title_rendered;

	clear_all();
	if (e->arg_max_len + e->center.w_border + 1 > e->winsize.ws_col)
		return (render_insufficient_width(e));
	else
	{
		title_rendered = 0;
		if (e->winsize.ws_col > W_TITLE && e->winsize.ws_row > H_TITLE)
		{
			render_title(e);
			title_rendered = 1;
		}
		render_args(e, title_rendered);
	}
	return (0);
}

void	update_center(t_env *e)
{
	e->center.nb_columns = 	ft_clamp(1, (e->winsize.ws_col) /
			((e->arg_max_len + 1)), e->nb_args);
	if (e->center.nb_columns > 1)
		e->center.arg_x_padding = (double)(e->winsize.ws_col -
				((e->center.nb_columns * e->arg_max_len))) /(double)
			(e->center.nb_columns - 1);
	if (e->center.nb_columns > 0)
		e->center.nb_lines = ft_round((double)e->nb_args /
				(double)e->center.nb_columns);
	int c = max_col_drawn(e);
	e->center.w_border = ft_max(0, (e->winsize.ws_col - ((c * e->arg_max_len) + (c) * e->center.arg_x_padding)) / 2.0);
}

void	handle_kill(int signal)
{
	(void)signal;
	ft_dprintf(2, "HANDLE SIGKILL\n");
	reset_shell();
	exit(0);
}

void	handle_resize(int signal)
{
	int win_width;

	(void)signal;
	win_width = g_env.winsize.ws_col;
	ioctl(0, TIOCGWINSZ, &g_env.winsize);
	if (win_width < g_env.winsize.ws_col)
		g_env.decreasing = 0;
	else if (win_width > g_env.winsize.ws_col)
		g_env.decreasing = 1;
	update_center(&g_env);
	render(&g_env);
}
