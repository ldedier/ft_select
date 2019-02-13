/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_insufficient.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 19:30:21 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/13 19:30:23 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		render_decreasing_width(t_env *e)
{
	if (e->winsize.ws_col >= 39)
		ft_dprintf(2, "going that way won't make things better");
	else if (e->winsize.ws_col >= 22)
		ft_dprintf(2, "this is the wrong way!");
	else if (e->winsize.ws_col >= 15)
		ft_dprintf(2, "what r u doing?");
	else if (e->winsize.ws_col >= 8)
		ft_dprintf(2, "really ?");
	else if (e->winsize.ws_col >= 3)
		ft_dprintf(2, "ಠ_ಠ");
	else if (e->winsize.ws_col >= 1)
		ft_dprintf(2, "益");
	return (0);
}

int		render_insufficient_width(t_env *e)
{
	if (e->winsize.ws_col >= 54 && e->arg_max_len - e->winsize.ws_col >= 5)
		ft_dprintf(2,
				"terminal width is not enough to display all arguments");
	else if (e->decreasing)
		return (render_decreasing_width(e));
	else
	{
		if (e->arg_max_len - e->winsize.ws_col < 5 && e->winsize.ws_col >= 15)
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
	return (0);
}

int		render_insufficient_height(t_env *e)
{
	if (e->winsize.ws_col >= 50)
		ft_dprintf(2,
			"The terminal is too small to display all arguments");
	else if (e->winsize.ws_col >= 27)
		ft_dprintf(2, "This terminal is too small!");
	else if (e->winsize.ws_col >= 18)
		ft_dprintf(2, "This is too small!");
	else if (e->winsize.ws_col >= 10)
		ft_dprintf(2, "please ...");
	else if (e->winsize.ws_col >= 3)
		ft_dprintf(2, "...");
	return (0);
}
