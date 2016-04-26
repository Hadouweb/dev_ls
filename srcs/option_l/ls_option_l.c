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

void		ls_print_option_l(char *name)
{
	struct stat file;
	char		*link;

	if ((link = ls_get_link(name)) == NULL)
		file = ls_get_data_file(name, 0);
	else
		file = ls_get_data_file(name, 1);
	ls_print_mode(file.st_mode);
	ls_print_physical_link(file.st_nlink);
	ls_print_user_group(file.st_uid, file.st_gid);
	ls_print_size(file.st_size, file.st_mode, file.st_rdev);
	ls_print_time(file.st_mtime);
	ls_print_path(name, link);
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
