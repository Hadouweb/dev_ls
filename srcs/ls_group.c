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

void	ls_print_group_data(struct group *group)
{
	int		i;

	i = 0;
	printf("%s\n", group->gr_name);    /* Nom du groupe.          */
	printf("%s\n", group->gr_passwd);  /* Mot de passe du groupe. */
	printf("%u\n", group->gr_gid);     /* ID du groupe.           */
	while (group->gr_mem[i])
		printf("%s\n", group->gr_mem[i++]);     /* Membres du groupe.      */
}