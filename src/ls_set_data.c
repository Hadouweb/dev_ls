/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_set_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 17:20:31 by nle-bret          #+#    #+#             */
/*   Updated: 2016/04/26 17:20:33 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_set_file_data(char *rpath, char *name, t_listd **lst, t_app *app)
{
	t_path	*path;
	int		ret;

	if (rpath == NULL)
		rpath = name;
	if ((path = (t_path*)ft_memalloc(sizeof(t_path))) == NULL)
		ls_error("Error: malloc");
	path->name = ft_strdup(name);
	if ((path->link = ls_get_link(rpath)) == NULL)
		ret = ls_get_data_file(rpath, 0, &path->file);
	else
		ret = ls_get_data_file(rpath, 1, &path->file);
	app->ms.total_folder += path->file.st_blocks;
	if (ret == 0)
		ls_push_after_sort(lst, path, app);
	free(path);
}

void	ls_set_option_l(t_app *app, t_path *path)
{
	t_prepa 	*p;

	if ((p = (t_prepa*)ft_memalloc(sizeof(t_prepa))) == NULL)
		ls_error("Error: malloc");
	ls_set_mode(p, path->file.st_mode);
	ls_set_nb_link(p, path->file.st_nlink, app);
	ls_set_user(p, path->file.st_uid, app);
	ls_set_group(p, path->file.st_gid, app);
	ls_set_size(p, path->file, app);
	ls_set_time(p, path->file.st_mtime, app);
	ls_set_path(p, path->name, path->link, app);
	ft_lstd_pushback(&app->prepa, (void*)p, sizeof(t_prepa));
	free(p);
}

void	ls_set_folder(t_app *app, char *name)
{
	DIR		*dir;
	char	*dir_path;
	t_listd	*lst;

	lst = NULL;
	if (name[ft_strlen(name) - 1] != '/')
		dir_path = ft_stradd_char(&name, '/');
	else
		dir_path = ft_strdup(name);
	dir = ls_opendir(dir_path);
	ls_readdir(dir, &lst, dir_path, app);
	ls_closedir(dir);
	ls_print_folder(app, &lst, name);
	ft_strdel(&dir_path);
}