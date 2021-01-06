#include "signal_handler.h"

void		default_signal(int signal_no)
{
	if (signal_no == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		prompt();
	}
}

void		child_signal(int signal_no)
{
	if (signal_no == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		exit(INVALID_ARGUMENT_TO_EXIT + signal_no);
	}
	else if (signal_no == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		exit(INVALID_ARGUMENT_TO_EXIT + signal_no);
	}
}

void		init_signal(void)
{
	signal(SIGINT, default_signal);
	signal(SIGQUIT, SIG_IGN);
}

void		signal_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void		init_child_signal(void)
{
	signal(SIGINT, child_signal);
	signal(SIGQUIT, child_signal);
}
