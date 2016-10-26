/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_l.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 17:24:10 by nle-bret          #+#    #+#             */
/*   Updated: 2016/04/26 17:24:11 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_set_user(t_entity *e, int st_uid)
{
	t_entity_full	*e_full;
	struct passwd	*user;
	int				size;

	e_full = e->entity_full;
	user = ls_get_user_data(st_uid);
	if (user == NULL)
		e_full->user = ft_itoa(st_uid);
	else
		e_full->user = user->pw_name;
	if ((size = ft_strlen(e_full->user)) > e->ms.user)
		e->ms.user = size;
}

void		ls_set_group(t_entity *e, int st_gid)
{
	t_entity_full	*e_full;
	struct group	*group;
	int 			size;

	e_full = e->entity_full;
	group = ls_get_group_data(st_gid);
	if (group == NULL)
		e_full->group = ft_itoa(st_gid);
	else
		e_full->group = group->gr_name;
	if ((size = ft_strlen(e_full->group) + 1) > e->ms.group)
		e->ms.group = size;
}

void		ls_set_size(t_entity *e, struct stat file)
{
	t_entity_full	*e_full;
	int		nbr;
	int		size;

	e_full = e->entity_full;
	nbr = 0;
	if (S_ISCHR(file.st_mode) || S_ISBLK(file.st_mode))
	{
		nbr = ls_major(file.st_rdev);
		e_full->major = ft_itoa(nbr);
		nbr = ls_minor(file.st_rdev);
		e_full->minor = ft_itoa(nbr);
		e_full->size = NULL;
		if ((size = 8) > e->ms.size)
			e->ms.size = size;
	}
	else
	{
		e_full->size = ft_itoa(file.st_size);
		e_full->major = NULL;
		e_full->minor = NULL;
		if ((size = ft_strlen(e_full->size)) > e->ms.size)
			e->ms.size = size;
	}
}

void		ls_set_time(t_entity *e, const time_t t)
{
	t_entity_full	*e_full;
	char			*str_time;
	char			**split;
	int				dm;
	int				size;

	e_full = e->entity_full;
	dm = ls_diff_six_month(t);
	str_time = ctime(&t);
	split = ft_strsplit(str_time, ' ');
	e_full->month = ft_strdup(split[1]);
	e_full->day = ft_strdup(split[2]);
	if (dm)
		e_full->hour_year = ft_strndup(split[4], 4);
	else
		e_full->hour_year = ft_strndup(split[3], 5);
	ft_free_tab(split);
	if ((size = ft_strlen(e_full->month)) > e->ms.month)
		e->ms.month = size;
	if ((size = ft_strlen(e_full->day)) > e->ms.day)
		e->ms.day = size;
	if ((size = ft_strlen(e_full->hour_year)) > e->ms.hour_year)
		e->ms.hour_year = size;
}
