#include "signal_handler.h"
#include <errno.h>

void		prompt(void)
{
	char	*str;

	str = I_CYAN"minishell "B_YELLOW"$ "WHITE;
	write(1, str, ft_strlen(str));
}

void		default_signal(int signal_no)
{
	if (signal_no == SIGINT)
	{
		ft_putstr_fd("\b\b\b\b\n", 1);
		prompt();
	}
	else if (signal_no == SIGQUIT)
	{
		ft_putstr_fd("\b\b\b\b\n", 1);
		prompt();
	}
}

void		child_signal(int signal_no)
{
	if (signal_no == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		exit(signal_no);
	}
	else if (signal_no == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		exit(signal_no);
	}
}

void		init_signal(void)
{
	signal(SIGINT, default_signal);
	signal(SIGQUIT, default_signal);
}

void		init_child_signal(void)
{
	signal(SIGINT, child_signal);
	signal(SIGQUIT, child_signal);
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
