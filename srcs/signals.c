/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 19:59:05 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/17 20:31:35 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	handle_stp()
{
	reset_shell();
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, "\x1a");
}

void	handle_cont()
{
	int		win_width;

	set_shell();
	win_width = g_env.winsize.ws_col;
	ioctl(0, TIOCGWINSZ, &g_env.winsize);
	if (win_width < g_env.winsize.ws_col)
		g_env.decreasing = 0;
	else if (win_width > g_env.winsize.ws_col)
		g_env.decreasing = 1;
	update_center(&g_env);
	render(&g_env);
}

void	init_signals(void)
{
	signal(SIGWINCH, handle_resize);
	signal(SIGINT, handle_kill);
	signal(SIGHUP, handle_kill);
	signal(SIGTERM, handle_kill);
	signal(SIGABRT, handle_kill);
	signal(SIGALRM, handle_kill);
	signal(SIGQUIT, handle_kill);
	signal(SIGSTOP, handle_kill);
	signal(SIGTSTP, handle_stp);
	signal(SIGCONT, handle_cont);
}

void	handle_kill(int signal)
{
	(void)signal;
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
