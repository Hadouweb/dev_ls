#include "ft_ls.h"

struct passwd	*ls_get_user_data(int uid)
{
	struct passwd *user;

	errno = 0;
	user = getpwuid(uid);
	if (errno != 0 || user == NULL)
		ls_error_errno("Error in print_user_data ");
	return (user);
}

void	ls_print_user_data(struct passwd *user)
{
	printf("%s\n", user->pw_name);       /* username */
	printf("%s\n", user->pw_passwd);     /* user password */
	printf("%u\n", user->pw_uid);        /* user ID */
	printf("%u\n", user->pw_gid);        /* group ID */
	printf("%s\n", user->pw_gecos);      /* user information */
	printf("%s\n", user->pw_dir);        /* home directory */
	printf("%s\n", user->pw_shell);      /* shell program */
}