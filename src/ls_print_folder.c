#include "ft_ls.h"

static void	ls_final_output_folder(t_app *app, t_path *path)
{
	if (app->opt == OPT_R)
	{
		ft_putendl(path->name);
	}
	else if (app->opt == 0 || app->opt == OPT_a || app->opt == OPT_t)
		ft_putendl(path->name);
	else if (app->opt & OPT_l)
		ls_set_option_l(app, path);
}

void		ls_print_folder(t_app *app, t_listd **lst, char *dir)
{
	t_listd	*l;
	t_listd	*tmp;
	t_path	*path;
	int 	token;

	//printf("ls_print_folder \n");
	//ft_lstd_print(*lst, ls_debug_print_content, 1);
	//ls_sort(app, lst);
	l = *lst;
	if (dir)
		;
	/*if (app->size_lst > 1)
	{
		ft_putstr(dir);
		ft_putendl(":");
	}*/
	if (app->opt & OPT_l)
	{
		ft_putstr("total ");
		ft_putnbr(app->ms.total_folder);
		ft_putchar('\n');
	}
	token = 0;
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
		token++;
	}
	//if (token > 0)
	if (app->opt & OPT_R)
		ls_print_with_option_R(*lst, app);
}