/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 19:50:37 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/05 05:01:00 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_dlist(t_dlist *dlist, void (*print_func)(void *))
{
	t_dlist *ptr;
	int		first;

	ptr = dlist;
	first = 1;
	while ((ptr != dlist && ptr != NULL) || (first && ptr != NULL))
	{
		print_func(ptr->content);
		ptr = ptr->next;
		first = 0;
	}
}
