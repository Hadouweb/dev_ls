/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_way.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 17:19:34 by nle-bret          #+#    #+#             */
/*   Updated: 2016/04/26 17:19:36 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_print_entity_if_exist(t_entity *e)
{
	if (e->errno_code != 0)
	{
		ft_putstr_fd("ls: ", 2);
		errno = e->errno_code;
		perror(e->name);
		errno = 0;
	}
	else
		ft_putendl(e->name);
}

void		ls_print_opt_l(t_app *app, t_entity *e)
{
	if (S_ISDIR(e->file.st_mode))
	{
		if (app->nb_param > 1)
		{
			ft_putstr(e->name);
			ft_putendl(":");
		}
	}
	else
		ls_print_line_opt_l(e, app->root_ms);
}

void		ls_print_no_option(t_app *app, t_entity *e)
{
	if (S_ISDIR(e->file.st_mode))
	{
		if (app->nb_param > 1)
		{
			ft_putstr(e->name);
			ft_putendl(":");
		}
		ls_print_child(app, e);
	}
	else
		ls_print_entity_if_exist(e);
}

void		ls_print_entity(t_app *app, t_entity *e)
{
	if (S_ISDIR(e->file.st_mode))
		ls_print_child(app, e);
	else
	{
		if (app->opt & OPT_L && e->errno_code == 0)
			ls_print_opt_l(app, e);
		else
			ls_print_no_option(app, e);
	}
	if (e->errno_code == 0)
		app->token = 1;
}

void		ls_foreach_entity(t_app *app)
{
	t_listd		*l;
	t_listd		*tmp;
	t_entity	*e;

	l = app->entity;
	while (l)
	{
		e = (t_entity*)l->content;
		ls_set_entity_param(app, e);
		l = l->next;
	}
	l = app->entity;
	ls_sort_entity_param(app);
	while (l)
	{
		e = (t_entity*)l->content;
		ls_print_entity(app, e);
		ls_free_entity(e);
		tmp = l;
		l = l->next;
		free(tmp);
	}
}
