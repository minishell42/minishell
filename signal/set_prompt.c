#include "signal_handler.h"

void		prompt(void)
{
	char	*str;

	str = I_CYAN"minishell "B_YELLOW"$ "WHITE;
	write(1, str, ft_strlen(str));
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
