/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse_option.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 17:20:53 by nle-bret          #+#    #+#             */
/*   Updated: 2016/04/26 17:20:55 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ls_check_option(char *opt)
{
	int		i;

	i = 1;
	if (ft_strcmp(opt, "--") == 0)
		return ;
	while (opt[i])
	{
		if (opt[i] != 'l' && opt[i] != 'R' && opt[i] != 'a' && opt[i] != 't'
			&& opt[i] != 'r' && opt[i] != '1')
		{
			ft_putstr_fd("ls: illegal option -- ", 2);
			ft_putchar_fd(opt[i], 2);
			ft_putendl_fd("\nusage: ft_ls [-lRatr] [file ...]", 2);
			exit(1);
		}
		i++;
	}
}

void		ls_option(char *opt, t_app *app)
{
	int		i;

	i = 1;
	ls_check_option(opt);
	while (opt[i])
	{
		if (opt[i] == 'l')
			app->opt |= OPT_L;
		if (opt[i] == 'R')
			app->opt |= OPT_R;
		if (opt[i] == 'a')
			app->opt |= OPT_A;
		if (opt[i] == 't')
			app->opt |= OPT_T;
		if (opt[i] == 'r')
			app->opt |= OPT_RMIN;
		i++;
	}
}
