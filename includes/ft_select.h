/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 17:50:48 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/13 20:32:40 by ldedier          ###   ########.fr       */
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
# include <sys/stat.h>
# include <stdio.h> //TODEL
# include <termcap.h>

# define W_TITLE		50
# define H_TITLE		8
# define TITLE_TOP		0
# define TITLE_BOTTOM	2
# define PREFIX_STR		"● "
# define NO_PRINT		1
# define PRINT			2
# define MAX_COLOR_LEN	100
# define DIR_COL		L_CYAN BOLD
# define CHR_COL		BLUE
# define BLK_COL		L_BLUE
# define FIFO_COL		YELLOW
# define SOCK_COL		L_MAGENTA

typedef struct		s_arg
{
	char			*name;
	char			selected;
	char			color[MAX_COLOR_LEN];
}					t_arg;

typedef struct		s_xy
{
	int				x;
	int				y;
}					t_xy;

typedef struct		s_center
{
	int				w_border;
	int				arg_x_padding;
	int				arg_y_padding;
	int				nb_lines;
	int				nb_columns;
	int				true_nb_cols;
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
int					process_render_arg_ptr(t_env *e, int title_rendered,
						t_dlist *to_render);
int					render_arg_ptr(t_env *e, t_dlist *to_render);
int					putchar_int(int i);
int					reset_shell(void);
void				update_center(t_env *e);
int					process_keys(t_env *e);
int					can_render(t_env *e);
int					render_arg(t_env *e, t_dlist *ptr, int x, int y);
int					render_insufficient_width(t_env *e);
int					render_insufficient_height(t_env *e);
int					render_args(t_env *e, int title_rendered);
int					can_render_title(t_env *e);
int					dist_to_start(t_dlist *ptr, t_env *e);
int					dist_to_start_inv(t_dlist *ptr, t_env *e);
int					process_left(t_env *e);
int					process_right(t_env *e);
void				process_shift_all(t_env *e);
void				suppr_current(t_env *e, int *stop);
void				select_current(t_env *e);
void				init_signals(void);
#endif
