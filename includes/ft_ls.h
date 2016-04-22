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
# include <time.h>
# include <stdio.h>

void			ls_print_folder(char *name);
void			ls_error_errno(char *str);
struct passwd	*ls_get_user_data(int uid);
struct group	*ls_get_group_data(int gid);

struct stat 	ls_get_data_file(char *name);
void			ls_print_mode(int st_mode);
void			ls_print_option_l(char *name);

void			ls_print_physical_link(int st_nlink);
void			ls_print_user_group(int st_uid, int st_gid);
void			ls_print_size(int st_size);
void			ls_print_time(const time_t t);

void			ls_print_stat_debug(struct stat file);
void			ls_print_dirent_debug(struct dirent *dp); 
void			ls_print_group_debug(struct group *group);
void			ls_print_user_debug(struct passwd *user);

#endif