#include "ft_ls.h"

int		ls_swap(t_list *a, t_list *b)
{
	char	*tmp;
	
	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
	return (1);
}

int		ls_lstcmp(t_list *a, t_list *b)
{
	t_path	*path_a;
	t_path	*path_b;

	path_a = (t_path*)a->content;
	path_b = (t_path*)b->content;
	return (ft_strcmp(path_a->name, path_b->name));
}

int		ls_cmp_file_type(t_list *a, t_list *b)
{
	t_path	*path_a;
	t_path	*path_b;

	path_a = (t_path*)a->content;
	path_b = (t_path*)b->content;
	if (S_ISDIR(path_a->file.st_mode) && !S_ISDIR(path_b->file.st_mode))
		return (1);
	else if (S_ISDIR(path_a->file.st_mode) || S_ISDIR(path_b->file.st_mode))
		return (-1);
	return (0);
}

void	ls_lstsort(t_list **lst)
{
	t_list	*l;
	int		swap;
	int		is_dir;

	swap = 1;
	while (swap)
	{
		swap = 0;
		l = *lst;
		is_dir = 0;
		while (l->next)
		{
			is_dir = ls_cmp_file_type(l, l->next);
			//if (is_dir > 0)
			//	swap = ls_swap(l, l->next);
			if (ls_lstcmp(l, l->next) > 0)
				swap = ls_swap(l, l->next);
			l = l->next;
		}
	}
}