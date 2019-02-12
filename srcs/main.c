/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 02:34:27 by ldedier           #+#    #+#             */
/*   Updated: 2019/02/13 00:21:08 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	print_selection(t_env *e)
{
	t_dlist	*ptr;
	int		first;
	int		first_print;
	t_arg	*arg;

	ptr = e->args;
	first = 1;
	first_print = 1;
	while ((ptr != e->args && ptr != NULL) || (first && ptr != NULL))
	{
		arg = (t_arg *)ptr->content;
		if (arg->selected)
		{
			if (!first_print)
				ft_printf(" %s", arg->name);
			else
				ft_printf("%s", arg->name);
			first_print = 0;
		}
		ptr = ptr->next;
		first = 0;
	}
}


void __attribute__((destructor)) end();
void    end(void) //permet de mieux checker les leaks !
{
//	ft_dprintf(2, "destructor loop\n");
//	while(1);
}

int		main(int argc, char **argv, char **env)
{
	int ret;

	(void)env;
	if (argc < 2)
	{
		ft_dprintf(2, "This program takes at least 1 argument\n");
		return (1);
	}
	if (init_all(&g_env, argc, argv))
		return (1);
	update_center(&g_env);
	render(&g_env);
	ret = process_keys(&g_env);
	clear_all();
	reset_shell();	
	if (ret == PRINT)
		print_selection(&g_env);
	ft_dlstdel(&g_env.args);
	return (0);
}
