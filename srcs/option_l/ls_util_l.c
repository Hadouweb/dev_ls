#include "ft_ls.h"

int 	ls_major(int st_rdev)
{
	return (int)(((int)st_rdev >> 24) & 0xff);
}

int 	ls_minor(int st_rdev)
{
	return (int)((st_rdev) & 0xffffff);
}

char	*ls_get_link(char *name)
{
	char		buf[1024];

	errno = 0;
	readlink(name, buf, 1025);
	if (errno != 0)
		return (NULL);
	return (ft_strdup(buf));
}