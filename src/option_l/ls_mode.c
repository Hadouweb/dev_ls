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

void		ls_set_mode(t_entity *e)
{
	t_entity_full	*e_full;
	int				st_mode;

	st_mode = e->file.st_mode;
	e_full = e->entity_full;
	e_full->mode = ft_memalloc(12 * sizeof(char));
	ft_memset(e_full->mode, '-', 11);
	e_full->mode[11] = '\0';
	e_full->mode[0] = ls_get_file_type(st_mode);
	e_full->mode[1] = st_mode & S_IRUSR ? 'r' : e_full->mode[1];
	e_full->mode[2] = st_mode & S_IWUSR ? 'w' : e_full->mode[2];
	e_full->mode[3] = st_mode & S_IXUSR ? 'x' : e_full->mode[3];
	e_full->mode[4] = st_mode & S_IRGRP ? 'r' : e_full->mode[4];
	e_full->mode[5] = st_mode & S_IWGRP ? 'w' : e_full->mode[5];
	e_full->mode[6] = st_mode & S_IXGRP ? 'x' : e_full->mode[6];
	e_full->mode[7] = st_mode & S_IROTH ? 'r' : e_full->mode[7];
	e_full->mode[8] = st_mode & S_IWOTH ? 'w' : e_full->mode[8];
	e_full->mode[9] = st_mode & S_IXOTH ? 'x' : e_full->mode[9];
	ls_stickybit_suid(&e_full->mode[3], &e_full->mode[6],
	&e_full->mode[9], st_mode);
	e_full->mode[10] = ' ';
}
