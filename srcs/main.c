/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 17:18:59 by nle-bret          #+#    #+#             */
/*   Updated: 2016/04/26 17:19:01 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	int		i;
	t_app	app;
	int		end_option;

	i = 1;
	end_option = 0;
	ft_bzero(&app, sizeof(t_app));
	if (ac > 1)
	{
		while (i < ac)
		{
			if (av[i][0] == '-' && ft_strlen(av[i]) > 1 && !end_option)
				ls_option(av[i], &app);
			else
			{
				ls_set_file_data(NULL, av[i], &app.lst, &app);
				app.size_lst++;
			}
			if (ft_strcmp(av[i], "--") == 0 || ft_strcmp(av[i], "-") == 0)
				end_option = 1;
			i++;
		}
	}
	if (app.size_lst == 0)
		ls_set_file_data(NULL, ".", &app.lst, &app);
	ls_sort_param(&app, &app.lst);
	ls_print_result(&app);
	//sleep(5);
	return (0);
}
