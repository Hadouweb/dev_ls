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
		ls_set_sub_dir(app, path);
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
		ls_open_folder(app, path->name);
		l = l->next;
	}
	ls_print_option_l(app);
	l = app->sub_dir;
	while (l)
	{
		//ft_lstd_print(l, ls_debug_print_content, 1);
		path = (t_entity*)l->content;
		ls_open_folder(app, path->name);
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
/*void	ls_set_sub_dir(t_app *app, t_entity *path)
{
	if (S_ISDIR(path->file.st_mode))
	{
		if (path->parent)
			ls_open_folder(app, path->parent);
		else
			ls_open_folder(app, path->name);
	}
}*/
/*void 	ls_print_with_option_R(t_app *app)
{
	t_listd		*l;
	t_listd		*tmp;
	t_entity		*path;

	l = app->sub_dir;
	while (l)
	{
		//ft_lstd_print(l, ls_debug_print_content, 1);
		path = (t_entity*)l->content;
		ls_print_line(app, path);
		ls_set_sub_dir(app, path);
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

void		ls_exec_flag(t_app *app, t_entity *path)
{
	//ft_lstd_print(app->param, ls_debug_print_content, 1);
	if (app->opt & OPT_l) {
		ls_set_option_l(app, path);
	}
	//ft_lstd_print(app->prepa, ls_debug_print_entity_full, 1);
}

void		ls_print_data(t_app *app, t_entity *path)
{
	if (app->opt & OPT_l) {

	}
}

void		ls_foreach_param(t_app *app)
{
	t_listd		*l;
	t_entity		*path;

	l = app->param;
	while (l)
	{
		path = (t_entity*)l->content;
		ls_exec_flag(app, path);
		l = l->next;
	}
	l = app->param;
	while (l)
	{
		path = (t_entity*)l->content;
		ls_print_data(app, path);
		l = l->next;
	}
}

