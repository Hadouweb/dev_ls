#include "ft_ls.h"

t_listd	*ls_get_node_cmp_time(t_listd **lst, t_entity *path)
{
	__uint128_t 	t1;
	__uint128_t 	t2;
	t_listd 		*l;
	t_entity 		*path_cmp;

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

t_listd	*ls_get_node_cmp(t_app *app, t_listd **lst, t_entity *e)
{
	t_listd 		*l;
	t_entity 		*path_cmp;
	int 			cmp;

	l = *lst;
	while (l)
	{
		path_cmp = (t_entity*)l->content;
		if (app->opt & OPT_r && e->errno_code == 0)
			cmp = ft_strcmp(path_cmp->name, e->name);
		else
			cmp = ft_strcmp(e->name, path_cmp->name);
		//printf("%s %s %d\n", path->name, path_cmp->name, cmp);
		if (cmp != 0)
		{
			if (cmp < 0)
				return l;
		}
		l = l->next;
	}
	return NULL;
}