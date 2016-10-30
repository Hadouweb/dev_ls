#include "ft_ls.h"

t_listd	*ls_get_node_cmp_time(t_app *app, t_listd **lst, t_entity *e)
{
	__uint128_t 	t1;
	__uint128_t 	t2;
	t_listd 		*l;
	t_entity 		*e_cmp;
	int 			cmp;

	t1 = (__uint128_t) e->file.st_mtimespec.tv_sec
				 << 64 | e->file.st_mtimespec.tv_nsec;

	l = *lst;
	while (l)
	{
		e_cmp = (t_entity*)l->content;
		t2 = (__uint128_t) e_cmp->file.st_mtimespec.tv_sec
					 << 64 | e_cmp->file.st_mtimespec.tv_nsec;

		if (app->opt & OPT_r && t1 < t2)
			return l;
		else if (!(app->opt & OPT_r) && t1 > t2)
			return l;

		if (t2 - t1 == 0) {
			if (app->opt & OPT_r)
				cmp = ft_strcmp(e_cmp->name, e->name);
			else
				cmp = ft_strcmp(e->name, e_cmp->name);
			if (cmp < 0)
				return l;
		}
		l = l->next;
	}
	return NULL;
}

t_listd	*ls_get_node_cmp(t_app *app, t_listd **lst, t_entity *e)
{
	t_listd 		*l;
	t_entity 		*e_cmp;
	int 			cmp;

	l = *lst;
	while (l)
	{
		e_cmp = (t_entity*)l->content;
		if (app->opt & OPT_r)
			cmp = ft_strcmp(e_cmp->name, e->name);
		else
			cmp = ft_strcmp(e->name, e_cmp->name);
		if (cmp < 0)
			return l;
		l = l->next;
	}
	return NULL;
}