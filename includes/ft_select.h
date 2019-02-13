/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 17:50:48 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/13 13:32:56 by ldedier          ###   ########.fr       */
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

# define W_TITLE		50
# define H_TITLE		8
# define TITLE_TOP		0
# define TITLE_BOTTOM	2

# define NO_PRINT		1
# define PRINT			2

typedef struct		s_arg
{
	char			*name;
	char			selected;
}					t_arg;

typedef struct		s_center
{
	int				w_border;
	int				arg_x_padding;
	int				arg_y_padding;
	int				nb_lines;
	int				nb_columns;
}					t_center;

typedef struct		s_env
{
	t_dlist			*args;
	t_dlist			*cursor;
	int				nb_args;
	int				arg_max_len;
	t_center		center;
	struct termios	term;
	struct termios	term_init;
	struct winsize	winsize;
	char			decreasing;
}					t_env;

t_env				g_env;

void				handle_resize(int signal);
void				handle_kill(int signal);
int					init_all(t_env *e, int argc, char **argv);
int					clear_all(void);
void				move(int x, int y);
int					render(t_env *e);
int					render_arg_ptr(t_env *e, t_dlist *to_render);
int					putchar_int(int i);
int					reset_shell(void);
void				update_center(t_env *e);
int					process_keys(t_env *e);
#endif
