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

void	ls_readdir(DIR *dir, t_listd **lst, char *origin, t_app *app)
{
	struct dirent	*dp;
	char			*relativ_path;
	int 			token;

	errno = 0;
	token = 0;
	//printf("ls_readdir\n");
	while ((dp = readdir(dir)) != NULL)
	{
		relativ_path = ft_strjoin(origin, dp->d_name);
		if (errno != 0)
			ls_error_errno("Error in ls_readdir ");
		if (dp->d_name[0] != '.' || app->opt & OPT_a)
			ls_set_file_data(relativ_path, dp->d_name, lst, app);
		ft_strdel(&relativ_path);
		token++;
	}
	if (token > 0 && app->token == 1)
		ft_putchar('\n');
	else
		app->token = 1;
	//ft_lstd_print(*lst, ls_debug_print_content, 1);
}

void	ls_closedir(DIR *dir)
{
	errno = 0;
	closedir(dir);
	if (errno != 0)
		ls_error_errno("Error in ls_closedir ");
}
