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
			i++;
		}
		//ls_print_option_l(av[1]);
		//ls_print_stat_debug(file);
	}
	ft_printbit(app.opt);
	return (0);
}