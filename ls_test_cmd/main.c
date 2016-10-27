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
	char str_cmd[256];

	if (ft_strlen(cmd) > 0)
		sprintf(str_cmd, "-%s %s", cmd, param);
	else
		sprintf(str_cmd, "%s%s", cmd, param);

	sprintf(str2, "../ft_ls %s 2> ../output2 >> ../output2", str_cmd);
	sprintf(str1, "ls -1%s %s 2> ../output1 >> ../output1", cmd, param);

	//rintf("%s\n", str1);
	//printf("%s\n", str2);

	system(str1);
	system(str2);
	system("diff ../output1 ../output2 > ../diff");
	if (getdiff() > 0) {
		printf("\033[031m[ Error    ]\033[0m ft_ls %s\n", str_cmd);
		system("cat ../diff");
	} else
		printf("\033[032m[ Success  ]\033[0m ft_ls %s\n", str_cmd);
}

void	test0(void)
{
	printf("\033[035m****************** test0 ******************\033[0m\n");
	cmd("", "test");
	cmd("", "test test");
	cmd("", "file3 test test file1 file2");
	cmd("", "/etc/resolv.conf /dev file1 test file2");
	cmd("", "/etc");
	cmd("", "/dev");
}

void	test1(void)
{
	printf("\033[035m****************** test1 ******************\033[0m\n");
	cmd("l", "test");
	cmd("l", "test test");
	cmd("l", "test test file1 file2");
	cmd("l", "file1 file2");
	cmd("l", "file1");
	cmd("l", "");
	cmd("l", "/etc");
	cmd("l", "/etc/");
	cmd("l", "/etc/resolv.conf");
	cmd("l", "/dev");
	cmd("l", "/etc/resolv.conf /dev file1 test file2");
}

int		main(void)
{
	system("make -C ../");
	test0();
	//test1();
	return (0);
}