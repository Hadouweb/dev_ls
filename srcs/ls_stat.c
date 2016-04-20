#include "ft_ls.h"

void	ls_print_stat(struct stat file)
{
	printf("%d\n", file.st_dev);
	printf("%llu\n", file.st_ino);      /* Numéro inœud */
	printf("%d\n", file.st_mode);     /* Protection */
	printf("%d\n", file.st_nlink);    /* Nb liens matériels */
	printf("%d\n", file.st_uid);      /* UID propriétaire */
	printf("%d\n", file.st_gid);      /* GID propriétaire */
	printf("%d\n", file.st_rdev);     /* ID périphérique (si fichier spécial) */
	printf("st_size : %lld\n", file.st_size);     /* Taille totale en octets */
	printf("%d\n", file.st_blksize);  /* Taille de bloc pour E/S */
	printf("%lld\n", file.st_blocks);   /* Nombre de blocs alloués */
	printf("%ld\n", file.st_atime);    /* Heure dernier accès */
	printf("%ld\n", file.st_mtime);    /* Heure dernière modification */
	printf("%ld\n", file.st_ctime);    /* Heure dernier changement état */
}

struct stat ls_get_data_file(char *name)
{
	struct stat file;

	errno = 0;
	stat(name, &file);
	if (errno != 0)
		ls_error_errno("Error in ft_get_data_file ");
	return (file);
}