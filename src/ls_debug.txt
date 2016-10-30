#include "ft_ls.h"

void	ls_print_stat_debug(struct stat file)
{
	printf("st_dev : %d\n", file.st_dev);		/* ID du périphérique contenant le fichier */
	printf("st_ino : %llu\n", file.st_ino);      /* Numéro inœud */
	printf("st_mode : %d\n", file.st_mode);     /* Protection */
	printf("st_nlink : %d\n", file.st_nlink);    /* Nb liens matériels */
	printf("st_uid : %d\n", file.st_uid);      /* UID propriétaire */
	printf("st_gid : %d\n", file.st_gid);      /* GID propriétaire */
	printf("st_rdev : %d\n", file.st_rdev);     /* ID périphérique (si fichier spécial) */
	printf("st_size : %lld\n", file.st_size);     /* Taille totale en octets */
	printf("st_blksize : %d\n", file.st_blksize);  /* Taille de bloc pour E/S */
	printf("st_blocks : %lld\n", file.st_blocks);   /* Nombre de blocs alloués */
	printf("st_atime : %ld\n", file.st_atime);    /* Heure dernier accès */
	printf("st_mtime : %ld\n", file.st_mtime);    /* Heure dernière modification */
	printf("st_ctime : %ld\n\n", file.st_ctime);    /* Heure dernier changement état */
}

void	ls_debug_swap(t_listd *a, t_listd *b)
{
	t_entity	*path_a;
	t_entity	*path_b;

	path_a = (t_entity*)a->content;
	path_b = (t_entity*)b->content;
	printf("SWAP [%s %s]\n", path_a->name, path_b->name);
}

void	ls_debug_print_entity_full(void *content)
{
	t_entity 		*e;
	t_entity_full 	*e_full;

	e = (t_entity*)content;
	e_full = e->entity_full;
	ft_putchar('\n');
	ft_putendl(e->name);
	if (e_full != NULL) {
		ft_putendl(e_full->group);
		ft_putendl(e_full->major);
		ft_putendl(e_full->minor);
		ft_putendl(e_full->mode);
		ft_putendl(e_full->nb_link);
		ft_putendl(e_full->size);
		ft_putendl(e_full->month);
		ft_putendl(e_full->day);
		ft_putendl(e_full->hour_year);
		ft_putendl(e_full->user);
	}
}

void	ls_debug_print_content(void *content)
{
	t_entity *e;

	e = (t_entity*)content;
	if (e != NULL && e->name != NULL) {
		ft_putstr(e->name);
		ft_putstr(" ");
		if (e->e_parent)
			ft_putstr(e->e_parent->name);
		else
			ft_putstr("NULL");
	}
}

void	ls_debug_entity(void *content)
{
	t_entity	*e;

	e = (t_entity*)content;
	printf("\nname : %s\n", e->name);
	printf("link : %s\n", e->link);
	ls_print_stat_debug(e->file);
}

void	ls_debug_max_size(t_max_size ms)
{
	printf("size nb_link : %d\n", ms.nb_link);
	printf("size user : %d\n", ms.user);
	printf("size group : %d\n", ms.group);
	printf("size size : %d\n", ms.size);
	printf("size month : %d\n", ms.month);
	printf("size day : %d\n", ms.day);
	printf("size hour_year : %d\n", ms.hour_year);
	printf("size name : %d\n", ms.name);
}

void	ls_debug_prepared_data(void *content)
{
	t_entity_full		*p;

	p = (t_entity_full*)content;
	printf("Mode : %s\n", p->mode);
	printf("nb link : %s\n", p->nb_link);
	printf("user : %s\n", p->user);
	printf("group : %s\n", p->group);
	printf("size : %s\n", p->size);
	printf("major : %s\n", p->major);
	printf("minor : %s\n", p->minor);
	printf("month : %s\n", p->month);
	printf("day : %s\n", p->day);
	printf("hour_year : %s\n", p->hour_year);
	printf("name : %s\n", p->name);
}

void	ls_print_dirent_debug(struct dirent *dp) 
{
	printf("d_ino : %llu\n", dp->d_ino);
	printf("d_reclen : %d\n", dp->d_reclen);
	printf("d_type : %hhu\n", dp->d_type);
	printf("d_name : %s\n\n", dp->d_name);
}

void	ls_print_group_debug(struct group *group)
{
	int		i;

	i = 0;
	printf("gr_name : %s\n", group->gr_name);    /* Nom du groupe.          */
	printf("gr_passwd : %s\n", group->gr_passwd);  /* Mot de passe du groupe. */
	printf("gr_gid : %u\n", group->gr_gid);     /* ID du groupe.           */
	while (group->gr_mem[i])
		printf("gr_mem : %s\n", group->gr_mem[i++]);     /* Membres du groupe.      */
}

void	ls_print_user_debug(struct passwd *user)
{
	printf("pw_name : %s\n", user->pw_name);       /* username */
	printf("pw_passwd : %s\n", user->pw_passwd);     /* user password */
	printf("pw_uid : %u\n", user->pw_uid);        /* user ID */
	printf("pw_gid : %u\n", user->pw_gid);        /* group ID */
	printf("pw_gecos : %s\n", user->pw_gecos);      /* user information */
	printf("pw_dir : %s\n", user->pw_dir);        /* home directory */
	printf("pw_shell : %s\n", user->pw_shell);      /* shell program */
}