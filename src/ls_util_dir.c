/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 17:22:34 by nle-bret          #+#    #+#             */
/*   Updated: 2016/04/26 17:22:36 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_readdir(DIR *dir, t_listd **lst, t_app *app, t_entity *parent)
{
	struct dirent	*dp;

	errno = 0;
	while ((dp = readdir(dir)) != NULL)
	{
		if (errno != 0)
			ls_error_errno("Error in ls_readdir ");
		if (dp->d_name[0] != '.' || app->opt & OPT_A)
			ls_push_entity(app, parent, dp->d_name, lst);
	}
}

void	ls_closedir(DIR *dir)
{
	errno = 0;
	closedir(dir);
	if (errno != 0)
		ls_error_errno("Error in ls_closedir ");
}

int		ls_swap(t_listd *a, t_listd *b)
{
	char	*tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
	return (1);
}
