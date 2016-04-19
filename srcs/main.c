#include "ft_ls.h"

int		main(int ac, char **av)
{
	struct stat file;
	struct group *group;

	if (ac > 1)
	{
		file = ls_get_data_file(av[1]);
		group = ls_get_group_data(file.st_gid);
		ls_print_group_data(group);
	}
	return (0);
}