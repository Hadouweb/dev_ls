#include "ft_ls.h"

void	ls_prepare_to_push(char *name, t_app *app)
{
	t_path	*path;
	char	*link;

	if ((path = (t_path*)ft_memalloc(sizeof(t_path))) == NULL)
		ls_error("Error: malloc");
	path->name = ft_strdup(name);
	if ((path->link = ls_get_link(name)) == NULL)
		stat(name, &path->file);
	else
		lstat(name, &path->file);
	ft_lstpush_back(&app->lst, (void*)path, sizeof(t_path));
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
			ls_prepare_to_push(av[i], &app);
			//ls_print_option_l(av[i]);
			i++;
		}
	}
	ft_lstprint(app.lst, ls_debug_path);
	ls_lstsort(&app.lst);
	printf("_________\n");
	ft_lstprint(app.lst, ls_debug_path);
	//ft_printbit(app.opt);
	return (0);
}