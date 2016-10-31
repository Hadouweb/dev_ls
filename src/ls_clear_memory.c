/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_clear_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 11:38:59 by nle-bret          #+#    #+#             */
/*   Updated: 2016/10/31 11:39:01 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_free_entity_full(t_entity_full *e)
{
	ft_strdel(&e->name);
	ft_strdel(&e->day);
	if (e->group)
		ft_strdel(&e->group);
	ft_strdel(&e->hour_year);
	ft_strdel(&e->major);
	ft_strdel(&e->minor);
	ft_strdel(&e->month);
	ft_strdel(&e->nb_link);
	ft_strdel(&e->size);
	ft_strdel(&e->user);
	ft_strdel(&e->mode);
	free(e);
}

void		ls_free_entity(t_entity *e)
{
	if (e->name != NULL)
		ft_strdel(&e->name);
	if (e->entity_full)
		ls_free_entity_full(e->entity_full);
	if (e->link)
		ft_strdel(&e->link);
	if (e->rpath)
		ft_strdel(&e->rpath);
	free(e);
}
