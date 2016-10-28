/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 17:19:51 by nle-bret          #+#    #+#             */
/*   Updated: 2016/04/26 17:19:52 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ls_swap(t_listd *a, t_listd *b)
{
	char	*tmp;

	//ls_debug_swap(a, b);
	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
	return (1);
}

static int	ls_lstcmp(t_listd *a, t_listd *b, t_app *app)
{
	t_entity			*path_a;
	t_entity			*path_b;

	if (app)
		;
	path_a = (t_entity*)a->content;
	path_b = (t_entity*)b->content;

	return (ft_strcmp(path_a->name, path_b->name));
}

static int	ls_cmp_file_type(t_listd *a, t_listd *b)
{
	t_entity	*path_a;
	t_entity	*path_b;

	path_a = (t_entity*)a->content;
	path_b = (t_entity*)b->content;
	if (S_ISDIR(path_a->file.st_mode) && !S_ISDIR(path_b->file.st_mode))
		return (1);
	else if (path_a->errno_code == 0 && path_b->errno_code != 0)
		return (1);
	return (0);
}

void		ls_sort_entity_param(t_app *app)
{
	t_listd *l;
	int 	swap;

	l = app->entity;

	swap = 1;
	while (swap)
	{
		l = app->entity;
		swap = 0;
		while (l && l->next)
		{
			if (ls_cmp_file_type(l, l->next) == 1)
				swap = ls_swap(l, l->next);
			l = l->next;
		}
	}
}

void		ls_sort_entity(t_app *app, t_listd **lst)
{
	t_listd	*l;
	int		swap;
	int		is_dir;

	swap = 1;
	while (swap)
	{
		swap = 0;
		l = *lst;
		is_dir = 0;
		while (l && l->next)
		{
			is_dir = ls_cmp_file_type(l, l->next);
			if (is_dir == 1)
				swap = ls_swap(l, l->next);
			else if (ls_lstcmp(l, l->next, app) > 0 && is_dir == -1)
				swap = ls_swap(l, l->next);
			l = l->next;
		}
	}
}

void	ls_push_after_sort(t_listd **lst, t_entity *e, t_app *app)
{
	t_listd *node;

	node = NULL;
	if (app->opt & OPT_t) {
		node = ls_get_node_cmp_time(lst, e);
	}
	else {
		node = ls_get_node_cmp(lst, e);
	}
	if (node != NULL)
	{
		ft_lstd_pushbefore_node(lst, node, ft_lstd_new((void *) e, sizeof(t_entity)));
	} else {
		ft_lstd_pushback(lst, (void *) e, sizeof(t_entity));
	}
}
