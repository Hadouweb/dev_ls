/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print2_l.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 17:28:20 by nle-bret          #+#    #+#             */
/*   Updated: 2016/04/26 17:28:21 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_prepare_nb_link(t_prepa *p, int st_nlink, t_app *app)
{
	int		size;
	
	p->nb_link = ft_itoa(st_nlink);
	if ((size = ft_strlen(p->nb_link)) > app->ms.nb_link)
		app->ms.nb_link = size;
}

void		ls_print_path(char *path, char *link)
{
	ft_putchar(' ');
	ft_putstr(path);
	if (link != NULL)
	{
		ft_putstr(" -> ");
		ft_putstr(link);
	}
}
