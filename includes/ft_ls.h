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

typedef struct 		s_path
{
	char			*name;
	struct stat 	file;
	char			*link;

}					t_path;

typedef struct 		s_col
{
	int 			nbr_link;
}					t_col;

typedef struct  	s_prepa
{
	char			mode[12];
	char			*nb_link;
	char			*user;
	char			*group;
	char			*size;
	char			*major;
	char			*minor;
	char			*time;
	char			*name;
}					t_prepa;

typedef struct 		s_max_size
{
	int				nb_link;
	int				user;
	int				group;
	int				size;
	int				major;
	int				minor;
	int				time;
	int				name;
}					t_max_size;

typedef struct  	s_app
{
	unsigned char	opt;
	t_list			*lst;
	t_list			*prepa;
	t_max_size		ms;
	t_col			col;
	int 			size_lst;
}					t_app;

void			ls_print_folder(t_app *app, char *name);
void			ls_error_errno(char *str);
struct passwd	*ls_get_user_data(int uid);
struct group	*ls_get_group_data(int gid);
void			ls_prepare_for_option_l(t_app *app, t_path *path);

struct stat 	ls_get_data_file(char *name, int is_link);
void			ls_prepare_mode(t_prepa *p, int st_mode);
void			ls_print_option_l(t_app *app);

void			ls_prepare_nb_link(t_prepa *p, int st_nlink, t_app *app);
void			ls_prepare_user(t_prepa *p, int st_uid, t_app *app);
void			ls_prepare_group(t_prepa *p, int st_gid, t_app *app);
void			ls_prepare_size(t_prepa *p, struct stat file, t_app *app);
void			ls_prepare_time(t_prepa *p, const time_t t, t_app *app);
void			ls_prepare_path(t_prepa *p, char *path, char *link, t_app *app);

int 			ls_major(int st_rdev);
int 			ls_minor(int st_rdev);
char			*ls_get_link(char *name);
int				ls_diff_six_month(time_t t);

void			ls_print_stat_debug(struct stat file);
void			ls_print_dirent_debug(struct dirent *dp); 
void			ls_print_group_debug(struct group *group);
void			ls_print_user_debug(struct passwd *user);
void			ls_debug_path(void *content);
void			ls_debug_prepared_data(void *content);
void			ls_debug_max_size(t_app *app);

void			ls_error(char *str);

void			ls_option(char *opt, t_app *app);

void			ls_lstsort_param(t_list **lst);
void			ls_lstsort_folder(t_list **lst);

void	ls_prepare_file_data(char *relativ_path, char *name, t_list **lst);

void	ls_print_result(t_app *app);

void	ls_adjust_space(int max);

#endif