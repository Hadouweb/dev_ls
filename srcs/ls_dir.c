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

void	ls_prepare_to_push(char *name, t_list **lst)
{
	t_path	*path;
	char	*link;

	if ((path = (t_path*)ft_memalloc(sizeof(t_path))) == NULL)
		ls_error("Error: malloc");
	path->name = ft_strdup(name);
	if ((path->link = ls_get_link(name)) == NULL)
		path->file = ls_get_data_file(name, 0);
	else
		path->file = ls_get_data_file(name, 1);
	ft_lstpush_back(lst, (void*)path, sizeof(t_path));
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
			ls_prepare_to_push(relativ_path, lst);
	}
}

void	ls_closedir(DIR *dir)
{
	errno = 0;
	closedir(dir);
	if (errno != 0)
		ls_error_errno("Error in ls_closedir ");
}

void	ls_print_folder(char *name)
{
	DIR		*dir;
	t_list	*lst;

	lst = NULL;
	if (name[ft_strlen(name) - 1] != '/')
		name = ft_stradd_char(&name, '/');
	dir = ls_opendir(name);
	ls_readdir(dir, &lst, name);
	ls_closedir(dir);
	ls_lstsort(&lst);
	ft_lstprint(lst, ls_debug_path);
}