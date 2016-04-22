#include "ft_ls.h"

int 	ls_major(int st_rdev)
{
	return (int)(((int)st_rdev >> 24) & 0xff);
}

int 	ls_minor(int st_rdev)
{
	return (int)((st_rdev) & 0xffffff);
}