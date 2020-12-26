#include "signal_handler.h"

void		prompt(void)
{
	char	*str;

	str = I_CYAN"minishell "B_YELLOW"$ "WHITE;
	write(1, str, ft_strlen(str));
}

void		handler_signal(int signal_no)
{
	if (signal_no == SIGINT)
		ft_putstr_fd("\b\b\b\b\n", 1);
	else if (signal_no == SIGQUIT)
		ft_putstr_fd("\b\b\b\b\n", 1);
}

void		process_exit(bool option)
{
	char	*str;

	if (option)
		ft_putstr_fd("exit\n", 1);
	str = B_YELLOW"minishell exit\n";
	write(1, str, ft_strlen(str));
	exit(0);
}

void		child_exit(int signo)
{
	char	*str;

	str = B_YELLOW"실행중인 프로그램을 중지합니다.\n";
	ft_putstr_fd("\b\b\b\b\n", 1);
	write(1, str, ft_strlen(str));
	exit(signo);
}

void		set_signal(void)
{
	pid_t	pid;
	int		status;
	
	pid = fork();
	if (pid > 0)
	{
		signal(SIGINT, handler_signal);
		signal(SIGQUIT, handler_signal);
	}
	while (waitpid(pid, &status, 0) > 0)
	{
		if (!status)
			exit(0);
		pid = fork();
	}
	if (pid == 0)
	{
		signal(SIGINT, exit);
		signal(SIGQUIT, exit);
	}
}