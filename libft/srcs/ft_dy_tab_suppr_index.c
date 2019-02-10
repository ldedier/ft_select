/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dy_tab_suppr_index.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:42:30 by ldedier           #+#    #+#             */
/*   Updated: 2019/01/14 15:49:18 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dy_tab_suppr_index(t_dy_tab *d_tab, size_t index)
{
	free(d_tab->tab[index]);
	ft_dy_tab_suppr_index_ptr(d_tab, index);
}
