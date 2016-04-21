#include "ft_ls.h"

void	ls_print_stat(struct stat file)
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

char		ls_get_file_type(int st_mode)
{
	if (S_ISREG(st_mode))
		return ('-');
	else if (S_ISDIR(st_mode))
		return ('d');
	else if (S_ISCHR(st_mode))
		return ('c');
	else if (S_ISBLK(st_mode))
		return ('b');
	else if (S_ISFIFO(st_mode))
		return ('p');
	else if (S_ISLNK(st_mode))
		return ('l');
	else if (S_ISSOCK(st_mode))
		return ('s');
	return ('-');
}

void		ls_print_mode(int st_mode)
{
	char	str_mode[12];

	ft_memset(str_mode, '-', 11);
	str_mode[11] = '\0';
	str_mode[0] = ls_get_file_type(st_mode);
	str_mode[1] = st_mode & S_IRUSR ? 'r' : '-';
	str_mode[2] = st_mode & S_IWUSR ? 'w' : '-';
	str_mode[3] = st_mode & S_IXUSR ? 'x' : '-';
	str_mode[4] = st_mode & S_IRGRP ? 'r' : '-';
	str_mode[5] = st_mode & S_IWGRP ? 'w' : '-';
	str_mode[6] = st_mode & S_IXGRP ? 'x' : '-';
	str_mode[7] = st_mode & S_IROTH ? 'r' : '-';
	str_mode[8] = st_mode & S_IWOTH ? 'w' : '-';
	str_mode[9] = st_mode & S_IXOTH ? 'x' : '-';
	str_mode[10] = ' ';
	ft_putstr(str_mode);
}

struct stat ls_get_data_file(char *name)
{
	struct stat file;
	char		buf[1024];

	errno = 0;
	readlink(name, buf, 1025);
	if (errno != 0)
	{
		errno = 0;
		stat(name, &file);
	}
	else
		lstat(name, &file);
	if (errno != 0)
		ls_error_errno("Error in ft_get_data_file ");
	ls_print_mode(file.st_mode);
	return (file);
}