/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 18:26:47 by nle-bret          #+#    #+#             */
/*   Updated: 2016/10/30 18:26:49 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "libft.h"
# include <stdio.h>

# define OPT_L 0x01
# define OPT_R 0x02
# define OPT_A 0x04
# define OPT_T 0x08
# define OPT_RMIN 0x10

typedef struct		s_max_size
{
	int				nb_link;
	int				user;
	int				group;
	int				size;
	int				month;
	int				day;
	int				hour_year;
	int				name;
	int				total_folder;
}					t_max_size;

typedef struct		s_entity_full
{
	char			*mode;
	char			*nb_link;
	char			*user;
	char			*group;
	char			*size;
	char			*major;
	char			*minor;
	char			*month;
	char			*day;
	char			*hour_year;
	char			*name;
}					t_entity_full;

typedef struct		s_entity
{
	char			*name;
	struct stat		file;
	t_entity_full	*entity_full;
	t_listd			*child;
	t_max_size		ms;
	struct s_entity	*e_parent;
	char			*rpath;
	char			*link;
	int				errno_code;
}					t_entity;

typedef struct		s_app
{
	unsigned char	opt;
	t_listd			*entity;
	int				token;
	int				nb_param;
	int				nb_dir_param;
	t_max_size		root_ms;
	unsigned char	param_mode;
}					t_app;

int					main(int ac, char **av);

t_listd				*ls_get_node_cmp_time(t_app *app, t_listd **lst,
						t_entity *e);
t_listd				*ls_get_node_cmp(t_app *app, t_listd **lst, t_entity *e);

void				ls_error_errno(char *str);
void				ls_error(char *str);

void				ls_free_entity_full(t_entity_full *e);
void				ls_free_entity(t_entity *e);

void				ls_print_entity_if_exist(t_entity *e);
void				ls_print_opt_l(t_app *app, t_entity *e);
void				ls_print_no_option(t_app *app, t_entity *e);
void				ls_print_entity(t_app *app, t_entity *e);
void				ls_foreach_entity(t_app *app);

struct passwd		*ls_get_user_data(int uid);
struct group		*ls_get_group_data(int gid);
t_listd				*ls_get_entity_child(t_app *app, char *name,
						t_entity *parent);

void				ls_option(char *opt, t_app *app);

void				ls_print_child(t_app *app, t_entity *e);

void				ls_set_child(t_app *app, t_entity *e, t_listd *lst_child);
void				ls_set_entity_param(t_app *app, t_entity *e);
void				ls_push_entity(t_app *app, t_entity *parent,
					char *name, t_listd **lst);
int					ls_set_filestat(t_app *app, t_entity *e);

void				ls_readdir(DIR *dir, t_listd **lst, t_app *app,
					t_entity *parent);
void				ls_closedir(DIR *dir);
int					ls_swap(t_listd *a, t_listd *b);

void				ls_sort_entity_param(t_app *app);
void				ls_push_after_sort(t_listd **lst, t_entity *e, t_app *app);

void				ls_set_mode(t_entity *e);

void				ls_print_adjust_space_left(char *str, int size);
void				ls_print_adjust_space_right(char *str, int size);
void				ls_print_adjust_size(t_entity *e, t_max_size ms);
void				ls_print_line_opt_l(t_entity *e, t_max_size ms);

void				ls_set_user(t_entity *e, t_max_size *ms);
void				ls_set_group(t_entity *e, t_max_size *ms);
char				*ls_format_hour_year(char *str);
void				ls_set_time(t_entity *e, t_max_size *ms);
void				ls_set_option_l(t_entity *e, t_max_size *ms);

void				ls_set_nb_link(t_entity *e, t_max_size *ms);
void				ls_set_link(t_entity *e);
void				ls_set_size(t_entity *e, t_max_size *ms);

int					ls_major(int st_rdev);
int					ls_minor(int st_rdev);
char				*ls_get_link(char *name);
int					ls_diff_six_month(time_t t);

#endif
