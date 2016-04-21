#include "ft_ls.h"


int		main(int ac, char **av)
{
	struct stat file;


	if (ac > 1)
	{
		file = ls_get_data_file(av[1]);
		//ls_print_stat(file);
	}
	return (0);
}