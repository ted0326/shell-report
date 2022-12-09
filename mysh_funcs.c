/**
* shell.c:shell program
* author:lee seo bin
* email:sltenic@naver.com
* version:1.0
* date:2022.12.06
**/

char** get_tokens(char* CommandLine) {
	char** tokens;//��ū���� ������ �迭
	char* token;
	int COUNT = 0;
	//\n ��� \0����
	CommandLine[strlen(CommandLine) - 1] = '\0';
	//��ū ������ �迭 ũ��
	tokens = malloc((sizeof(char*)) * MAX);
	//" "�� �����ڷ� �ڸ�
	token = strtok(CommandLine, " ");
	while (token != NULL) {
		//\0�����ؾ��ϹǷ� +1
		tokens[COUNT] = malloc(strlen(token) + 1);
		//�����Ҵ� �� ���뺹�� 
		strncpy(tokens[COUNT], token, strlen(token) + 1);
		token = strtok(NULL, " ");
		COUNT++;
	}
	//��ū�� �Է� ������ null
	tokens[COUNT] = NULL;
	return tokens;
}
//////////////////////////////////////////////////////////////////////////////////////
/////����� ������ ���� 
void execute_com(char** commands) {
	int fork_process;
	int status;
	int i = 0;
	char* dir;
	///////////////////////////////////////////////
	/////////shell builtin command  
	if (!strcmp(commands[0], "cd")) {
		if (commands[1] == NULL) {
			printf("USEAGE : cd directory\n");
		}
		chdir(commands[1]);
	}
	else if (!strcmp(commands[0], "pwd")) {
		printf("Present Working Directory: %s\n", getcwd(dir, MAX));
	}
	///////////////////////////////////////////////
	///////////����Ǿ��ִ� ��ɾ�(/bin�ȿ� ����)
	else {
		if ((fork_process = fork()) == 0) {
			//execv'P' �� PATH�� ��ϵ� ��� ���丮�� �ִ� ���α׷��� ����
				//��ɾ� ������ �о ���� ��Ȳ�� ���� ����
			while (commands[i]) {
				if (!strcmp(commands[i], ">")) {
					redirection_com(commands, i);
				}
				else if (!strcmp(commands[i], "&")) {
					background_com(commands, i);
				}
				i++;
			}
			//�߸��� commands[0]�� ������ -1 ��ȯ��
			if (execvp(commands[0], commands) == -1) {
				printf("%s : command not found\n", commands[0]);
				exit(1);
			}
		}
		else if (fork_process < 0) {
			printf("fork error\n");
			exit(1);
		}
		else
			wait(&status);
	}
}

//////////////////////////////////////////////////////////////////////
///////////��ɾ �����̷����� ������� ����
//ex) cat a.txt > b.txt
void redirection_com(char** commands, int i) {
	char* to = commands[i + 1];
	char* from = commands[i - 1];
	int to_fd;

	to_fd = open(to, O_WRONLY | O_CREAT, 0641);
	if (to_fd < 0) {
		printf("open error\n");
		exit(1);
	}
	//STDOUT_FILENO�� to_fd�� ����Ű����
	dup2(to_fd, STDOUT_FILENO);
	//>�ڸ��� NULL��
	commands[i] = NULL;
	//��ɾ� ����
	if (execvp(commands[0], commands) == -1) {
		printf("No such command : %s\n", commands[0]);
		exit(1);
	}
}
/////////////////////////////////////////////////////////////////////////
////////��ɾ &�� ������� background processing ����
void background_com(char** commands, int i) {
	commands[i] = NULL;
	int fork_process;
	if ((fork_process = fork()) == 0) {
		if (execvp(commands[0], commands) == -1) {
			printf("No such command : %s\n", commands[0]);
			exit(1);
		}
	}
	else if (fork_process < 0) {
		printf("fork error\n");
		exit(1);
	}
	//��ٸ��� ����
	else {
		exit(1);
	}
};