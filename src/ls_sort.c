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

void		TEST(time_t now) 
{
    struct tm *tm;

    if ((tm = localtime (&now)) == NULL) {
        printf ("Error extracting time stuff\n");
        //return;
    }

       printf ("%04d-%02d-%02d %02d:%02d:%02d\n",
        tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
        tm->tm_hour, tm->tm_min, tm->tm_sec);
}

static int	ls_lstcmp(t_list *a, t_list *b, t_app *app)
{
	t_path	*path_a;
	t_path	*path_b;

	path_a = (t_path*)a->content;
	path_b = (t_path*)b->content;
	if (app->opt & OPT_t)
	{
		//TEST(path_b->file.st_mtime);
		if (path_b->file.st_mtime - path_a->file.st_mtime == 0)
		{
			//TEST(path_b->file.st_mtime);
			//TEST(path_a->file.st_mtime);
			if (!S_ISDIR(path_a->file.st_mode) && S_ISDIR(path_b->file.st_mode))
				return (-1);
			else {
				printf("%s : %s", path_b->name, path_a->name);
				printf("%d\n", ft_strcmp(path_a->name, path_b->name));
				//printf("\n\n");
				if (ft_strcmp(path_b->name, path_a->name) < 0)
					return 1;
				return (ft_strcmp(path_b->name, path_a->name));
			}
		}
		return (path_b->file.st_mtime - path_a->file.st_mtime);
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
