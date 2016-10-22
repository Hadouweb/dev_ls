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

void		ls_set_user(t_prepa *p, int st_uid, t_app *app)
{
	struct passwd	*user;
	int				size;

	user = ls_get_user_data(st_uid);
	if (user == NULL)
		p->user = ft_itoa(st_uid);
	else
		p->user = user->pw_name;
	if ((size = ft_strlen(p->user)) > app->ms.user)
		app->ms.user = size;
}

void		ls_set_group(t_prepa *p, int st_gid, t_app *app)
{
	struct group	*group;
	int 			size;

	group = ls_get_group_data(st_gid);
	if (group == NULL)
		p->group = ft_itoa(st_gid);
	else
		p->group = group->gr_name;
	if ((size = ft_strlen(p->group) + 1) > app->ms.group)
		app->ms.group = size;
}

void		ls_set_size(t_prepa *p, struct stat file, t_app *app)
{
	int		nbr;
	int		size;

	nbr = 0;
	if (S_ISCHR(file.st_mode) || S_ISBLK(file.st_mode))
	{
		nbr = ls_major(file.st_rdev);
		p->major = ft_itoa(nbr);
		nbr = ls_minor(file.st_rdev);
		p->minor = ft_itoa(nbr);
		p->size = NULL;
		if ((size = 8) > app->ms.size)
			app->ms.size = size;
	}
	else
	{
		p->size = ft_itoa(file.st_size);
		p->major = NULL;
		p->minor = NULL;
		if ((size = ft_strlen(p->size)) > app->ms.size)
			app->ms.size = size;
	}
}

void		ls_set_time(t_prepa *p, const time_t t, t_app *app)
{
	char			*str_time;
	char			**split;
	int				dm;
	int				size;

	dm = ls_diff_six_month(t);
	str_time = ctime(&t);
	split = ft_strsplit(str_time, ' ');
	p->time = ft_strdup(split[1]);
	p->time = ft_strjoin_free_s1(p->time, " ");
	p->time = ft_strjoin_free_s1(p->time, split[2]);
	p->time = ft_strjoin_free_s1(p->time, " ");
	split[3][5] = '\0';
	split[4][4] = '\0';
	if (dm)
		p->time = ft_strjoin_free_s1(p->time, split[4]);
	else
		p->time = ft_strjoin_free_s1(p->time, split[3]);
	ft_free_tab(split);
	if ((size = ft_strlen(p->time)) > app->ms.time)
		app->ms.time = size;
}
