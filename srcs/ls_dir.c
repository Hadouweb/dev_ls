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

DIR		*ls_opendir(char *file)
{
	DIR		*dir;

	errno = 0;
	dir = opendir(file);
	if (errno != 0)
		ls_error_errno("Error in ls_opendir ");
	return (dir);
}

void	ls_readdir(DIR *dir, t_list **lst, char *origin)
{
	struct dirent	*dp;
	char			*relativ_path;

	errno = 0;
	while ((dp = readdir(dir)) != NULL)
	{
		relativ_path = ft_strjoin(origin, dp->d_name);
		if (errno != 0)
			ls_error_errno("Error in ls_readdir ");
		if (dp->d_name[0] != '.')
			ls_prepare_file_data(relativ_path, dp->d_name, lst);
		ft_strdel(&relativ_path);
	}
}

void	ls_closedir(DIR *dir)
{
	errno = 0;
	closedir(dir);
	if (errno != 0)
		ls_error_errno("Error in ls_closedir ");
}

void	ls_final_output(t_app *app, t_path *path)
{
	if (app->opt == 0)
		ft_putendl(path->name);
	else if (app->opt & OPT_l)
		ls_prepare_for_option_l(app, path);
}

void	ls_print_folder_way(t_app *app, t_list **lst, char *dir)
{
	t_list	*l;
	t_list	*tmp;
	t_path	*path;

	ls_lstsort_folder(lst);
	l = *lst;
	if (app->size_lst > 1)
	{
		ft_putchar('\n');
		ft_putstr(dir);
		ft_putendl(":");
	}
	while (l)
	{
		path = (t_path*)l->content;
		ls_final_output(app, path);
		tmp = l;
		l = l->next;
		ft_strdel(&path->name);
		if (path->link != NULL)
			ft_strdel(&path->link);
		free(path);
		free(tmp);
	}
}

void	ls_print_folder(t_app *app, char *name)
{
	DIR		*dir;
	char	*dir_path;
	t_list	*lst;

	lst = NULL;
	if (name[ft_strlen(name) - 1] != '/')
		dir_path = ft_stradd_char(&name, '/');
	else
		dir_path = ft_strdup(name);
	dir = ls_opendir(dir_path);
	ls_readdir(dir, &lst, dir_path);
	ls_closedir(dir);
	ls_print_folder_way(app, &lst, name);
	ft_strdel(&dir_path);
}
