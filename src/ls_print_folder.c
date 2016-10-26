#include "ft_ls.h"

/*static void	ls_final_output_folder(t_app *app, t_entity *path)
{
	if (app->opt == 0 || app->opt == OPT_a || app->opt == OPT_t)
		ft_putendl(path->name);
	else if (app->opt & OPT_l)
		ls_set_option_l(app, path);
	else if (app->opt & OPT_R)
		ft_putendl(path->name);
}*/

/*void		ls_print_folder(t_app *app, t_listd **lst, char *dir)
{
	t_listd	*l;
	t_listd	*tmp;
	t_entity	*path;

	l = *lst;
	if (dir)
		;
	if (app->opt & OPT_l)
	{
		ft_putstr("total ");
		ft_putnbr(app->ms.total_folder);
		ft_putchar('\n');
	}
	while (l)
	{
		path = (t_entity*)l->content;
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
		} else {
			ft_lstd_pushback(&app->stack, (void*)path, sizeof(t_entity));
		}
	}
}*/