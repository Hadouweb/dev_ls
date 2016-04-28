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

void		ls_prepare_user(t_prepa *p, int st_uid, t_app *app)
{
	struct passwd	*user;
	int 			size;

	user = ls_get_user_data(st_uid);
	if (user == NULL)
		p->user = ft_itoa(st_uid);
	else
		p->user = user->pw_name;
	if ((size = ft_strlen(p->user)) > app->ms.user)
		app->ms.user = size;
}

void		ls_prepare_group(t_prepa *p, int st_gid, t_app *app)
{
	struct group	*group;
	int 			size;

	group = ls_get_group_data(st_gid);
	if (group == NULL)
		p->group = ft_itoa(st_gid);
	else
		p->group = group->gr_name;
	if ((size = ft_strlen(p->group)) > app->ms.group)
		app->ms.group = size;
}

void		ls_prepare_size(t_prepa *p, struct stat file, t_app *app)
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
		if ((size = ft_strlen(p->major)) > app->ms.major)
			app->ms.major = size;
		if ((size = ft_strlen(p->minor)) > app->ms.minor)
			app->ms.minor = size;
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

/*static void	ls_print_month(char *m)
{
	m = (ft_strcmp(m, "Jan") == 0) ? ft_memmove(m, "jan", 3) : m;
	m = (ft_strcmp(m, "Feb") == 0) ? ft_memmove(m, "fév", 4) : m;
	m = (ft_strcmp(m, "Mar") == 0) ? ft_memmove(m, "mar", 3) : m;
	m = (ft_strcmp(m, "Apr") == 0) ? ft_memmove(m, "avr", 3) : m;
	m = (ft_strcmp(m, "May") == 0) ? ft_memmove(m, "mai", 3) : m;
	m = (ft_strcmp(m, "Jun") == 0) ? ft_memmove(m, "jui", 3) : m;
	m = (ft_strcmp(m, "Jul") == 0) ? ft_memmove(m, "jul", 3) : m;
	m = (ft_strcmp(m, "Aug") == 0) ? ft_memmove(m, "aoû", 4) : m;
	m = (ft_strcmp(m, "Sep") == 0) ? ft_memmove(m, "sep", 3) : m;
	m = (ft_strcmp(m, "Oct") == 0) ? ft_memmove(m, "oct", 3) : m;
	m = (ft_strcmp(m, "Nov") == 0) ? ft_memmove(m, "nov", 3) : m;
	m = (ft_strcmp(m, "Dec") == 0) ? ft_memmove(m, "déc", 4) : m;
	ft_putstr(m);
}*/

void		ls_prepare_time(t_prepa *p, const time_t t, t_app *app)
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
