#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# include "pipe.h"
# include <signal.h>

# define I_CYAN		"\033[3;36m"
# define B_YELLOW	"\033[1;33m"
# define WHITE		"\033[0;39m"

/*
** set_prompt.c
*/
void		prompt(void);
void		process_exit(bool option);
/*
** signal_handler.c
*/
void		init_child_signal(void);
void		init_signal(void);
void		signal_ignore(void);

#endif
