/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_set_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 17:20:31 by nle-bret          #+#    #+#             */
/*   Updated: 2016/04/26 17:20:33 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_set_child(t_app *app, t_entity *e, t_listd *lst_child)
{
	t_listd		*l;
	t_entity	*e_child;

	e->child = lst_child;
	l = e->child;
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
	if (S_ISDIR(e->file.st_mode))
	{
		app->nb_dir_param++;
		ls_set_child(app, e, ls_get_entity_child(app, e->name, e));
	}
	else
	{
		if (app->opt & OPT_l)
			ls_set_option_l(e, &app->root_ms);
	}
}

void		ls_push_entity(t_app *app, t_entity *parent,
	char *name, t_listd **lst)
{
	t_entity	*e;

	if (ft_strcmp(name, "\0") == 0)
	{
		ft_putstr_fd("ls: fts_open: No such file or directory\n", 2);
		exit(1);
	}
	if ((e = (t_entity*)ft_memalloc(sizeof(t_entity))) == NULL)
		ls_error("Error: malloc");
	e->name = ft_strdup(name);
	if (parent == NULL)
	{
		e->e_parent = NULL;
		e->rpath = ft_strdup(e->name);
	}
	else
	{
		e->e_parent = parent;
		e->rpath = ft_strjoin_free_s1(ft_strjoin(parent->rpath, "/"), e->name);
	}
	ls_set_filestat(app, e);
	ls_push_after_sort(lst, e, app);
	free(e);
}

static char	*ls_update_link(t_entity *e)
{
	char	*rpath;
	char	*str;
	int		i;
	int		find;

	rpath = e->rpath;
	i = ft_strlen(rpath) - 1;
	find = 0;
	while (rpath[i])
	{
		if (rpath[i] == '/' && (find = 1))
			break ;
		i--;
	}
	if (i > 0)
		str = ft_strjoin_free_s1(ft_strndup(rpath, i + 1), e->link);
	else if (find)
		str = ft_strjoin("/", e->link);
	else
		str = e->link;
	if (opendir(str) != NULL)
		return (str);
	return (e->rpath);
}

int			ls_set_filestat(t_app *app, t_entity *e)
{
	int		ret;
	char	*path;

	path = e->rpath;
	e->link = ls_get_link(path);
	errno = 0;
	if (e->link != NULL)
	{
		if (!(app->opt & OPT_l) && (!(app->opt & OPT_R) ||
			app->param_mode == 1))
			path = ls_update_link(e);
		errno = 0;
		ret = lstat(path, &e->file);
	}
	else
		ret = stat(path, &e->file);
	if (errno != 0)
	{
		e->errno_code = errno;
		e->name = path;
	}
	if (e->e_parent != NULL)
		e->e_parent->ms.total_folder += e->file.st_blocks;
	return (ret);
}
