#include "ft_ls.h"

void	ls_error_errno(char *str)
{
	if (str != NULL)
		perror(str);
	else
		perror("");
	exit(1);
}