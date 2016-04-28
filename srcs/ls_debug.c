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
	printf("st_ctime : %ld\n", file.st_ctime);    /* Heure dernier changement état */
	printf("__%d\n", S_IFMT);
}

void	ls_debug_path(void *content)
{
	t_path	*path;

	path = (t_path*)content;
	printf("\nname : %s\n", path->name);
	printf("link : %s\n", path->link);
	//ls_print_stat_debug(path->file);
}

void	ls_debug_max_size(t_app *app)
{
	printf("size nb_link : %d\n", app->ms.nb_link);
	printf("size user : %d\n", app->ms.user);
	printf("size group : %d\n", app->ms.group);
	printf("size size : %d\n", app->ms.size);
	printf("size major : %d\n", app->ms.major);
	printf("size minor : %d\n", app->ms.minor);
	printf("size time : %d\n", app->ms.time);
	printf("size name : %d\n", app->ms.name);
}

void	ls_debug_prepared_data(void *content)
{
	t_prepa		*p;

	p = (t_prepa*)content;
	printf("Mode : %s\n", p->mode);
	printf("nb link : %s\n", p->nb_link);
	printf("user : %s\n", p->user);
	printf("group : %s\n", p->group);
	printf("time : %s\n", p->time);
}

void	ls_print_dirent_debug(struct dirent *dp) 
{
	printf("d_ino : %llu\n", dp->d_ino);
	printf("d_reclen : %d\n", dp->d_reclen);
	printf("d_type : %hhu\n", dp->d_type);
	printf("d_name : %s\n", dp->d_name);
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