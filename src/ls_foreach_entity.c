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

/*static void	ls_print_without_option(t_app *app)
{
	t_listd	*l;
	t_entity	*path;

	//ft_lstd_print(app->lst, ls_debug_print_content, 1);
	l = app->lst;
	while (l)
	{
		path = (t_entity*)l->content;
		ls_print_line(app, path);
		ls_set_stack(app, path);
		l = l->next;
	}
}
*/
/*static void	ls_print_with_option_l(t_app *app)
{
	t_listd	*l;
	t_entity	*path;
	t_listd	*tmp;

	l = app->lst;
	while (l)
	{
		path = (t_entity*)l->content;
		ls_get_entity_dir(app, path->name);
		l = l->next;
	}
	ls_print_option_l(app);
	l = app->stack;
	while (l)
	{
		//ft_lstd_print(l, ls_debug_print_content, 1);
		path = (t_entity*)l->content;
		ls_get_entity_dir(app, path->name);
		tmp = l;
		l = l->next;
		path = NULL;
		tmp = NULL;
		free(path);
		free(tmp);
		ls_print_option_l(app);
	}
	l = NULL;
	//ls_debug_max_size(app);
}
*/
/*void	ls_print_line(t_app *app, t_entity *path)
{
	if (app->token == 1)
		ft_putchar('\n');
	else
		app->token = 1;
	if (S_ISDIR(path->file.st_mode))
	{
		if (!(path->parent == NULL && app->size_lst <= 1)) {
			ft_putstr(path->name);
			ft_putendl(":");
		}
	} else {
		ft_putendl(path->name);
	}
}*/
/*void	ls_set_stack(t_app *app, t_entity *path)
{
	if (S_ISDIR(path->file.st_mode))
	{
		if (path->parent)
			ls_get_entity_dir(app, path->parent);
		else
			ls_get_entity_dir(app, path->name);
	}
}*/
/*void 	ls_print_with_option_R(t_app *app)
{
	t_listd		*l;
	t_listd		*tmp;
	t_entity		*path;

	l = app->stack;
	while (l)
	{
		//ft_lstd_print(l, ls_debug_print_content, 1);
		path = (t_entity*)l->content;
		ls_print_line(app, path);
		ls_set_stack(app, path);
		tmp = l;
		l = l->next;
		path = NULL;
		tmp = NULL;
		free(path);
		free(tmp);
	}
	l = NULL;
	free(l);
}*/

void		ls_set_child(t_entity *e, t_listd *lst_child)
{
	t_listd 	*l;

	e->child = lst_child;
	l = e->child;
	while (l)
	{
		ls_set_option_l((t_entity*)l->content);
		l = l->next;
	}
}

void		ls_exec_flag(t_app *app, t_entity *e)
{
	//ft_lstd_print(app->entity, ls_debug_print_content, 1);
	if (app->opt & OPT_l) {
		if (S_ISDIR(e->file.st_mode))
			ls_set_child(e, ls_get_entity_dir(app, e->name));
		else
			ls_set_option_l(e);
	}
}

void		ls_print_child(t_app *app, t_entity *e)
{
	t_listd 	*l;

	l = e->child;
	while (l)
	{
		if (app->opt & OPT_l) {
			ls_set_option_l((t_entity *) l->content);
			ls_print_line_opt_l((t_entity *) l->content);
		}
		l = l->next;
	}
}

void		ls_print_entity_root(t_app *app, t_entity *e)
{
	if (app->opt & OPT_l) {
		if (S_ISDIR(e->file.st_mode)) {
			ft_putstr("total ");
			ft_putnbr(e->ms.total_folder);
			ft_putchar('\n');
			ls_print_child(app, e);
		} else
			ls_print_line_opt_l(e);
	}
	//ls_debug_max_size(app);
}

void		ls_foreach_entity(t_app *app)
{
	t_listd		*l;
	t_entity	*e;

	l = app->entity;
	while (l)
	{
		e = (t_entity*)l->content;
		ls_exec_flag(app, e);
		l = l->next;
	}
	//ft_lstd_print(app->entity, ls_debug_print_entity_full, 0);

	l = app->entity;
	while (l)
	{
		e = (t_entity*)l->content;
		ls_print_entity_root(app, e);
		l = l->next;
	}
}

