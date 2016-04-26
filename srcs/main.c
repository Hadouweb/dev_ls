#include "ft_ls.h"

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
			i++;
		}
	}
	if (app.lst == NULL)
		ls_prepare_to_push(NULL, ".", &app.lst);
	ls_lstsort(&app.lst);
	ls_print_result(&app);
	sleep(5);
	return (0);
}