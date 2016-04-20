#include "ft_ls.h"


int		main(int ac, char **av)
{
	struct stat file;
	size_t		rl;
	char		buf[1024];


	if (ac > 1)
	{
		file = ls_get_data_file(av[1]);
		//ls_print_stat(file);
		ls_print_stat(file);
		rl = readlink(av[1], buf, 1024);
		printf("%zu\n", rl);
		printf("%s\n", buf);
		printf("« %s » pointe vers « %s »\n", av[1], buf);
	}
	return (0);
}