#include "ft_ls.h"


void	ls_print_without_option(t_app *app)
{
	t_list	*l;
	t_path	*path;

	l = app->lst;
	while (l)
	{
		path = (t_path*)l->content;
		if (S_ISDIR(path->file.st_mode))
			ls_print_folder(path->name, 0);
		else
			ft_putendl(path->name);
		l = l->next;
	}
	//ft_lstprint(app->lst, ls_debug_path);
}

void	ls_print_result(t_app *app)
{
	if (app->opt & OPT_l)
		printf("option l\n");
	else if (app->opt & OPT_R)
		printf("option R\n");
	else if (app->opt & OPT_a)
		printf("option a\n");
	else if (app->opt & OPT_t)
		printf("option t\n");
	else if (app->opt & OPT_r)
		printf("option r\n");
	else
		ls_print_without_option(app);
}

int		main(int ac, char **av)
{
	int		i;
	t_app	app;

	i = 1;
	ft_bzero(&app, sizeof(t_app));
	if (ac > 1)
	{
		while (i < ac)
		{
			if (av[i][0] == '-')
				ls_option(av[i], &app);
			else
				ls_prepare_to_push(NULL, av[i], &app.lst);
			//ls_print_option_l(av[i]);
			i++;
		}
	}
	if (app.lst == NULL)
		ls_prepare_to_push(NULL, ".", &app.lst);
	ls_lstsort(&app.lst);
	/*ft_lstprint(app.lst, ls_debug_path);
	ls_lstsort(&app.lst);
	printf("_________\n");
	ft_lstprint(app.lst, ls_debug_path);*/
	ls_print_result(&app);
	//ft_printbit(app.opt);
	return (0);
}