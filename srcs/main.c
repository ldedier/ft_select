/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 02:34:27 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/11 23:29:13 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		putchar_int(int i)
{
	ft_putchar_fd(i, 2);
	return (0);
}

int		reset_shell(void)
{
	if (tcsetattr(0, TCSAFLUSH, &g_env.term_init) == -1)
		return (-1);
	return (0);
}

/*
void	move(int x, int y)
{
	char *res;
	res = tgetstr("cm", &area);
	tputs(tgoto(res, pos_x, pos_y), 1, ft_putchar);
}
*/

int		clear_all(void)
{
	char *res;

	if (!(res = tgetstr("cl", NULL)))
		return (-1);
	tputs(res, 1, putchar_int);
	return (0);
}

int     process_keys()
{
	char     buffer[3];

	while (1)
	{
		read(0, buffer, 3);
		if (buffer[0] == 27)
			dprintf(2, "C'est une fleche !\n");
		else if (buffer[0] == 4)
		{
			dprintf(2, "Ctlr+d, on quitte !\n");
			return (0);
		}
		else if (buffer[0] == 9)
			ft_dprintf(2, "tab!\n");
		else if (buffer[0] == 12)
			clear_all();
		else
			ft_dprintf(2, "%c", buffer[0]);
	}
	return (0);
}

void	print_params(int argc, char **argv)
{
	int i;

	i = 0;
	while (i < argc)
		ft_dprintf(2, "%s\n", argv[i++]);
}

int		main(int argc, char **argv, char **env)
{
	(void)env;
//	print_params(argc, argv);
	if (argc < 2)
	{
		ft_dprintf(2, "This program takes at least 1 argument\n");
		return (1);
	}
	if (init_all(&g_env, argc, argv))
		return (1);
	render(&g_env);
	process_keys();
	reset_shell();
	ft_dprintf(1, "auteur");
	return (0);
}
