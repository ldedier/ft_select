/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 18:32:07 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/12 19:50:08 by ldedier          ###   ########.fr       */
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
	char *str;

	if (tcsetattr(0, TCSAFLUSH, &g_env.term_init) == -1)
		return (-1);

	str = tgetstr("ve", NULL);
	tputs(str, 1, putchar_int);
	return (0);
}

void	move(int x, int y)
{
	char *res;
	res = tgetstr("cm", NULL);
	tputs(tgoto(res, x, y), 1, putchar_int);
}

int		clear_all(void)
{
	char *res;

	if (!(res = tgetstr("cl", NULL)))
		return (-1);
	tputs(res, 1, putchar_int);
	return (0);
}
