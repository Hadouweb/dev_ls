#include "ft_ls.h"

t_listd	*ls_get_node_cmp_time(t_listd **lst, t_entity *path)
{
	__uint128_t 	t1;
	__uint128_t 	t2;
	t_listd 		*l;
	t_entity 			*path_cmp;

	t1 = (__uint128_t) path->file.st_mtimespec.tv_sec
				 << 64 | path->file.st_mtimespec.tv_nsec;

	l = *lst;
	while (l)
	{
		path_cmp = (t_entity*)l->content;
		if (ft_strcmp(path->name, path_cmp->name) != 0)
		{
			t2 = (__uint128_t) path_cmp->file.st_mtimespec.tv_sec
						 << 64 | path_cmp->file.st_mtimespec.tv_nsec;

			if (t2 - t1 == 0 && ft_strcmp(path->name, path_cmp->name) < 0)
			{
				//printf("t1:[%s] = t2:[%s]\n", path->name, path_cmp->name);
				return l;
			}
			/*printf("t1:[%s][%ld %ld] t2[%s][%ld %ld]\n",
				   path->name, path->file.st_mtimespec.tv_sec,
				   path->file.st_mtimespec.tv_nsec,
				   path_cmp->name, path_cmp->file.st_mtimespec.tv_sec,
				   path_cmp->file.st_mtimespec.tv_nsec);*/
			if (t1 > t2)
			{
				//printf("t1:[%s] > t2[%s]\n", path->name, path_cmp->name);
				return l;
			}
		}
		l = l->next;
	}
	return NULL;
}

t_listd	*ls_get_node_cmp(t_listd **lst, t_entity *path)
{
	t_listd 		*l;
	t_entity 			*path_cmp;

	l = *lst;
	while (l)
	{
		path_cmp = (t_entity*)l->content;
		if (ft_strcmp(path->name, path_cmp->name) != 0)
		{
			/*if (!ft_isalpha(path->name[0]) && ft_isalpha(path_cmp->name[0]))
				return l;
			if (ft_isupper(path->name[0]) && !ft_isupper(path_cmp->name[0]))
				return l;
			if (((ft_isupper(path->name[0]) && ft_isupper(path_cmp->name[0])) ||
					(ft_islower(path->name[0]) && ft_islower(path_cmp->name[0]))) &&
					ft_strcmp(path->name, path_cmp->name) < 0)
				return l;*/
			if (ft_strcmp(path->name, path_cmp->name) < 0)
				return l;
		}
		l = l->next;
	}
	return NULL;
}