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
	t_entity	*e;
	int			ret;

	if ((e = (t_entity*)ft_memalloc(sizeof(t_entity))) == NULL)
		ls_error("Error: malloc");
	if (rpath == NULL) {
		e->parent = NULL;
		rpath = name;
	} else
		e->parent = ft_strdup(rpath);
	e->name = ft_strdup(name);
	if ((e->link = ls_get_link(rpath)) == NULL)
		ret = ls_get_data_file(rpath, 0, &e->file);
	else
		ret = ls_get_data_file(rpath, 1, &e->file);
	e->ms.total_folder += e->file.st_blocks;
	if (ret == 0)
		ls_push_after_sort(lst, e, app);
}

void	ls_set_option_l(t_entity *e)
{
	t_entity_full 	*e_full;

	if ((e_full = (t_entity_full*)ft_memalloc(sizeof(t_entity_full))) == NULL)
		ls_error("Error: malloc");
	ls_set_mode(e_full, e->file.st_mode);
	ls_set_nb_link(e, e->file.st_nlink);
	ls_set_user(e, e->file.st_uid);
	ls_set_group(e, e->file.st_gid);
	ls_set_size(e, e->file);
	ls_set_time(e, e->file.st_mtime);
	ls_set_entity(e, e->name, e->link);
	e->entity_full = e_full;
}

t_listd	*ls_get_entity_dir(t_app *app, char *name)
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
	if (dir != NULL) {
		ls_readdir(dir, &lst, dir_path, app);
		ls_closedir(dir);
		//ls_print_folder(app, &lst, name);
		ft_strdel(&dir_path);
	}
	return lst;
}