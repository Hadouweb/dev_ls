#include "ft_ls.h"

DIR		*ls_opendir(char *file)
{
	DIR 	*dir;

	errno = 0;
	dir = opendir(file);
	if (errno != 0)
		ls_error_errno("Error in ls_opendir ");
	return (dir);
}

void	ls_readdir(DIR *dir, t_list **lst, char *origin)
{
	struct dirent 	*dp;
	char			*relativ_path;

	errno = 0;
	while ((dp = readdir(dir)) != NULL)
	{
		relativ_path = ft_strjoin(origin, dp->d_name);
		if (errno != 0)
			ls_error_errno("Error in ls_readdir ");
		if (dp->d_name[0] != '.')
			ls_prepare_to_push(relativ_path, dp->d_name, lst);
	}
}

void	ls_closedir(DIR *dir)
{
	errno = 0;
	closedir(dir);
	if (errno != 0)
		ls_error_errno("Error in ls_closedir ");
}

void	ls_print_folder_way(t_list **lst, char *dir, int opt)
{
	t_list	*l;
	t_path	*path;

	l  = *lst;
	ls_lstsort(lst);
	if (ft_strcmp(dir, ".") != 0)
	{
		ft_putchar('\n');
		ft_putstr(dir);
		ft_putendl(":");
	}
	while (l)
	{
		path = (t_path*)l->content;
		ft_putendl(path->name);
		l = l->next;
	}
	//ft_lstprint(*lst, ls_debug_path);
}

void	ls_print_folder(char *name, int opt)
{
	DIR		*dir;
	char 	*dir_path;
	t_list	*lst;

	lst = NULL;
	if (name[ft_strlen(name) - 1] != '/')
		dir_path = ft_stradd_char(&name, '/');
	else
		dir_path = ft_strdup(name);
	dir = ls_opendir(dir_path);
	ls_readdir(dir, &lst, dir_path);
	ls_closedir(dir);
	ls_print_folder_way(&lst, name, opt);
	ft_strdel(&dir_path);
	ft_strdel(&name);
}