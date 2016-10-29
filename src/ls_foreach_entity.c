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

void		ls_print_entity_if_exist(t_app *app, t_entity *e)
{
	if (app)
		;
	if (e->errno_code != 0)
	{
		ft_putstr_fd("ls: ", 2);
		errno = e->errno_code;
		perror(e->name);
		errno = 0;
	} else {
		ft_putendl(e->name);
	}
}

void		ls_print_opt_l(t_app *app, t_entity *e)
{
	if (S_ISDIR(e->file.st_mode)) {
		if (app->nb_param > 1) {
			ft_putstr(e->name);
			ft_putendl(":");
		}
	} else
		ls_print_line_opt_l(e, app->root_ms);
}

void		ls_print_no_option(t_app *app, t_entity *e)
{
	if (S_ISDIR(e->file.st_mode)) {
		if (app->nb_param > 1) {
			ft_putstr(e->name);
			ft_putendl(":");
		}
		ls_print_child(app, e);
	} else
		ls_print_entity_if_exist(app, e);
}

void		ls_print_child(t_app *app, t_entity *e)
{
	t_listd 	*l;
	t_entity	*e_child;

	l = e->child;
	//ls_debug_max_size(e->ms);
	//printf("print child Parent: %s and child:\n", e->name);
	//ft_lstd_print(e->child, ls_debug_print_content, 0);
	//printf("___________\n");
	if (app->nb_param > 1 || app->opt & OPT_R) {
		if (app->token == 1) {
			ft_putchar('\n');
			if (app->opt & OPT_R && app->nb_dir_param == 1) {
				ft_putstr(e->rpath);
				ft_putendl(":");
			}
		} else
			app->token = 1;

		if (!(app->opt & OPT_R) || app->nb_dir_param > 1) {
			ft_putstr(e->rpath);
			ft_putendl(":");
		}
	}
	if (e->errno_code != 0)
	{
		errno = e->errno_code;
		ls_error_errno(e->name);
		errno = 0;
	}
	if (app->opt & OPT_l && e->errno_code == 0) {
		ft_putstr("total ");
		ft_putnbr(e->ms.total_folder);
		ft_putchar('\n');
	}

	while (l)
	{
		e_child = (t_entity *) l->content;
		if (app->opt & OPT_l)
			ls_print_line_opt_l(e_child, e->ms);
		else
			ls_print_entity_if_exist(app, e_child);
		l = l->next;
	}
	l = e->child;
	while (l) {
		e_child = (t_entity *) l->content;
		if (ft_strcmp(e_child->name, ".") != 0 && ft_strcmp(e_child->name, "..")) {
			if (app->opt & OPT_R && S_ISDIR(e_child->file.st_mode)) {
				//ls_push_stack(app, e_child);
				ls_set_child(app, e_child,
							 ls_get_entity_child(app, e_child->rpath, e_child));
				ls_print_child(app, e_child);
			}
		}
		l = l->next;
	}
}

void		ls_print_entity(t_app *app, t_entity *e)
{

	if (S_ISDIR(e->file.st_mode)) {
		ls_print_child(app, e);
	}
	else {
		if (app->opt & OPT_l && e->errno_code == 0)
			ls_print_opt_l(app, e);
		else
			ls_print_no_option(app, e);
	}
	app->token = 1;
}

void		ls_set_child(t_app *app, t_entity *e, t_listd *lst_child)
{
	t_listd 	*l;
	t_entity	*e_child;

	e->child = lst_child;
	l = e->child;
	//printf("set child Parent: %s and child:\n", e->name);
	//ft_lstd_print(e->child, ls_debug_print_content, 0);
	//printf("___________\n");
	while (l)
	{
		e_child = (t_entity*)l->content;
		if (app->opt & OPT_l)
			ls_set_option_l(e_child, &e->ms);
		l = l->next;
	}
}

void		ls_set_entity_param(t_app *app, t_entity *e)
{
	if (S_ISDIR(e->file.st_mode)) {
		app->nb_dir_param++;
		ls_set_child(app, e, ls_get_entity_child(app, e->name, e));
	} else {
		if (app->opt & OPT_l)
			ls_set_option_l(e, &app->root_ms);
	}
}

void		ls_foreach_entity(t_app *app)
{
	t_listd		*l;
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
		l = l->next;
	}
}

