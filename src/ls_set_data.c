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

void	debug_print_content(void *content)
{
	t_path *path;

	path = (t_path*)content;
	ft_putstr(path->name);
}

t_listd	*ls_get_node_cmp(t_listd **lst, t_path *path)
{
	__uint128_t 	t1;
	__uint128_t 	t2;
	t_listd 		*l;
	t_path 			*path_cmp;

	t1 = (__uint128_t) path->file.st_mtimespec.tv_sec
				 << 64 | path->file.st_mtimespec.tv_nsec;

	l = *lst;
	while (l)
	{
		path_cmp = (t_path*)l->content;
		if (ft_strcmp(path->name, path_cmp->name) != 0)
		{
			t2 = (__uint128_t) path_cmp->file.st_mtimespec.tv_sec
						 << 64 | path_cmp->file.st_mtimespec.tv_nsec;

			if (t2 - t1 == 0 && ft_strcmp(path->name, path_cmp->name) > 0)
			{
				printf("t1:[%s] = t2:[%s]\n", path->name, path_cmp->name);
				if (!S_ISDIR(path->file.st_mode) &&
					S_ISDIR(path_cmp->file.st_mode))
				{
					printf("not dir:[%s] dir:[%s]\n", path->name, path_cmp->name);
					return l;
				}
			}
			printf("t1:[%s][%ld %ld] t2[%s][%ld %ld]\n",
				   path->name, path->file.st_mtimespec.tv_sec,
				   path->file.st_mtimespec.tv_nsec,
				   path_cmp->name, path_cmp->file.st_mtimespec.tv_sec,
				   path_cmp->file.st_mtimespec.tv_nsec);
			if (t1 > t2)
			{
				printf("t1:[%s] > t2[%s]\n", path->name, path_cmp->name);
				return l;
			}
		}
		l = l->next;
	}
	return NULL;
}


void	ls_push_after_sort(t_listd **lst, t_path *path, t_app *app)
{
	if (app->opt & OPT_t)
	{
		t_listd *node = ls_get_node_cmp(lst, path);
		if (node != NULL)
		{
			ft_lstd_pushbefore_node(lst, node, ft_lstd_new((void *) path, sizeof(t_path)));
			printf("before this: %s current: %s\n",
			 ((t_path*)node->content)->name, path->name);
		} else {
			ft_lstd_pushback(lst, (void *) path, sizeof(t_path));
			printf("add classic: %s\n", path->name);
		}
	}
}

void	ls_set_file_data(char *rpath, char *name, t_listd **lst, t_app *app)
{
	t_path	*path;
	int		ret;

	ft_lstd_print(*lst, debug_print_content, 1);
	//printf("ls_set_file_data | rpath: %s name: %s\n", rpath, name);

	ret = -1;
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