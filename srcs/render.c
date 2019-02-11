/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:58:32 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/12 00:02:25 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_print_arg(t_dlist *dlist)
{
	t_arg *arg;

	arg = (t_arg *)(dlist->content);
	ft_dprintf(2, "%s\n", arg->name);
}
int		render(t_env *e)
{
	(void)e;
	clear_all();
	if (e->arg_max_len > e->winsize.ws_col)
	{
		if (e->winsize.ws_col >= 54)
			ft_dprintf(2,
				"terminal width is not enough to display all arguments");
		else if (e->decreasing)
		{
			if (e->winsize.ws_col >= 39)
				ft_dprintf(2, "going that way won't make things better");
			else if (e->winsize.ws_col >= 22)
				ft_dprintf(2, "this is the wrong way!");
			else if (e->winsize.ws_col >= 15)
				ft_dprintf(2, "what r u doing?");
			if (e->winsize.ws_col >= 8)
				ft_dprintf(2, "really ?");
			else if (e->winsize.ws_col >= 3)
				ft_dprintf(2, "ಠ_ಠ");
			else if(e->winsize.ws_col >= 1)
				ft_dprintf(2, "益");
		}
		else
		{
			if (e->winsize.ws_col >= 15 && e->arg_max_len - e->winsize.ws_col < 5)
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
	}
	else
		ft_dlstiter(e->args, ft_print_arg);
	return (0);
}

void	handle_resize(int signal)
{
	int win_width;

	(void)signal;
	win_width = g_env.winsize.ws_col;
	ioctl(0, TIOCGWINSZ, &g_env.winsize);
	render(&g_env);
	if (win_width < g_env.winsize.ws_col)
		g_env.decreasing = 0;
	else if (win_width > g_env.winsize.ws_col)
		g_env.decreasing = 1;
	//ft_printf("%d:%d\n", g_winsize.ws_row,g_winsize.ws_col);
}
