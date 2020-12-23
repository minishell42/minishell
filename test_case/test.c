#include "test.h"

void	divide_process(int *p_fd, bool flag, int i)
{
	int pid2;
	int status;
	char buff[BUFFER_SIZE];

	pid2 = fork();
	ft_bzero(buff, BUFFER_SIZE);
	if (pid2 > 0)
	{
		printf("2nd\tprocess ? %d\tpid ? %d\n",getpid(), pid2);
		waitpid(pid2, &status, 0);
		if (i == 2)
		{
			read(p_fd[0], buff, BUFFER_SIZE);
			printf("parents pipe buffer ? %s\n", buff);
		}
	}
	else if (pid2 == 0)
	{
		printf("3th\tprocess ? %d\tpid ? %d\n",getpid(), pid2);
		dup2(p_fd[1], 1);
		printf("sample\tindex ? %d\n", i);
		if (flag)
		{
			dup2(p_fd[0], 0);
			printf("ex\n");
			// read(0, buff, BUFFER_SIZE);
			// printf("child pipe buffer ? %s\tindex ? %d\n", buff, i);
		}
		exit(0);
	}
}

int main(int argc, char **argv, char *envp[])
{
	if (argc != 1)
		return (0);
	argv[1] = 0;

	int p_fd[2];
	int pid;
	int status;
	int	i;
	bool flag;

	pipe(p_fd);
	pid = fork();
	i = 0;
	flag = false;
	if (pid == 0)
	{
		while (i < 3)
		{
			divide_process(p_fd, flag, i);
			close(p_fd[1]);
			flag = true;
			i++;
		}
	}
	else if (pid > 0)
	{
		printf("1st\tprocess ? %d\tpid ? %d\n",getpid(), pid);
		waitpid(pid, &status, 0);
	}
	return (0);
}

