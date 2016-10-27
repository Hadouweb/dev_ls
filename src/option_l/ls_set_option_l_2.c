/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print2_l.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 17:28:20 by nle-bret          #+#    #+#             */
/*   Updated: 2016/04/26 17:28:21 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_set_nb_link(t_entity *e, t_max_size *ms)
{
	t_entity_full 	*e_full;
	int				size;
	int 			st_nlink;

	st_nlink = e->file.st_nlink;
	e_full = e->entity_full;
	e_full->nb_link = ft_itoa(st_nlink);
	if ((size = ft_strlen(e_full->nb_link)) > ms->nb_link)
		ms->nb_link = size;
}

void		ls_set_link(t_entity *e)
{
	//t_entity_full 	*e_full;
	//int				size;

	//e_full = e->entity_full;
	//e->name = ft_strdup(e->name);
	if (e->link != NULL)
	{
		e->name = ft_strjoin_free_s1(e->name, " -> ");
		e->name = ft_strjoin_free_s1(e->name, e->link);
	}
	//if ((size = ft_strlen(e_full->name)) > e->ms.name)
	//	e->ms.name = size;
}
