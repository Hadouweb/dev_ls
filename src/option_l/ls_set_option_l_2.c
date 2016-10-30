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
	t_entity_full	*e_full;
	int				size;
	int				st_nlink;

	st_nlink = e->file.st_nlink;
	e_full = e->entity_full;
	e_full->nb_link = ft_itoa(st_nlink);
	if ((size = ft_strlen(e_full->nb_link)) > ms->nb_link)
		ms->nb_link = size;
}

void		ls_set_link(t_entity *e)
{
	if (e->link != NULL)
	{
		e->name = ft_strjoin_free_s1(e->name, " -> ");
		e->name = ft_strjoin_free_s1(e->name, e->link);
	}
}

void		ls_set_size(t_entity *e, t_max_size *ms)
{
	t_entity_full	*e_full;
	int				size;
	struct stat		file;

	file = e->file;
	e_full = e->entity_full;
	if (S_ISCHR(file.st_mode) || S_ISBLK(file.st_mode))
	{
		e_full->major = ft_itoa(ls_major(file.st_rdev));
		e_full->minor = ft_itoa(ls_minor(file.st_rdev));
		e_full->size = NULL;
		if ((size = 8) > ms->size)
			ms->size = size;
	}
	else
	{
		e_full->size = ft_itoa(file.st_size);
		e_full->major = NULL;
		e_full->minor = NULL;
		if ((size = ft_strlen(e_full->size)) > ms->size)
			ms->size = size;
	}
}
