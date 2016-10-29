/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 17:22:34 by nle-bret          #+#    #+#             */
/*   Updated: 2016/04/26 17:22:36 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char 	*ls_format_name_error(char *file)
{
	int		size;
	char 	*tmp;

	tmp = file;
	size = ft_strlen(file);
	if (file[size - 1] == '/')
		file[size - 1] = '\0';
	size -= 2;
	while (file[size] && file[size] != '/')
	{
		if (file[size] == '/')
			break;
		size--;
	}
	if (file[size] == '/' && file[size + 1])
		size++;
	return (&file[size]);
}

DIR		*ls_opendir(char *file)
{
	DIR		*dir;

	errno = 0;
	dir = opendir(file);
	//printf("ls_opendir: %s\n", file);
	if (errno != 0) {
		//e->errno_code = errno;
		//e->name = path;
		//ls_error_errno(ls_format_name_error(file));
		//errno = 0;
	}
	return (dir);
}

void	ls_readdir(DIR *dir, t_listd **lst, t_app *app, t_entity *parent)
{
	struct dirent	*dp;

	errno = 0;
	while ((dp = readdir(dir)) != NULL)
	{
		if (errno != 0)
			ls_error_errno("Error in ls_readdir ");
		if (dp->d_name[0] != '.' || app->opt & OPT_a)
			ls_push_entity(app, parent, dp->d_name, lst);
	}
	//ft_lstd_print(*lst, ls_debug_print_content, 1);
}

void	ls_closedir(DIR *dir)
{
	errno = 0;
	closedir(dir);
	if (errno != 0)
		ls_error_errno("Error in ls_closedir ");
}
