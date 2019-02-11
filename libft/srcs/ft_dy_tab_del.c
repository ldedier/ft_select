/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dy_tab_del.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:38:21 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/14 15:38:28 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dy_tab_del(t_dy_tab *d_tab)
{
	int i;

	i = 0;
	while ((size_t)i < d_tab->current_size)
	{
		free(d_tab->tab[i]);
		i++;
	}
	free(d_tab->tab);
	free(d_tab);
}