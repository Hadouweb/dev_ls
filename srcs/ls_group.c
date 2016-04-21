#include "ft_ls.h"

struct group	*ls_get_group_data(int gid)
{
	struct group *group;

	errno = 0;
	group = getgrgid(gid);
	if (errno != 0 || group == NULL)
		ls_error_errno("Error in ls_get_group_data ");
	return (group);
}
