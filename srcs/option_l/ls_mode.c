/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_mode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 17:23:26 by nle-bret          #+#    #+#             */
/*   Updated: 2016/04/26 17:23:28 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	ls_get_file_type(int st_mode)
{
	if (S_ISREG(st_mode))
		return ('-');
	else if (S_ISDIR(st_mode))
		return ('d');
	else if (S_ISCHR(st_mode))
		return ('c');
	else if (S_ISBLK(st_mode))
		return ('b');
	else if (S_ISFIFO(st_mode))
		return ('p');
	else if (S_ISLNK(st_mode))
		return ('l');
	else if (S_ISSOCK(st_mode))
		return ('s');
	return ('-');
}

static void	ls_stickybit_suid(char *u, char *g, char *o, int st_mode)
{
	if (st_mode & S_IXUSR)
		*u = st_mode & S_ISUID ? 's' : *u;
	else
		*u = st_mode & S_ISUID ? 'S' : *u;
	if (st_mode & S_IXGRP)
		*g = st_mode & S_ISGID ? 's' : *g;
	else
		*g = st_mode & S_ISGID ? 'S' : *g;
	if (st_mode & S_IXOTH)
		*o = st_mode & S_ISVTX ? 't' : *o;
	else
		*o = st_mode & S_ISVTX ? 'T' : *o;
}

void		ls_prepare_mode(t_prepa *p, int st_mode)
{
	ft_memset(p->mode, '-', 11);
	p->mode[11] = '\0';
	p->mode[0] = ls_get_file_type(st_mode);
	p->mode[1] = st_mode & S_IRUSR ? 'r' : p->mode[1];
	p->mode[2] = st_mode & S_IWUSR ? 'w' : p->mode[2];
	p->mode[3] = st_mode & S_IXUSR ? 'x' : p->mode[3];
	p->mode[4] = st_mode & S_IRGRP ? 'r' : p->mode[4];
	p->mode[5] = st_mode & S_IWGRP ? 'w' : p->mode[5];
	p->mode[6] = st_mode & S_IXGRP ? 'x' : p->mode[6];
	p->mode[7] = st_mode & S_IROTH ? 'r' : p->mode[7];
	p->mode[8] = st_mode & S_IWOTH ? 'w' : p->mode[8];
	p->mode[9] = st_mode & S_IXOTH ? 'x' : p->mode[9];
	ls_stickybit_suid(&p->mode[3], &p->mode[6], &p->mode[9], st_mode);
	p->mode[10] = ' ';
}
