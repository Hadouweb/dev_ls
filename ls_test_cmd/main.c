#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

int		getdiff(void)
{
	FILE *fp;
	char buff[255];

	fp = fopen("../diff", "r");
	fscanf(fp, "%s", buff);
	fclose(fp);

	return (ft_strlen(buff));
}

void	cmd(char *cmd, char *param)
{
	char str1[256];
	char str2[256];

	sprintf(str2, "../ft_ls -%s %s 2> ../output2 >> ../output2", cmd, param);
	sprintf(str1, "ls -1%s %s 2> ../output1 >> ../output1", cmd, param);

	//rintf("%s\n", str1);
	//printf("%s\n", str2);

	system(str1);
	system(str2);
	system("diff ../output1 ../output2 > ../diff");
	if (getdiff() > 0) {
		printf("\033[031m[ Error    ]\033[0m ft_ls -%s %s\n", cmd, param);
		system("cat ../diff");
	} else
		printf("\033[032m[ Success  ]\033[0m ft_ls -%s %s\n", cmd, param);
}

void	test1(void)
{
	cmd("l", "test");
	cmd("l", "test test");
	cmd("l", "test test file1 file2");
	cmd("l", "file1 file2");
	cmd("l", "file1");
	cmd("l", "");
	cmd("l", "/etc");
	cmd("l", "/etc/");
	cmd("l", "/etc/resolv.conf");
}

int		main(void)
{
	system("make -C ../");
	test1();
	return (0);
}