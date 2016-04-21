#include "ft_ls.h"

void	ls_print_physical_link(int st_nlink)
{
	ft_putchar(' ');
	ft_putnbr(st_nlink);
}

void	ls_print_user(int st_uid)
{
	struct passwd *user;

	user = ls_get_user_data(st_uid);
	ft_putchar(' ');
	ft_putstr(user->pw_name);
	ft_putchar(' ');
}

void	ls_print_group(int st_gid)
{
	struct group *group;

	group = ls_get_group_data(st_gid);
	ft_putchar(' ');
	ft_putstr(group->gr_name);
	ft_putchar(' ');
}

void	ls_print_size(int st_size)
{
	ft_putchar(' ');
	ft_putnbr(st_size);
}

void	ls_print_option_l(struct stat file)
{
	ls_print_mode(file.st_mode);
	ls_print_physical_link(file.st_nlink);
	ls_print_user(file.st_uid);
	ls_print_group(file.st_gid);
	ls_print_size(file.st_size);
	ft_putchar('\n');
	//ls_print_stat_debug(file);
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