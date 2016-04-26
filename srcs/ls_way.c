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
			ls_print_folder(app, path->name);
		else
			ft_putendl(path->name);
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
			ls_print_folder(app, path->name);
		else
			ls_print_option_l(path->name);
		l = l->next;
	}
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
