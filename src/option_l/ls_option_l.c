/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_option_l.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 17:24:03 by nle-bret          #+#    #+#             */
/*   Updated: 2016/04/26 17:24:05 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_print_adjust_space_left(char *str, int size)
{
	int		i;

	i = ft_strlen(str) - 1;
	while (i < size)
	{
		ft_putchar(' ');
		i++;
	}
	ft_putstr(str);
}

void		ls_print_adjust_space_right(char *str, int size)
{
	int		i;

	i = ft_strlen(str) - 1;
	ft_putstr(str);
	while (i < size)
	{
		ft_putchar(' ');
		i++;
	}
}

void		ls_print_adjust_size(t_entity *e, t_max_size ms)
{
	t_entity_full *e_full;

	e_full = e->entity_full;
	if (e_full->size != NULL)
	{
		ls_print_adjust_space_left(e_full->size, ms.size);
	}
	else
	{
		ls_print_adjust_space_left(e_full->major, 3);
		ft_putchar(',');
		ls_print_adjust_space_left(e_full->minor, 3);
	}
}

void		ls_print_line_opt_l(t_entity *e, t_max_size ms)
{
	t_entity_full *e_full;

	e_full = e->entity_full;
	ft_putstr(e_full->mode);
	ls_print_adjust_space_left(e_full->nb_link, ms.nb_link);
	ft_putchar(' ');
	ls_print_adjust_space_right(e_full->user, ms.user + 1);
	ls_print_adjust_space_right(e_full->group, ms.group - 1);
	ls_print_adjust_size(e, ms);
	ls_print_adjust_space_left(e_full->month, ms.month);
	if (ms.day < 2)
		ms.day = 2;
	ls_print_adjust_space_left(e_full->day, ms.day);
	if (ft_strlen(e_full->hour_year) > 5)
		ft_putchar(' ');
	ls_print_adjust_space_left(e_full->hour_year, 5);
	ft_putchar(' ');
	if (e->link != NULL)
		ls_set_link(e);
	ft_putstr(e->name);
	ft_putchar('\n');
}
