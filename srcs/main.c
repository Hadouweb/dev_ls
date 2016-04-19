#include "ft_ls.h"

DIR		*ft_opendir(char *file)
{
	DIR 	*dir;

	errno = 0;
	dir = opendir(file);
	if (errno != 0)
		perror("Error in ft_opendir ");
	return (dir);
}

void	ft_readdir(DIR *dir)
{
	struct dirent *dp;

	dp = readdir(dir);
}

int		main(int ac, char **av)
{
	DIR		*dir;

	if (ac > 1)
	{
		dir = ft_opendir(av[1]);
		ft_readdir(dir);
	}
	return (0);
}