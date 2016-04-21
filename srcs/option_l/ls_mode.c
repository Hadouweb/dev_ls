#include "ft_ls.h"

static char	ls_get_file_type(int st_mode)
{
	if (S_ISREG(st_mode))
		return ('-');
	else if (S_ISDIR(st_mode))
		return ('d');
	else if (S_ISCHR(st_mode))
		return ('c');
	else if (S_ISBLK(st_mode))
		return ('b');
	else if (S_ISFIFO(st_mode))
		return ('p');
	else if (S_ISLNK(st_mode))
		return ('l');
	else if (S_ISSOCK(st_mode))
		return ('s');
	return ('-');
}

void		ls_print_mode(int st_mode)
{
	char	str_mode[12];

	ft_memset(str_mode, '-', 11);
	str_mode[11] = '\0';
	str_mode[0] = ls_get_file_type(st_mode);
	str_mode[1] = st_mode & S_IRUSR ? 'r' : '-';
	str_mode[2] = st_mode & S_IWUSR ? 'w' : '-';
	str_mode[3] = st_mode & S_IXUSR ? 'x' : '-';
	str_mode[4] = st_mode & S_IRGRP ? 'r' : '-';
	str_mode[5] = st_mode & S_IWGRP ? 'w' : '-';
	str_mode[6] = st_mode & S_IXGRP ? 'x' : '-';
	str_mode[7] = st_mode & S_IROTH ? 'r' : '-';
	str_mode[8] = st_mode & S_IWOTH ? 'w' : '-';
	str_mode[9] = st_mode & S_IXOTH ? 'x' : '-';
	str_mode[10] = ' ';
	ft_putstr(str_mode);
}