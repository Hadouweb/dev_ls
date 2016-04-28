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

void	ls_prepare_file_data(char *relativ_path, char *name, t_list **lst)
{
	t_path	*path;

	if (relativ_path == NULL)
		relativ_path = name;
	if ((path = (t_path*)ft_memalloc(sizeof(t_path))) == NULL)
		ls_error("Error: malloc");
	path->name = ft_strdup(name);
	if ((path->link = ls_get_link(relativ_path)) == NULL)
		path->file = ls_get_data_file(relativ_path, 0);
	else
		path->file = ls_get_data_file(relativ_path, 1);
	ft_lstpush_back(lst, (void*)path, sizeof(t_path));
	free(path);
}

void	ls_prepare_for_option_l(t_app *app, t_path *path)
{
	t_prepa 	*p;

	if ((p = (t_prepa*)ft_memalloc(sizeof(t_prepa))) == NULL)
		ls_error("Error: malloc");
	ls_prepare_mode(p, path->file.st_mode);
	ls_prepare_nb_link(p, path->file.st_nlink, app);
	ls_prepare_user(p, path->file.st_uid, app);
	ls_prepare_group(p, path->file.st_gid, app);
	ls_prepare_size(p, path->file, app);
	ls_prepare_time(p, path->file.st_mtime, app);
	ft_lstpush_back(&app->prepa, (void*)p, sizeof(t_prepa));
	free(p);
}