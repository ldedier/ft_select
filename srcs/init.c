/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:55:04 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/13 00:21:09 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		init_terminal_data(void)
{
	char	*termtype;
	int		success;

	termtype = getenv("TERM");
	if (termtype == 0)
	{
		ft_dprintf(2, "Specify a terminal type with 'setenv TERM'\n");
		return (1);
	}
	success = tgetent(NULL, termtype);
	if (success < 0)
	{
		ft_dprintf(2, "Could not access the termcap data base\n");
		return (1);
	}
	if (success == 0)
	{
		ft_dprintf(2, "Terminal type `%s' is not defined\n", termtype);
		return (1);
	}
	return (0);
}

t_arg	*new_arg(char *name)
{
	t_arg *res;

	if (!(res = (t_arg *)malloc(sizeof(t_arg))))
		return (NULL);
	res->name = name;
	res->selected = 0;
	return (res);
}

int		init_args(t_env *e, int argc, char **argv)
{
	int		i;
	t_arg	*arg;
	int len;

	e->args = NULL;
	e->nb_args = 0;
	i = 1;
	e->arg_max_len = -1;
	while (i < argc)
	{
		if (!(arg = new_arg(argv[i])))
			return (1);
		if (ft_add_to_dlist_ptr_back(&e->args, arg, sizeof(t_arg)))
		{
			free(arg);
			return (1);
		}
		if (e->arg_max_len < (len = ft_strlen(arg->name)))
			e->arg_max_len = len;
		e->nb_args++;
		i++;
	}
	e->cursor = e->args;
	e->decreasing = 0;
	return (0);
}

int		init_all(t_env *e, int argc, char **argv)
{
	char	*str;

	if (init_terminal_data())
		return (1);
	if (tcgetattr(0, &e->term) == -1)
		return (-1);
	if (tcgetattr(0, &e->term_init) == -1)
		return (-1);
	e->term.c_lflag &= ~(ICANON); // Met le terminal en mode non canonique.
	e->term.c_lflag &= ~(ECHO); // les touches tapées ne s'inscriront plus dans le terminal
	e->term.c_lflag |= ISIG; // on recupere les signaux
	e->term.c_cc[VMIN] = 1;
	e->term.c_cc[VTIME] = 0;
	//On applique les changements
	if (tcsetattr(0, TCSADRAIN, &e->term) == -1)
		return (-1);
	if (init_args(e, argc, argv))
		return (1);
	signal(SIGWINCH, handle_resize);
	signal(SIGINT, handle_kill);
	signal(SIGQUIT, handle_kill);
	signal(SIGTSTP, handle_kill);
	signal(SIGSTOP, handle_kill);
	signal(SIGCONT, handle_kill);
	ioctl(0, TIOCGWINSZ, &g_env.winsize);
	str = tgetstr("vi", NULL);
	tputs(str, 1, putchar_int);
	return (0);
}
