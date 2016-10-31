/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_cmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 17:36:21 by nle-bret          #+#    #+#             */
/*   Updated: 2016/10/30 17:36:23 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static __uint128_t	ls_get_uint128(t_entity *e)
{
	return ((__uint128_t)e->file.st_mtimespec.tv_sec
					<< 64 | e->file.st_mtimespec.tv_nsec);
}

t_listd				*ls_get_node_cmp_time(t_app *app, t_listd **lst,
	t_entity *e)
{
	__uint128_t		t1;
	__uint128_t		t2;
	t_listd			*l;
	t_entity		*e_cmp;
	int				cmp;

	t1 = ls_get_uint128(e);
	l = *lst;
	cmp = 0;
	while (l)
	{
		e_cmp = (t_entity*)l->content;
		t2 = ls_get_uint128(e_cmp);
		if (app->opt & OPT_r && t1 < t2)
			return (l);
		else if (!(app->opt & OPT_r) && t1 > t2)
			return (l);
		if (t2 - t1 == 0 && app->opt & OPT_r)
			cmp = ft_strcmp(e_cmp->name, e->name);
		else if (t2 - t1 == 0)
			cmp = ft_strcmp(e->name, e_cmp->name);
		if (cmp < 0)
			return (l);
		l = l->next;
	}
	return (NULL);
}

t_listd				*ls_get_node_cmp(t_app *app, t_listd **lst, t_entity *e)
{
	t_listd			*l;
	t_entity		*e_cmp;
	int				cmp;

	l = *lst;
	while (l)
	{
		e_cmp = (t_entity*)l->content;
		if (app->opt & OPT_r)
			cmp = ft_strcmp(e_cmp->name, e->name);
		else
			cmp = ft_strcmp(e->name, e_cmp->name);
		if (cmp < 0)
			return (l);
		l = l->next;
	}
	return (NULL);
}
