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
	char str1[1024];
	char str2[1024];
	char str_cmd[1024];

	if (ft_strlen(cmd) > 0)
		sprintf(str_cmd, "-%s %s", cmd, param);
	else
		sprintf(str_cmd, "%s%s", cmd, param);

	sprintf(str1, "ls %s 1> ../output1 2> ../outputerr1", str_cmd);
	sprintf(str2, "../ft_ls %s 1> ../output2 2> ../outputerr2", str_cmd);

	//printf("%s\n", str1);
	//printf("%s\n", str2);

	system(str1);
	system(str2);
	system("cat ../outputerr1 >> ../output1");
	system("cat ../outputerr2 >> ../output2");
	system("diff ../output1 ../output2 > ../diff");
	if (getdiff() > 0) {
		printf("\033[031m[ Error    ]\033[0m ft_ls %s\n", str_cmd);
		//system("cat ../diff");
		exit(1);
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
	cmd("", "file1 testnoexist filenoexist file2 test");
}

void	test1(void)
{
	printf("\033[035m****************** test1 ******************\033[0m\n");
	cmd("a", "test");
	cmd("a", "test test");
	cmd("a", "file3 test test file1 file2");
	cmd("a", "/etc/resolv.conf /dev file1 test file2");
	cmd("a", "/etc");
	cmd("a", "file1 testnoexist filenoexist file2 test");
	cmd("a", "/dev");
}

void	test2(void)
{
	printf("\033[035m****************** test2 ******************\033[0m\n");
	cmd("l", "test");
	cmd("l", "test test");
	cmd("l", "file1 testnoexist filenoexist file2 test");
	cmd("l", "test test file1 file2");
	cmd("l", "file1 file2");
	cmd("l", "file1");
	cmd("l", "");
	//cmd("l", "/etc");
	cmd("l", "/etc/");
	cmd("l", "/etc/resolv.conf");
	cmd("l", "/dev");
	cmd("l", "link");
	cmd("l", "/etc/resolv.conf /dev file1 test file2");
}

void	test3(void)
{
	printf("\033[035m****************** test3 ******************\033[0m\n");
	cmd("t", "test");
	cmd("t", "file1 testnoexist filenoexist file2 test");
	cmd("t", "test test");
	cmd("t", "file3 test test file1 file2");
	cmd("t", "fileFUTUR /etc/resolv.conf file1 test file2 fileOLD");
	cmd("t", "../ls_test_cmd/link/a file1 file2");
	cmd("t", "/etc");
	cmd("t", "/dev");
}

void	test4(void)
{
	printf("\033[035m****************** test4 ******************\033[0m\n");
	cmd("at", "test");
	cmd("at", "test link");
	cmd("at", "file3 test test file1 file2");
	cmd("at", "fileFUTUR /etc/resolv.conf file1 test file2 fileOLD");
	cmd("at", "../ls_test_cmd/link/a file1 file2");
	cmd("at", "/etc");
	cmd("at", "/dev");
}

void	test5(void)
{
	printf("\033[035m****************** test5 ******************\033[0m\n");
	cmd("a", "file2 test/noexist fileanoexist file1 test link error_dir");
	cmd("l", "file2 test/noexist fileanoexist error_dir file1 test link");
	cmd("t", "file2 test/noexist error_dir fileanoexist file1 test link");
	cmd("", "error_dir file2 test/noexist fileanoexist file1 test link");
}

void	test6(void)
{
	printf("\033[035m****************** test6 ******************\033[0m\n");
	cmd("alrt", "file2 test/noexist fileanoexist file1 test link error_dir");
	//cmd("lrta", "fileFUTUR /etc/resolv.conf file1 test file2 fileOLD");
	//cmd("rtal", "../ls_test_cmd/link/a file1 file2");
	//cmd("talr", "test link");
	//cmd("alrt", "/etc");
	//cmd("lrta", "/etc/");
	//cmd("tlar", "/etc/resolv.conf");
	//cmd("rtrl", "/dev");
	//cmd("rtla", "/test/.lol");
}

void	test7(void)
{
	printf("\033[035m****************** test7 ******************\033[0m\n");
	cmd("R", "test");
	cmd("R", "test test");
	cmd("Rt", "/etc");
	cmd("R", "/etc/");
	cmd("Rl", "file1 test test file2");
	cmd("lRta", "file2 test/noexist fileanoexist file1 test link error_dir");
	cmd("lRat", "file2 test/noexist fileanoexist file1 test link error_dir");
	cmd("lRat", "file2 test/noexist fileanoexist error_dir file1 test link");
}

int		main(void)
{
	system("make -C ../");
	test0();
	test1();
	test2();
	test3();
	test4();
	test5();
	//test6();
	test7();
	return (0);
}