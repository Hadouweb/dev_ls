#include "ft_ls.h"

void		ls_free_entity_full(t_entity_full *e)
{
	ft_strdel(&e->name);
	ft_strdel(&e->day);
	if (e->group)
		ft_strdel(&e->group);
	ft_strdel(&e->hour_year);
	ft_strdel(&e->major);
	ft_strdel(&e->minor);
	ft_strdel(&e->month);
	ft_strdel(&e->nb_link);
	ft_strdel(&e->size);
	ft_strdel(&e->user);
}

void		ls_free_entity(t_entity *e)
{
	if (e->name != NULL)
		ft_strdel(&e->name);
	if (e->entity_full)
		ls_free_entity_full(e->entity_full);
	if (e->link)
		ft_strdel(&e->link);
	if (e->rpath)
		ft_strdel(&e->rpath);
}