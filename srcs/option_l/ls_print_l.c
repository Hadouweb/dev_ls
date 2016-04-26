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

void		ls_print_user_group(int st_uid, int st_gid)
{
	struct passwd	*user;
	struct group	*group;

	user = ls_get_user_data(st_uid);
	ft_putchar(' ');
	if (user == NULL)
		ft_putnbr(st_uid);
	else
		ft_putstr(user->pw_name);
	ft_putchar(' ');
	group = ls_get_group_data(st_gid);
	ft_putchar(' ');
	if (group == NULL)
		ft_putnbr(st_gid);
	else
		ft_putstr(group->gr_name);
	ft_putchar(' ');
}

void		ls_print_size(int st_size, int st_mode, int st_rdev)
{
	int		nbr;
	int		size;

	nbr = 0;
	size = 0;
	if (S_ISCHR(st_mode) || S_ISBLK(st_mode))
	{
		nbr = ls_major(st_rdev);
		ls_adjust_space(4 - ft_intlen(nbr));
		ft_putnbr(nbr);
		ft_putchar(',');
		nbr = ls_minor(st_rdev);
		ls_adjust_space(4 - ft_intlen(nbr));
		ft_putnbr(nbr);
		ft_putchar(' ');
	}
	else
	{
		ft_putchar(' ');
		ft_putnbr(st_size);
		ft_putchar(' ');
	}
}

static void	ls_print_month(char *m)
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
}

void		ls_print_time(const time_t t)
{
	char			*str_time;
	char			**split;
	int				i;
	int				dm;

	dm = ls_diff_six_month(t);
	str_time = ctime(&t);
	split = ft_strsplit(str_time, ' ');
	i = 0;
	if (ft_strlen(split[2]) == 1)
		ft_putchar(' ');
	ft_putstr(split[2]);
	ft_putchar(' ');
	ls_print_month(split[1]);
	ft_putchar(' ');
	split[3][5] = '\0';
	split[4][4] = '\0';
	if (dm)
	{
		ft_putchar(' ');
		ft_putstr(split[4]);
	}
	else
		ft_putstr(split[3]);
	ft_free_tab(split);
}
