/**
* shell.c:shell program
* author:lee seo bin
* email:sltenic@naver.com
* version:1.0
* date:2022.12.06
**/



#include"mysh.h"
void main() {
	write(STDOUT_FILENO, "+------------------------------------------------------------------------------------+\n", 88);
	write(STDOUT_FILENO, "|MYSHELL                                                                             |\n", 88);
	write(STDOUT_FILENO, "|------------------------------------------------------------------------------------|\n", 88);
	write(STDOUT_FILENO, "|QUIT : quit                                                                         |\n", 88);
	write(STDOUT_FILENO, "+------------------------------------------------------------------------------------+\n", 88);

	while (1) {
		//write�� �����Ⱚ ���� �ʱ�ȭ
		char CommandLine[MAX] = { 0 };
		char PWD[MAX] = { 0 };
		char** command;
		int read_size;
		int errno;
		/*char *getcwd(char *buf, int maxlen); => get pwd "unistd.h*/
		getcwd(PWD, MAX);
		/////////////////////////////////////////////////////////////////
		//ȭ�鿡 ���, write�� printf���� �����Ƿ� write�� ��f��..
		write(STDOUT_FILENO, "@myshell:~", 20);
		write(STDOUT_FILENO, PWD, MAX);
		write(STDOUT_FILENO, "$ ", 3);
		/////////////////////////////////////////////////////////////////
		//�б�
			/*�Է¹��� Ŀ�ǵ� command�� ����*/
		read_size = read(STDIN_FILENO, CommandLine, MAX);
		//input enter
		if (read_size == 1) {
			continue;
		}
		////////////////////////////////////////////////////////////////
		//��ɾ� �����ϰ� ����
		command = get_tokens(CommandLine);
		if (!strcmp(command[0], "quit")) {
			printf("+------------------------------------------------------------------------------------+\n");
			printf("|BASH                                                                                |\n");
			printf("+------------------------------------------------------------------------------------+\n");
			exit(1);
		}
		else {
			execute_com(command);
		}

	}
}