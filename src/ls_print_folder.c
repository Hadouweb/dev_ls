#include "ft_ls.h"

static void	ls_final_output_folder(t_app *app, t_path *path)
{
	if (app->opt == OPT_R)
	{
		/*if (S_ISDIR(path->file.st_mode))
			ls_set_folder(app, path->name);
		else*/
			ft_putendl(path->name);
	}
	else if (app->opt == 0 || app->opt == OPT_a || app->opt == OPT_t)
		ft_putendl(path->name);
	else if (app->opt & OPT_l)
		ls_set_option_l(app, path);
}

void		ls_recursif_folder(t_app *app, t_listd **lst)
{
	//t_listd *l;
	//t_path	*path;

	//l = *lst;
	//printf("ls_recursif_folder\n");
	//ft_lstd_print(*lst, ls_debug_print_content, 1);
	//while (l) {
	//	path = (t_path *) l->content;
	//	if (path != NULL && path->name != NULL) {
			ls_print_with_option_R(*lst, app);
	//	}
	//	l = l->next;
	//}
}

void		ls_print_folder(t_app *app, t_listd **lst, char *dir)
{
	t_listd	*l;
	t_listd	*tmp;
	t_path	*path;

	//printf("ls_print_folder \n");
	//ft_lstd_print(*lst, ls_debug_print_content, 1);
	//ls_sort(app, lst);
	l = *lst;
	if (app->size_lst > 1)
	{
		ft_putstr(dir);
		ft_putendl(":");
	}
	if (app->opt & OPT_l)
	{
		ft_putstr("total ");
		ft_putnbr(app->ms.total_folder);
		ft_putchar('\n');
	}
	while (l)
	{
		path = (t_path*)l->content;
		ls_final_output_folder(app, path);
		tmp = l;
		l = l->next;
		if (!S_ISDIR(path->file.st_mode))
		{
			ft_strdel(&path->name);
			if (path->link != NULL)
				ft_strdel(&path->link);
			if (path->parent != NULL)
				ft_strdel(&path->parent);
			path = NULL;
			free(path);
		}
	}
	if (app->opt & OPT_R)
		ls_recursif_folder(app, lst);
}