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

void	ls_push_entity(t_app *app, t_entity *parent, char *name, t_listd **lst)
{
	t_entity	*e;

	if ((e = (t_entity*)ft_memalloc(sizeof(t_entity))) == NULL)
		ls_error("Error: malloc");
	e->name = ft_strdup(name);
	if (parent == NULL) {
		e->e_parent = NULL;
		e->rpath = e->name;
	} else {
		e->rpath = ft_strjoin_free_s1(ft_strjoin(parent->rpath, "/"), e->name);
		e->e_parent = parent;
	}
	if (ls_set_filestat(e) == 0)
		ls_push_after_sort(lst, e, app);
	free(e);
}

char 	*ls_update_link(t_entity *e)
{
	char 	*path;
	DIR		*dir;
	//char 	*parent;

	path = e->rpath;
	dir = opendir("/etc/private/etc");
	if (dir)
		printf("Is a directory\n");
	printf("rpath:[%s] name:[%s] link:[%s]\n", e->rpath, e->name, e->link);

	printf("/%d\n", e->file.st_dev);

	return path;
}

int		ls_set_filestat(t_entity *e)
{
	int		ret;
	char 	*path;

	//ret = -1;
	path = e->rpath;
	e->link = ls_get_link(path);
	errno = 0;
	if (e->link != NULL) {
		path = ls_update_link(e);
		ret = lstat(path, &e->file);
	} else
		ret = stat(path, &e->file);

	//printf("%s %s\n", path, e->link);

	if (errno != 0)
	{
		ft_putstr("ls: ");
		perror(path);
	}
	if (e->e_parent != NULL)
		e->e_parent->ms.total_folder += e->file.st_blocks;
	return ret;
}

void	ls_set_option_l(t_entity *e, t_max_size *ms)
{
	if ((e->entity_full = (t_entity_full*)ft_memalloc(sizeof(t_entity_full))) == NULL)
		ls_error("Error: malloc");
	ls_set_mode(e);
	ls_set_nb_link(e, ms);
	ls_set_user(e, ms);
	ls_set_group(e, ms);
	ls_set_size(e, ms);
	ls_set_time(e, ms);
}

t_listd	*ls_get_entity_dir(t_app *app, char *name, t_entity *parent)
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
		ls_readdir(dir, &lst, app, parent);
		ls_closedir(dir);
		ft_strdel(&dir_path);
	}
	//ft_lstd_print(lst, ls_debug_print_content, 0);
	return lst;
}