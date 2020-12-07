#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#include "get_next_line.h"
#include "libft.h"

# define ECHO 1

typedef struct      s_command_line
{
    char			*command;
    char			*option;
    char			*param;
	int				command_num;
}					t_cmd_line;

void			message_and_exit(char *message, bool built_in_error);
