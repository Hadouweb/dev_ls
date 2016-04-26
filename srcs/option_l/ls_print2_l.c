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

void		ls_print_physical_link(int st_nlink)
{
	ft_putchar(' ');
	ft_putnbr(st_nlink);
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
