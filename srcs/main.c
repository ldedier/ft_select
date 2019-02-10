/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 02:34:27 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/10 21:38:01 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	print_dlist(t_dlist *elem)
{
	ft_printf("%s\n", (char *)elem->content);
}

void	test()
{
	t_dlist	*dlist;
	int		i;
	char	*str;

	dlist = NULL;
	i = 0;
	while (i < 10)
	{
		str = ft_itoa(i);
		ft_printf("before adding LENGTH: %d\n", ft_dlstlength(dlist));
		ft_add_to_dlist_ptr_back(&dlist, str, sizeof(str));
		ft_printf("after adding LENGTH: %d\n", ft_dlstlength(dlist));
		i++;
	}
	ft_dlstiter(dlist, print_dlist);
	ft_printf("LENGTH: %d\n", ft_dlstlength(dlist));
	ft_dlstdel(&dlist);
	ft_printf("LENGTH: %d\n", ft_dlstlength(dlist));
	ft_dlstiter(dlist, print_dlist);
	ft_printf("LENGTH: %d\n", ft_dlstlength(dlist));
}

int		main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	test();
	return (0);
}
