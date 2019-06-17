/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:55:04 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/17 20:30:01 by ldedier          ###   ########.fr       */
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

void	populate_color(struct stat st, t_arg *res)
{
	if (S_ISREG(st.st_mode) && st.st_mode & S_IXUSR)
		ft_strcpy(res->color, RED);
	else if (S_ISDIR(st.st_mode))
		ft_strcpy(res->color, DIR_COL);
	else if (S_ISLNK(st.st_mode))
		ft_strcpy(res->color, MAGENTA);
	else if (S_ISSOCK(st.st_mode))
		ft_strcpy(res->color, SOCK_COL);
	else if (S_ISFIFO(st.st_mode))
		ft_strcpy(res->color, FIFO_COL);
	else if (S_ISBLK(st.st_mode))
		ft_strcpy(res->color, BLK_COL);
	else if (S_ISCHR(st.st_mode))
		ft_strcpy(res->color, CHR_COL);
	else
		ft_strcpy(res->color, BOLD);
}

t_arg	*new_arg(char *name)
{
	t_arg		*res;
	struct stat	st;

	if (!(res = (t_arg *)malloc(sizeof(t_arg))))
		return (NULL);
	res->name = name;
	res->selected = 0;
	ft_bzero(res->color, MAX_COLOR_LEN);
	if (lstat(res->name, &st) != -1)
		populate_color(st, res);
	return (res);
}

int		init_args(t_env *e, int argc, char **argv)
{
	int		i;
	t_arg	*arg;
	int		len;

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
		if (e->arg_max_len < (len = ft_strlen(arg->name) +
					ft_strlen(PREFIX_STR)))
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
	e->term.c_lflag &= ~(ICANON);
	e->term.c_lflag &= ~(ECHO);
	e->term.c_lflag |= ISIG;
	e->term.c_cc[VMIN] = 1;
	e->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &e->term) == -1)
		return (-1);
	e->args = NULL;
	if (init_args(e, argc, argv))
		return (1);
	init_signals();
	ioctl(0, TIOCGWINSZ, &g_env.winsize);
	str = tgetstr("ti", NULL);
	tputs(str, 1, putchar_int);
	str = tgetstr("vi", NULL);
	tputs(str, 1, putchar_int);
	return (0);
}
