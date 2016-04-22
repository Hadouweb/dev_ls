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