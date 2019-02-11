/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 17:50:48 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/11 23:44:32 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <stdlib.h>
# include "libft.h"
# include <fcntl.h>
# include <signal.h>
# include <term.h>
# include <sys/ioctl.h>
# include <stdio.h> //TODEL
# include <termcap.h>

typedef struct		s_arg
{
	char			*name;
	char			selected;
}					t_arg;

typedef struct		s_env
{
	t_dlist			*args;
	t_dlist			*cursor;
	int				arg_max_len;
	struct termios	term;
	struct termios	term_init;
	struct winsize	winsize;
	char			decreasing;
}					t_env;

t_env				g_env;

void				handle_resize(int signal);
int					init_all(t_env *e, int argc, char **argv);
int					clear_all(void);
int					render(t_env *e);
#endif
