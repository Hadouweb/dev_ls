#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include <sys/stat.h> 
# include <unistd.h>
# include <pwd.h>
# include <grp.h>
# include <stdio.h>

void	ls_print_folder(char *name);
void	ls_error_errno(char *str);
struct stat ls_get_data_file(char *name);
void	ls_print_stat(struct stat file);
void	ls_print_user_data(struct passwd *user);
struct passwd	*ls_get_user_data(int uid);
struct group	*ls_get_group_data(int gid);
void	ls_print_group_data(struct group *group);

#endif