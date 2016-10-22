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

#include <time.h>
#include <sys/stat.h>
#include "ft_ls.h"
#include "../includes/ft_ls.h"

void		ls_debug_swap(t_list *a, t_list *b)
{
	t_path	*path_a;
	t_path	*path_b;

	path_a = (t_path*)a->content;
	path_b = (t_path*)b->content;
	printf("SWAP [%s %s]\n", path_a->name, path_b->name);
}

static int	ls_swap(t_list *a, t_list *b)
{
	char	*tmp;

	//ls_debug_swap(a, b);
	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
	return (1);
}

void TEST(struct stat file) {

    printf("%ld %hu\n", file.st_mtimespec.tv_nsec, file.st_mode);

    char *nsec = ft_ltoa(file.st_mtimespec.tv_nsec);
    printf("%s\n", nsec);


}

static int	ls_lstcmp(t_list *a, t_list *b, t_app *app)
{
	t_path			*path_a;
	t_path			*path_b;
	__int128_t 		t1;
	__int128_t 		t2;

	path_a = (t_path*)a->content;
	path_b = (t_path*)b->content;

	TEST(path_b->file);

	t1 = 0;
	t1 = ((t1 << 64) | path_a->file.st_mtimespec.tv_nsec) | path_a->file.st_mode;
	t2 = 0;
	t2 = ((t2 << 64) | path_a->file.st_mtimespec.tv_nsec) | path_a->file.st_mode;
	printf("%lld\n", (long long)(t1));
	printf("%ld\n", path_a->file.st_mtimespec.tv_nsec);
	printf("%hu\n", path_a->file.st_mode);
	if (app->opt & OPT_t)
	{
		if ((path_b->file.st_mtimespec.tv_nsec + path_b->file.st_mode) -
                    (path_a->file.st_mtimespec.tv_nsec + path_a->file.st_mode) == 0)
		{
			if (!S_ISDIR(path_a->file.st_mode) && S_ISDIR(path_b->file.st_mode))
				return (-1);
			else
            {
				return (ft_strcmp(path_a->name, path_b->name));
			}
		}
		return ((path_b->file.st_mtimespec.tv_nsec + path_b->file.st_mode) -
                (path_a->file.st_mtimespec.tv_nsec + path_a->file.st_mode));
	}
	return (ft_strcmp(path_a->name, path_b->name));
}

static int	ls_cmp_file_type(t_list *a, t_list *b)
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

void		ls_sort_param(t_app *app, t_list **lst)
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
		while (l && l->next)
		{
			is_dir = ls_cmp_file_type(l, l->next);
			if (is_dir == 1)
				swap = ls_swap(l, l->next);
			else if (ls_lstcmp(l, l->next, app) > 0 && is_dir == -1)
				swap = ls_swap(l, l->next);
			l = l->next;
		//	ft_lstprint(*lst, ls_debug_path);
		//	ft_putendl("_______");
		}
	}
}

void		ls_sort_folder(t_app *app, t_list **lst)
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
		while (l && l->next)
		{
			if (ls_lstcmp(l, l->next, app) > 0)
				swap = ls_swap(l, l->next);
			l = l->next;
		//	ft_lstprint(*lst, ls_debug_path);
		//	ft_putendl("_______");
		}
	}
}
