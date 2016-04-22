#include "ft_ls.h"

void	ls_error_errno(char *str)
{
	if (str != NULL)
		perror(str);
	else
		perror("");
	exit(1);
}

void	ls_error(char *str)
{
	if (str != NULL)
		ft_putendl_fd(str, 2);
	else
		ft_putendl_fd("Error", 2);
	exit(1);
}