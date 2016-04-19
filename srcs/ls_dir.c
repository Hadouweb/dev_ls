#include "ft_ls.h"

DIR		*ls_opendir(char *file)
{
	DIR 	*dir;

	errno = 0;
	dir = opendir(file);
	if (errno != 0)
		ls_error_errno("Error in ls_opendir ");
	return (dir);
}

void	ls_print_dirent(struct dirent *dp) 
{
	printf("%llu\n", dp->d_ino);
	printf("%d\n", dp->d_reclen);
	printf("%hhu\n", dp->d_type);
	printf("%s\n", dp->d_name);
}

void	ls_readdir(DIR *dir)
{
	struct dirent *dp;

	errno = 0;
	while ((dp = readdir(dir)) != NULL)
	{
		if (errno != 0)
			ls_error_errno("Error in ls_readdir ");
		printf("type : %hhu | name : %s\n", dp->d_type, dp->d_name);
	}
}

void	ls_closedir(DIR *dir)
{
	errno = 0;
	closedir(dir);
	if (errno != 0)
		ls_error_errno("Error in ls_closedir ");
}

void	ls_print_folder(char *name)
{
	DIR		*dir;
	
	dir = ls_opendir(name);
	ls_readdir(dir);
	ls_closedir(dir);
}