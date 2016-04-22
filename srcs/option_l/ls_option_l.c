#include "ft_ls.h"

int 	ls_major(int st_rdev)
{
	return (int)(((int)st_rdev >> 24) & 0xff);
}

int 	ls_minor(int st_rdev)
{
	return (int)((st_rdev) & 0xffffff);
}

void	ls_print_option_l(char *name)
{
	struct stat file;

	file = ls_get_data_file(name);
	ls_print_mode(file.st_mode);
	ls_print_physical_link(file.st_nlink);
	ls_print_user_group(file.st_uid, file.st_gid);
	ls_print_size(file.st_size);
	ls_print_time(file.st_mtime);
	ft_putchar(' ');
	ft_putstr(name);
	ft_putchar('\n');
	ls_print_stat_debug(file);
	printf("Major %d %d\n", ls_major(file.st_rdev), ls_minor(file.st_rdev));
}

struct stat ls_get_data_file(char *name)
{
	struct stat file;
	char		buf[1024];

	errno = 0;
	readlink(name, buf, 1025);
	if (errno != 0)
	{
		errno = 0;
		stat(name, &file);
	}
	else
		lstat(name, &file);
	if (errno != 0)
		ls_error_errno("Error in ft_get_data_file ");
	return (file);
}