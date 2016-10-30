/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 18:07:51 by nle-bret          #+#    #+#             */
/*   Updated: 2016/10/30 18:07:52 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ls_print_folder_and_newline(t_app *app, t_entity *e)
{
	if (app->nb_param > 1 || app->opt & OPT_R)
	{
		if (app->token == 1)
		{
			ft_putchar('\n');
			if (app->opt & OPT_R && app->nb_dir_param == 1)
			{
				ft_putstr(e->rpath);
				ft_putendl(":");
			}
		}
		else
			app->token = 1;
		if (!(app->opt & OPT_R) || app->nb_dir_param > 1)
		{
			ft_putstr(e->rpath);
			ft_putendl(":");
		}
	}
}

static void	ls_print_total_and_error(t_app *app, t_entity *e)
{
	if (e->errno_code != 0)
	{
		errno = e->errno_code;
		ls_error_errno(e->name);
		errno = 0;
	}
	if (app->opt & OPT_l && e->errno_code == 0 &&
		ft_lstsize((t_list*)e->child) > 0)
	{
		ft_putstr("total ");
		ft_putnbr(e->ms.total_folder);
		ft_putchar('\n');
	}
}

static void	ls_print_entity_child(t_app *app, t_entity *e)
{
	t_listd		*l;
	t_entity	*e_child;

	l = e->child;
	while (l)
	{
		e_child = (t_entity *)l->content;
		if (app->opt & OPT_l)
			ls_print_line_opt_l(e_child, e->ms);
		else
			ls_print_entity_if_exist(e_child);
		l = l->next;
	}
}

void		ls_print_child(t_app *app, t_entity *e)
{
	t_listd		*l;
	t_entity	*e_child;

	ls_print_folder_and_newline(app, e);
	ls_print_total_and_error(app, e);
	ls_print_entity_child(app, e);
	l = e->child;
	while (l)
	{
		e_child = (t_entity *)l->content;
		if (ft_strcmp(e_child->name, ".") != 0 &&
			ft_strcmp(e_child->name, ".."))
		{
			if (app->opt & OPT_R && S_ISDIR(e_child->file.st_mode))
			{
				ls_set_child(app, e_child,
				ls_get_entity_child(app, e_child->rpath, e_child));
				ls_print_child(app, e_child);
			}
		}
		l = l->next;
	}
}
