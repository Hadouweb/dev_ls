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

/*void		ls_clear_node_prepared(t_listd *node)
{
	t_entity_full		*p;

	p = (t_entity_full*)node->content;
	ft_strdel(&p->nb_link);
	if (p->size != NULL)
		ft_strdel(&p->size);
	else
	{
		ft_strdel(&p->major);
		ft_strdel(&p->minor);
	}
	ft_strdel(&p->time);
	ft_strdel(&p->name);
	free(p);
	p = NULL;
	free(node);
	node = NULL;
}*/

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

	//ls_debug_max_size(ms);
	e_full = e->entity_full;
	ft_putstr(e_full->mode);
	ls_print_adjust_space_left(e_full->nb_link, ms.nb_link);
	ft_putchar(' ');
	ls_print_adjust_space_right(e_full->user, ms.user + 1);
	ls_print_adjust_space_right(e_full->group, ms.group - 1);
	ls_print_adjust_size(e, ms);
	ls_print_adjust_space_left(e_full->month, ms.month);
	ls_print_adjust_space_left(e_full->day, ms.day);
	ls_print_adjust_space_left(e_full->hour_year, 5);
	ft_putchar(' ');
	if (e->link != NULL)
		ls_set_link(e);
	ft_putstr(e->name);
	ft_putchar('\n');
}

/*void		ls_print_option_l(t_app *app)
{
	t_listd	*l;
	t_listd	*tmp;

	l = app->prepa;
	while (l)
	{
		t_entity_full		*p;

		p = (t_entity_full*)l->content;
		ft_putstr(p->mode);
		ls_print_adjust_space_left(p->nb_link, app->ms.nb_link);
		ft_putchar(' ');
		ls_print_adjust_space_right(p->user, app->ms.user + 1);
		ls_print_adjust_space_right(p->group, app->ms.group - 1);
		ls_print_adjust_size(p, app);
		ls_print_adjust_space_left(p->time, app->ms.time);
		ft_putchar(' ');
		ft_putstr(p->name);
		ft_putchar('\n');
		tmp = l;
		l = l->next;
		ls_clear_node_prepared(tmp);
	}
	app->prepa = NULL;
}*/
