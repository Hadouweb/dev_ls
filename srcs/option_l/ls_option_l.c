/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_option_l.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 17:24:03 by nle-bret          #+#    #+#             */
/*   Updated: 2016/04/26 17:24:05 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_print_adjust_space(char *str, int size)
{
	int		i;

	i = ft_strlen(str) - 1;
	while (i < size)
	{
		ft_putchar(' ');
		i++;
	}
	ft_putstr(str);
}

void		ls_print_option_l(t_app *app)
{
	t_list	*l;

	l = app->prepa;
	while (l)
	{
		t_prepa		*p;

		p = (t_prepa*)l->content;
		ft_putstr(p->mode);
		ls_print_adjust_space(p->nb_link, app->ms.nb_link);
		ls_print_adjust_space(p->user, app->ms.user);
		ls_print_adjust_space(p->group, app->ms.group);
		ls_print_adjust_space(p->size, app->ms.size);
		ls_print_adjust_space(p->time, app->ms.time);
		ft_putchar(' ');
		ft_putstr(p->name);
		ft_putchar('\n');
		l = l->next;
	}
	//ls_print_mode(file.st_mode);
	//ls_print_physical_link(file.st_nlink);
	//ls_print_user_group(file.st_uid, file.st_gid);
	//ls_print_size(file.st_size, file.st_mode, file.st_rdev);
	//ls_print_time(file.st_mtime);
	//ls_print_path(path->name, path->link);
	ft_putchar('\n');
}

struct stat	ls_get_data_file(char *name, int is_link)
{
	struct stat	file;

	errno = 0;
	if (is_link)
		lstat(name, &file);
	else
		stat(name, &file);
	if (errno != 0)
		ls_error_errno("Error in ft_get_data_file ");
	return (file);
}
