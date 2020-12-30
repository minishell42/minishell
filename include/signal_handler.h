#ifndef SIGNAL_HANDLER_H
# define SIGANL_HANDLER_H

# include "parsing.h"
# include <signal.h>

# define I_CYAN		"\033[3;36m"
# define B_YELLOW	"\033[1;33m"
# define WHITE		"\033[0;39m"

void		prompt(void);
void		process_exit(bool option);
void		set_signal(void);

void		init_child_signal(void);
void		init_signal(void);

#endif
