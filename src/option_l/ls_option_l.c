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

void		ls_clear_node_prepared(t_listd *node)
{
	t_prepa		*p;

	p = (t_prepa*)node->content;
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
}

void		ls_print_adjust_size(t_prepa *p, t_app *app)
{
	if (p->size != NULL)
	{
		ls_print_adjust_space_left(p->size, app->ms.size);
	}
	else
	{
		ls_print_adjust_space_left(p->major, 3);
		ft_putchar(',');
		ls_print_adjust_space_left(p->minor, 3);
	}
}

void		ls_print_option_l(t_app *app)
{
	t_listd	*l;
	t_listd	*tmp;

	l = app->prepa;
	while (l)
	{
		t_prepa		*p;

		p = (t_prepa*)l->content;
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
}
