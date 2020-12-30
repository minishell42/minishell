#include "command.h"

char	*ft_exit(t_cmd_line *cmd_line)
{
	free_cmd_struct(cmd_line);
	free_env_list(&g_env);
	process_exit(0);
}