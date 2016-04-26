/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 17:19:51 by nle-bret          #+#    #+#             */
/*   Updated: 2016/04/26 17:19:52 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	else if (!S_ISDIR(path_a->file.st_mode) && !S_ISDIR(path_b->file.st_mode))
		return (-1);
	else if (S_ISDIR(path_a->file.st_mode) && S_ISDIR(path_b->file.st_mode))
		return (-1);
	return (0);
}

void	ls_lstsort_param(t_list **lst)
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
			if (is_dir == 1)
				swap = ls_swap(l, l->next);
			else if (ls_lstcmp(l, l->next) > 0 && is_dir == -1)
				swap = ls_swap(l, l->next);
			l = l->next;
		//	ft_lstprint(*lst, ls_debug_path);
		//	ft_putendl("_______");
		}
	}
}

void	ls_lstsort_folder(t_list **lst)
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
			if (ls_lstcmp(l, l->next) > 0)
				swap = ls_swap(l, l->next);
			l = l->next;
		//	ft_lstprint(*lst, ls_debug_path);
		//	ft_putendl("_______");
		}
	}
}
