#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include <sys/stat.h> 
# include <unistd.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <stdio.h>
# include "libft.h"

# define OPT_l 0x01
# define OPT_R 0x02
# define OPT_a 0x04
# define OPT_t 0x08
# define OPT_r 0x10

typedef struct 		s_path
{
	char			*name;
	struct stat 	file;
	char			*parent;
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
	int				time;
	int				name;
	int				total_folder;
}					t_max_size;

typedef struct  	s_app
{
	unsigned char	opt;
	t_listd			*lst;
	t_listd			*prepa;
	t_max_size		ms;
	t_col			col;
	int 			token;
	int 			size_lst;
}					t_app;

DIR				*ls_opendir(char *file);
void			ls_readdir(DIR *dir, t_listd **lst, char *origin, t_app *app);
void			ls_closedir(DIR *dir);

t_listd			*ls_get_node_cmp(t_listd **lst, t_path *path);
t_listd			*ls_get_node_cmp_time(t_listd **lst, t_path *path);

void			ls_push_after_sort(t_listd **lst, t_path *path, t_app *app);
void			ls_sort_param(t_app *app, t_listd **lst);
void			ls_sort(t_app *app, t_listd **lst);

void			ls_set_file_data(char *rpath, char *name, t_listd **lst, t_app *app);
void			ls_set_option_l(t_app *app, t_path *path);
void			ls_set_folder(t_app *app, char *name);

void			ls_print_result(t_app *app);

void			ls_print_folder(t_app *app, t_listd **lst, char *dir);

void			ls_option(char *opt, t_app *app);

struct passwd	*ls_get_user_data(int uid);
struct group	*ls_get_group_data(int gid);
int				ls_get_data_file(char *name, int is_link, struct stat *file);

void			ls_error_errno(char *str);
void			ls_error(char *str);

void			ls_print_stat_debug(struct stat file);
void			ls_debug_path(void *content);
void			ls_debug_max_size(t_app *app);
void			ls_debug_prepared_data(void *content);
void			ls_print_dirent_debug(struct dirent *dp);
void			ls_print_group_debug(struct group *group);
void			ls_print_user_debug(struct passwd *user);
void			ls_debug_print_content(void *content);
void			ls_debug_swap(t_listd *a, t_listd *b);

int				ls_major(int st_rdev);
int				ls_minor(int st_rdev);
char			*ls_get_link(char *name);
int				ls_diff_six_month(time_t t);

void			ls_set_user(t_prepa *p, int st_uid, t_app *app);
void			ls_set_group(t_prepa *p, int st_gid, t_app *app);
void			ls_set_size(t_prepa *p, struct stat file, t_app *app);
void			ls_set_time(t_prepa *p, const time_t t, t_app *app);
void			ls_set_nb_link(t_prepa *p, int st_nlink, t_app *app);
void			ls_set_path(t_prepa *p, char *path, char *link, t_app *app);

void			ls_print_adjust_space_left(char *str, int size);
void			ls_print_adjust_space_right(char *str, int size);
void			ls_clear_node_prepared(t_listd *node);
void			ls_print_adjust_size(t_prepa *p, t_app *app);
void			ls_print_option_l(t_app *app);

void			ls_set_mode(t_prepa *p, int st_mode);
void 			ls_print_with_option_R(t_listd *lst, t_app *app);

#endif
