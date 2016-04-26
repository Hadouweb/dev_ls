#include "ft_ls.h"

void	ls_prepare_to_push(char *relativ_path, char *name, t_list **lst)
{
	t_path	*path;
	char	*link;

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