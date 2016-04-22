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

# define OPT_l 0x01
# define OPT_R 0x02
# define OPT_a 0x04
# define OPT_t 0x08
# define OPT_r 0x10

typedef struct  	s_app
{
	unsigned char	opt;
}					t_app;

void			ls_print_folder(char *name);
void			ls_error_errno(char *str);
struct passwd	*ls_get_user_data(int uid);
struct group	*ls_get_group_data(int gid);

struct stat 	ls_get_data_file(char *name);
void			ls_print_mode(int st_mode);
void			ls_print_option_l(char *name);

void			ls_print_physical_link(int st_nlink);
void			ls_print_user_group(int st_uid, int st_gid);
void			ls_print_size(int st_size, int st_mode, int st_rdev);
void			ls_print_time(const time_t t);

int 			ls_major(int st_rdev);
int 			ls_minor(int st_rdev);

void			ls_print_stat_debug(struct stat file);
void			ls_print_dirent_debug(struct dirent *dp); 
void			ls_print_group_debug(struct group *group);
void			ls_print_user_debug(struct passwd *user);

void			ls_error(char *str);

void			ls_option(char *opt, t_app *app);

#endif