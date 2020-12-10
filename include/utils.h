#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/wait.h>

# include "get_next_line.h"
# include "libft.h"

void		remove_quotation(char *value);
void		message_and_exit(char *message, bool built_in_error);

#endif