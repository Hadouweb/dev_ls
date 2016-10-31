/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_user_group.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 17:21:52 by nle-bret          #+#    #+#             */
/*   Updated: 2016/04/26 17:21:53 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

struct passwd	*ls_get_user_data(int uid)
{
	struct passwd *user;

	errno = 0;
	user = getpwuid(uid);
	return (user);
}

struct group	*ls_get_group_data(int gid)
{
	struct group *group;

	errno = 0;
	group = getgrgid(gid);
	return (group);
}

t_listd			*ls_get_entity_child(t_app *app, char *name, t_entity *parent)
{
	DIR		*dir;
	char	*dir_path;
	t_listd	*lst;

	lst = NULL;
	if (name[ft_strlen(name) - 1] != '/')
		dir_path = ft_stradd_char(&name, '/');
	else
		dir_path = ft_strdup(name);
	errno = 0;
	dir = opendir(dir_path);
	ft_strdel(&dir_path);
	if (errno != 0)
	{
		parent->errno_code = errno;
		errno = 0;
	}
	if (dir != NULL)
	{
		ls_readdir(dir, &lst, app, parent);
		ls_closedir(dir);
	}
	return (lst);
}
