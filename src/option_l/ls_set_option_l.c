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
	int				st_uid;

	st_uid = e->file.st_uid;
	e_full = e->entity_full;
	user = ls_get_user_data(st_uid);
	if (user == NULL)
		e_full->user = ft_itoa(st_uid);
	else
		e_full->user = ft_strdup(user->pw_name);
	if ((size = ft_strlen(e_full->user)) > ms->user)
		ms->user = size;
}

void		ls_set_group(t_entity *e, t_max_size *ms)
{
	t_entity_full	*e_full;
	struct group	*group;
	int				size;
	int				st_gid;

	st_gid = e->file.st_gid;
	e_full = e->entity_full;
	group = ls_get_group_data(st_gid);
	if (group == NULL)
		e_full->group = ft_itoa(st_gid);
	else
		e_full->group = ft_strdup(group->gr_name);
	if ((size = ft_strlen(e_full->group) + 1) > ms->group)
		ms->group = size;
}

char		*ls_format_hour_year(char *str)
{
	int		i;
	char	*str_format;
	char 	*tmp;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	tmp = ft_strndup(str, i);
	str_format = ft_strjoin(" ", tmp);
	ft_strdel(&tmp);
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

void		ls_set_option_l(t_entity *e, t_max_size *ms)
{
	if ((e->entity_full = (t_entity_full*)ft_memalloc(
			sizeof(t_entity_full))) == NULL)
		ls_error("Error: malloc");
	ls_set_mode(e);
	ls_set_nb_link(e, ms);
	ls_set_user(e, ms);
	ls_set_group(e, ms);
	ls_set_size(e, ms);
	ls_set_time(e, ms);
}
