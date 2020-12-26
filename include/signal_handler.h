#ifndef SIGNAL_HANDLER_H
# define SIGANL_HANDLER_H

# include "parsing.h"
# include <signal.h>

# define I_CYAN		"\033[3;36m"
# define B_YELLOW	"\033[1;33m"
# define WHITE		"\033[0;39m"

void		prompt(void);
void		handler_signal(int signal_no);
void		process_exit(bool option);
void		set_signal(void);
void		child_exit(int signo);


#endif