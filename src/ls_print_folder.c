#include "ft_ls.h"

static void	ls_final_output_folder(t_app *app, t_path *path)
{
	if (app->opt == 0 || app->opt == OPT_a || app->opt == OPT_t)
		ft_putendl(path->name);
	else if (app->opt & OPT_l)
		ls_set_option_l(app, path);
}

void		ls_print_folder(t_app *app, t_listd **lst, char *dir)
{
	t_listd	*l;
	t_listd	*tmp;
	t_path	*path;

	//printf("ls_print_folder \n");

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
		ft_strdel(&path->name);
		if (path->link != NULL)
			ft_strdel(&path->link);
		free(path);
		free(tmp);
	}
}