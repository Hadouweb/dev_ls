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

void		ls_set_nb_link(t_entity *e, int st_nlink)
{
	t_entity_full 	*e_full;
	int				size;

	e_full = e->entity_full;
	e_full->nb_link = ft_itoa(st_nlink);
	if ((size = ft_strlen(e_full->nb_link)) > e->ms.nb_link)
		e->ms.nb_link = size;
}

/*void		ls_push_entity(t_entity *e, char *path, char *link)
{
	t_entity_full 	*e_full;
	int				size;

	e_full = e->entity_full;
	e_full->name = ft_strdup(path);
	if (link != NULL)
	{
		e_full->name = ft_strjoin_free_s1(e_full->name, " -> ");
		e_full->name = ft_strjoin_free_s1(e_full->name, link);
	}
	if ((size = ft_strlen(e_full->name)) > e->ms.name)
		e->ms.name = size;
}*/
