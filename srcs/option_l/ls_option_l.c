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
	ft_putchar(' ');
}

void	ls_print_month(char *m)
{
	m = (ft_strcmp(m, "Jan") == 0) ? ft_memmove(m, "jan", 3) : m;
	m = (ft_strcmp(m, "Feb") == 0) ? ft_memmove(m, "fév", 4) : m;
	m = (ft_strcmp(m, "Mar") == 0) ? ft_memmove(m, "mar", 3) : m;
	m = (ft_strcmp(m, "Apr") == 0) ? ft_memmove(m, "avr", 3) : m;
	m = (ft_strcmp(m, "May") == 0) ? ft_memmove(m, "mai", 3) : m;
	m = (ft_strcmp(m, "Jun") == 0) ? ft_memmove(m, "jui", 3) : m;
	m = (ft_strcmp(m, "Jul") == 0) ? ft_memmove(m, "jul", 3) : m;
	m = (ft_strcmp(m, "Aug") == 0) ? ft_memmove(m, "aoû", 4) : m;
	m = (ft_strcmp(m, "Sep") == 0) ? ft_memmove(m, "sep", 3) : m;
	m = (ft_strcmp(m, "Oct") == 0) ? ft_memmove(m, "oct", 3) : m;
	m = (ft_strcmp(m, "Nov") == 0) ? ft_memmove(m, "nov", 3) : m;
	m = (ft_strcmp(m, "Dec") == 0) ? ft_memmove(m, "déc", 4) : m;
	ft_putstr(m);
}

void	ls_print_time(const time_t t)
{
	char			*str_time;
	char			**split;
	int				i;

	str_time = ctime(&t);
	split = ft_strsplit(str_time, ' ');
	i = 0;
	ft_putstr(split[2]);
	ft_putchar(' ');
	ls_print_month(split[1]);
	ft_putchar(' ');
	split[3][5] = '\0';
	ft_putstr(split[3]);
}

void	ls_print_option_l(char *name)
{
	struct stat file;

	file = ls_get_data_file(name);
	ls_print_mode(file.st_mode);
	ls_print_physical_link(file.st_nlink);
	ls_print_user(file.st_uid);
	ls_print_group(file.st_gid);
	ls_print_size(file.st_size);
	ls_print_time(file.st_mtime);
	ft_putchar(' ');
	ft_putstr(name);
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