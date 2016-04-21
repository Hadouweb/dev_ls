#include "ft_ls.h"

int		main(int ac, char **av)
{
	if (ac > 1)
	{
		ls_print_option_l(av[1]);
		//ls_print_stat_debug(file);
	}
	return (0);
}