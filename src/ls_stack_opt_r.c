#include "ft_ls.h"

void		ls_print_entity_stack(t_app *app, t_entity *e)
{
	if (app->opt & OPT_l && e->errno_code == 0) {
		if (S_ISDIR(e->file.st_mode)) {
			if (app->nb_param > 1) {
				ft_putstr(e->name);
				ft_putendl(":");
			}
			ft_putstr("total ");
			ft_putnbr(e->ms.total_folder);
			ft_putchar('\n');
			ls_print_child(app, e);
		} else
			ls_print_line_opt_l(e, app->root_ms);
	} else {
		if (S_ISDIR(e->file.st_mode)) {
			ls_print_child(app, e);
		} else
			ls_print_entity_if_exist(app, e);
	}
}

void		ls_run_stack(t_app *app)
{
	t_listd 	*l;
	t_entity	*e;

	l = app->stack;
	//printf("Run stack:\n");
	//ft_lstd_print(app->stack, ls_debug_print_content, 0);
	//printf("___________\n");
	while (l)
	{
		e = (t_entity *)l->content;
		//e->name = e->rpath;
		//e->rpath = ft_strjoin(ft_strjoin(e->e_parent->rpath, "/"), e->rpath);
		//ls_set_entity_param(app, e);
		if (e) {
			ls_set_child2(app, e, ls_get_entity_child(app, e->rpath, e));
			ls_print_child2(app, e);
		}
		l = l->next;
	}
}

void		ls_push_stack(t_app *app, t_entity *e)
{
	//printf("1___%s %s %s\n", e->name, e->rpath, e->e_parent->name);
	ls_push_entity(app, e->e_parent, e->name, &app->stack);
	//printf("___%s %s %s\n", e->name, e->rpath, e->e_parent->name);
}