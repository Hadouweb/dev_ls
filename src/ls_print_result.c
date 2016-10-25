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

/*static int	ls_next_node_is_folder(t_listd *node)
{
	t_path	*path;

	path = (t_path*)node->content;
	if (S_ISDIR(path->file.st_mode))
		return (1);
	return (0);
}*/

static void	ls_print_without_option(t_app *app)
{
	t_listd	*l;
	t_path	*path;

	//ft_lstd_print(app->lst, ls_debug_print_content, 1);
	l = app->lst;
	while (l)
	{
		path = (t_path*)l->content;
		if (S_ISDIR(path->file.st_mode))
		{
			if (app->token == 1)
				ft_putchar('\n');
			else
				app->token = 1;
			ft_putstr(path->name);
			ft_putendl(":");
			ls_set_folder(app, path->name);
		}
		//else
		//	ft_putendl(path->name);
		l = l->next;
	}
}

static void	ls_print_with_option_l(t_app *app)
{
	t_listd	*l;
	t_path	*path;

	l = app->lst;
	while (l)
	{
		path = (t_path*)l->content;
		if (S_ISDIR(path->file.st_mode))
		{
			ls_print_option_l(app);
			ft_bzero(&app->ms, sizeof(t_max_size));
			ls_set_folder(app, path->name);
			ls_print_option_l(app);
		}
		else
			ls_set_option_l(app, path);
		l = l->next;
	}
	ls_print_option_l(app);
	//ls_debug_max_size(app);
}

void 	ls_print_with_option_R(t_listd *lst, t_app *app)
{
	t_listd	*l;
	t_path	*path;

	//printf("ls_print_with_option_R\n");
	//ft_lstd_print(lst, ls_debug_print_content, 1);
	l = lst;
	while (l)
	{
		path = (t_path*)l->content;
		if (path->name) {
			if (S_ISDIR(path->file.st_mode) && path->parent != NULL) {
				//printf("|parent: %s child: %s\n", path->parent, path->name);
				ft_putchar('\n');
				ft_putstr(path->parent);
				ft_putendl(":");
				ls_set_folder(app, path->parent);
			}
			else if (S_ISDIR(path->file.st_mode)) {
				//printf("LOL\n");
				/*if (app->token == 1)
					ft_putchar('\n');
				else
					app->token = 1;*/
				ls_set_folder(app, path->name);
			}
			//if (l->next && ls_next_node_is_folder(l->next))
			//	ft_putchar('\n');
			path = NULL;
			free(path);
		}
		l = l->next;
	}
}

void		ls_print_result(t_app *app)
{
	if (app->opt & OPT_l)
		ls_print_with_option_l(app);
	else if (app->opt & OPT_R)
		ls_print_with_option_R(app->lst, app);
	else if (app->opt & OPT_a)
		ls_print_without_option(app);
	else if (app->opt & OPT_r)
		printf("option r\n");
	else
		ls_print_without_option(app);
}
