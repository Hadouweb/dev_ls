#include "ft_ls.h"

struct passwd	*ls_get_user_data(int uid)
{
	struct passwd *user;

	errno = 0;
	user = getpwuid(uid);
	if (errno != 0 || user == NULL)
		;//ls_error_errno("Error in ls_get_user_data ");
	return (user);
}

struct group	*ls_get_group_data(int gid)
{
	struct group *group;

	errno = 0;
	group = getgrgid(gid);
	if (errno != 0 || group == NULL)
		;//ls_error_errno("Error in ls_get_group_data ");
	return (group);
}
