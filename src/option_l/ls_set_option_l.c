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

void		ls_set_user(t_entity *e, t_max_size *ms)
{
	t_entity_full	*e_full;
	struct passwd	*user;
	int				size;
	int 			st_uid;

	st_uid = e->file.st_uid;
	e_full = e->entity_full;
	user = ls_get_user_data(st_uid);
	if (user == NULL)
		e_full->user = ft_itoa(st_uid);
	else
		e_full->user = user->pw_name;
	if ((size = ft_strlen(e_full->user)) > ms->user)
		ms->user = size;
}

void		ls_set_group(t_entity *e, t_max_size *ms)
{
	t_entity_full	*e_full;
	struct group	*group;
	int 			size;
	int 			st_gid;

	st_gid = e->file.st_gid;
	e_full = e->entity_full;
	group = ls_get_group_data(st_gid);
	if (group == NULL)
		e_full->group = ft_itoa(st_gid);
	else
		e_full->group = group->gr_name;
	if ((size = ft_strlen(e_full->group) + 1) > ms->group)
		ms->group = size;
}

void		ls_set_size(t_entity *e, t_max_size *ms)
{
	t_entity_full	*e_full;
	int				nbr;
	int				size;
	struct stat 	file;

	file = e->file;
	e_full = e->entity_full;
	nbr = 0;
	if (S_ISCHR(file.st_mode) || S_ISBLK(file.st_mode))
	{
		nbr = ls_major(file.st_rdev);
		e_full->major = ft_itoa(nbr);
		nbr = ls_minor(file.st_rdev);
		e_full->minor = ft_itoa(nbr);
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

char 		*ls_format_hour_year(char *str)
{
	int 	i;
	char 	*str_format;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	str_format = ft_strndup(str, i);
	str_format = ft_strjoin(" ", str_format);
	return (str_format);
}

void		ls_set_time(t_entity *e, t_max_size *ms)
{
	t_entity_full	*e_full;
	char			*str_time;
	char			**split;
	int				dm;
	int				size;

	e_full = e->entity_full;
	dm = ls_diff_six_month(e->file.st_mtime);
	str_time = ctime(&e->file.st_mtime);
	split = ft_strsplit(str_time, ' ');
	e_full->month = ft_strdup(split[1]);
	e_full->day = ft_strdup(split[2]);

	if (dm)
		e_full->hour_year = ls_format_hour_year(split[4]);
	else
		e_full->hour_year = ft_strndup(split[3], 5);
	ft_free_tab(split);
	if ((size = ft_strlen(e_full->month)) > ms->month)
		ms->month = size;
	if ((size = ft_strlen(e_full->day)) > ms->day)
		ms->day = size;
	if ((size = ft_strlen(e_full->hour_year)) > ms->hour_year)
		ms->hour_year = size;
}
