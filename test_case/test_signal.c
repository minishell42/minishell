#include "test.h"

void test_signal(char **envp)
{
	int p[2];
	int pid;
	int pid2;
	int status;
	const char *path = 	"/bin/echo";
	char **values = ft_calloc(sizeof(char *), 5);
	char buf[255];

	ft_bzero(buf, 255); // grep 1 < 456
	values[0] = "echo";
	values[1] = "1";
	values[2] = "2";
	values[3] = "456";
	// values[1] = "\0";
	// values[2] = "";

	pipe(p);
	pid = fork();  // p c1
	if (pid == 0)
	{
		printf("start child\n");
		
		pid2 = fork(); // c1 c2
		if (pid2 > 0)
		{
			waitpid(pid2, &status, 0); // c1 wait -> pipe 1 : 123456
			printf("status : %d\n", status);
			printf("end child22222\n");
			// close(p[1]);
			read(p[0], buf, 255); // buf -> 123456
			write(1, buf, 255); // 1 -> 123456
			// printf("%s\n", buf);
			// dup2(1, sout);
			printf("recover pipe\n");
			exit(1);
		}
		else if (pid2 == 0) // c2 -> 123456
		{
			printf("start child2222\n");
			dup2(p[1], 1);
			// write(1, "", 1);
			// exit(5);
			// printf("write pipe = %d\n", p[1]);
			if (execve(path, values, envp) == -1)
				perror("excve\n");
		}

	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0); // p wait ->  1 : 123456
		printf("end child\n");
	}
	free(values);
}