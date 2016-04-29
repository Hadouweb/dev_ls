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

static void	ls_print_without_option(t_app *app)
{
	t_list	*l;
	t_path	*path;

	l = app->lst;
	while (l)
	{
		path = (t_path*)l->content;
		if (S_ISDIR(path->file.st_mode))
			ls_set_folder(app, path->name);
		else
			ft_putendl(path->name);
		if (l->next)
			ft_putchar('\n');
		l = l->next;
	}
}

static void	ls_print_with_option_l(t_app *app)
{
	t_list	*l;
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

void		ls_print_result(t_app *app)
{
	if (app->opt & OPT_l)
		ls_print_with_option_l(app);
	else if (app->opt & OPT_R)
		printf("option R\n");
	else if (app->opt & OPT_a)
		printf("option a\n");
	else if (app->opt & OPT_t)
		printf("option t\n");
	else if (app->opt & OPT_r)
		printf("option r\n");
	else
		ls_print_without_option(app);
}
