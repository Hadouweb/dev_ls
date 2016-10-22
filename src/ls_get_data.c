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
	if (errno != 0 || user == NULL)
		;//ls_error_errno("Error in ls_get_user_data ");
	return (user);
}

struct group	*ls_get_group_data(int gid)
{
	struct group *group;

	errno = 0;
	group = getgrgid(gid);
	if (errno != 0 || group == NULL)
		;//ls_error_errno("Error in ls_get_group_data ");
	return (group);
}

void DEBUG_print_file(char *name, struct stat *file)
{
	printf("Name %s | %ld\n", name, file->st_mtimespec.tv_sec);
}

int			ls_get_data_file(char *name, int is_link, struct stat *file)
{
	int			ret;

	errno = 0;
	ret = -1;
	if (is_link)
		ret = lstat(name, file);
	else
		ret = stat(name, file);
	if (errno != 0)
	{
		ft_putstr("ls: ");
		perror(name);
	}

	//DEBUG_print_file(name, file);

	return (ret);
}