/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 19:59:05 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/05 05:33:51 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	handle_stp(int sgl)
{
	(void)sgl;
	reset_shell();
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, "\x1a");
}

void	handle_cont(int sgl)
{
	int		win_width;

	(void)sgl;
	signal(SIGTSTP, handle_stp);
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
	signal(SIGINT, handle_kill);
	signal(SIGHUP, handle_kill);
	signal(SIGTERM, handle_kill);
	signal(SIGABRT, handle_kill);
	signal(SIGILL, handle_kill);
	signal(SIGTRAP, handle_kill);
	signal(SIGEMT, handle_kill);
	signal(SIGFPE, handle_kill);
	signal(SIGALRM, handle_kill);
	signal(SIGQUIT, handle_kill);
	signal(SIGKILL, handle_kill);
	signal(SIGBUS, handle_kill);
	signal(SIGSEGV, handle_kill);
	signal(SIGSYS, handle_kill);
	signal(SIGTTIN, handle_kill);
	signal(SIGTTOU, handle_kill);
	signal(SIGXCPU, handle_kill);
	signal(SIGXFSZ, handle_kill);
	signal(SIGVTALRM, handle_kill);
	signal(SIGPROF, handle_kill);
	signal(SIGUSR1, handle_kill);
	signal(SIGUSR2, handle_kill);
	signal(SIGTSTP, handle_stp);
	signal(SIGCONT, handle_cont);
	signal(SIGWINCH, handle_resize);
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
