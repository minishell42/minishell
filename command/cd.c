#include "command.h"
#include <sys/fcntl.h>

#define WRONG_DIRECTORY 5
#define TOO_MANY_REDIR_PARAM 6
#define NO_OLDPWD 7
#define NO_HOME 8
#define NOT_OPEN 9

//pipe flag가 있으면 실행 안되고 현 위치를 나타내야 한다. ; 콜론으로 구분된 것들만 동작
// ex> cd .. | cd.. ; cd .. == cd ..
// - 표시가 나오면 oldpwd에 저장된 위치로 옮겨진다 
// - 표시가 있고, oldpwd에 저장된 위치가 없으면 오류메시지와 오류를 발생시킨다.
// - 오류 메시지 : cd: OLDPWD 설정되지 않음
// chdir 함수의 파라미터로 상대경로도 넣을 수 있다.
// chdir 함수의 -1일때 환경변수 pwd값과 oldpwd값은 그대로 있어야 한다.
// redir flag가 있으면 해당 파일 이름의 빈 파일을 생성하고, cd도 정상적으로 동작한다.

bool	set_pipe_flag(t_cmd_line *cmd_line, bool *pipe_flag)
{
	if (cmd_line->pipe_flag)
	{
		*pipe_flag = true;
		return (false);
	}
	if (*pipe_flag && cmd_line->pipe_flag)
		return(false);
	else if (*pipe_flag && !cmd_line->pipe_flag)
	{
		*pipe_flag = false;
		return (false);
	}
	return (true);
}

t_list	*find_env_target_list(t_list *env, char *target)
{
	char	*key;
	char	*value;
	int		i;

	while (env)
	{
		i = 0;
		while ((((char *)env->content)[i] != '=') && ((char *)env->content)[i])
			i++;
		key = ft_substr(env->content, 0, i);
		value = ft_substr(env->content, i + 1, ft_strlen(env->content) - i);
		if (are_equal(target, key))
		{
			free(key);
			free(value);
			return (env);
		}
		free(key);
		free(value);
		env = env->next;
	}
	return (NULL);
}

char	*set_env_value(char *target, char *value)
{
	char	*target_tmp;
	char	*result;

	target_tmp = ft_strjoin(target, "=");
	result = ft_strjoin(target_tmp, value);
	free(target_tmp);
	return (result);
}

void	set_env_target(t_list *env, char *target, char *value)
{
	t_list	*target_env;
	void	*tmp;

	if (!(target_env = find_env_target_list(env, target)))
	{
		target_env = ft_calloc(sizeof(t_list), 1);
		target_env->content = set_env_value(target, value);
		target_env->next = NULL;
		ft_lstadd_back(&env, target_env);
	}
	else
	{
		tmp = target_env->content;
		target_env->content = set_env_value(target, value);
		// printf("value : %s\ntarget_env : %s\n", value, (char *)target_env->content);
		free(tmp);
	}
}

char	*make_err_msg(char *cmd, char *value, char *msg)
{
	char	*tmp;
	char	*str;
	char	*cmd_tmp;
	char	*val_tmp;
	char	*result;

	tmp = ft_strdup(msg);
	cmd_tmp = ft_strjoin(cmd, ": ");
	val_tmp = ft_strjoin(value, ": ");
	str = ft_strjoin(cmd_tmp, val_tmp);
	result = ft_strjoin(str, tmp);
	free(tmp);
	free(cmd_tmp);
	free(val_tmp);
	free(str);
	return (result);
}

char	*set_dir(t_cmd_line *cmd_line, t_list *env)
{
	char	*dir;
	char	*tmp;
	char	*home;
	int		index;

	if (cmd_line->param[0] == '-' && ft_strlen(cmd_line->param) == 1)
	{
		dir = get_env_value("OLDPWD", env);
		// 환경 변수값에  oldpwd가 있는지 확인 -> 없다면 오류 발생
		if (*dir == '\0')
		{
			parsing_err_value(NO_OLDPWD, "OLDPWD");
			return (false);
		}
	}
	else if (cmd_line->param[0] == '~' && are_equal(cmd_line->param, "--"))
	{
		home = get_env_value( "HOME", env);
		if (*home == '\0')
		{
			parsing_err_value(NO_HOME, "HOME");
			return (false);
		}
		// printf("home : %s\n", home);
		if (ft_strlen(cmd_line->param) != 1 && !are_equal(cmd_line->param, "--"))
		{
			tmp = ft_substr(cmd_line->param, 1, ft_strlen(cmd_line->param));
			dir = ft_strjoin(home, tmp);
			// printf("dir : %s\n", dir);
			free(tmp);
		}
		else
			dir = ft_strdup(home);
		free(home);
	}
	else
	{
		index = 0;
		dir = ft_strdup(cmd_line->param);
		check_character_in_line(dir, &index, ft_isspace);
		if (dir[index])
		{
			tmp = make_err_msg("bash", "cd", "인수가 너무 많습니다.");
			parsing_err_value(TOO_MANY_REDIR_PARAM, tmp);
			free(tmp);
			free(dir);
			return (NULL);
		}
	}
	return (dir);
}

bool	make_file_for_redir(t_cmd_line *cmd_line, char *pwd)
{
	char	*file;
	char	*tmp;
	int		fd;

	file = cmd_line->redir_param->content;
	if (cmd_line->redir_flag == OUT_OVERRIDE)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (cmd_line->redir_flag == REDIR_IN)
		fd = open(file, O_RDONLY);
	else if (cmd_line->redir_flag == OUT_ENDLINE)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		return (false);
	if (fd < 0)
	{
		tmp = make_err_msg("bash", file, "그런 파일이나 디렉터리가 없습니다\n");
		parsing_err_value(NOT_OPEN, tmp);
		free(tmp);
		return (false);
	}
	write(fd, NULL, 0);
	if (ft_lstsize(cmd_line->redir_param) != 1)
	{
		parsing_err_value(TOO_MANY_REDIR_PARAM, "cd : 인수가 너무 많습니다.\n");
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

bool	ft_cd(t_cmd_line *cmd_line, t_list *env, bool *pipe_flag)
{
	// pipe flag 가 있거나 전에 있었던 것 -> 종료
	char		*dir;
	char		*pwd;
	int			val;
	char		*tmp;

	// - 표시가 있는지 확인 -> 있으면 변환 없으면 그 다음 로직
	dir = set_dir(cmd_line, env);
	// 현재 directory -> oldPWD에 넣어야 한다.
	// 현재 directory 위치 찾기
	if (!(pwd = getcwd(NULL, 0)))
	{
		free(dir);
		return (false);
	}
	// redir_flag가 있다면 redir_param 첫번째 값에 대한 것만 파일이 생성 -> 그 뒤에는 모두 동작 하면 안된다.
	if (cmd_line->redir_flag)
	{
		printf("in\n");
		if (!make_file_for_redir(cmd_line, pwd))
		{
			free(pwd);
			free(dir);
			return (false);
		}
	}
	if (!set_pipe_flag(cmd_line, pipe_flag))
	{
		free(pwd);
		free(dir);
		return (false);
	}
	if (!dir)
	{
		free(pwd);
		return (false);
	}
	// oldpwd값이 있는지 확인한 후 없다면 새로 만들고 있다면 값을 변경해주기
	set_env_target(env, "OLDPWD", pwd);
	free(pwd);
	if (chdir(dir) < 0)
	{
		tmp = make_err_msg(cmd_line->command, dir, "그런 파일이나 드렉터리가 없습니다.\n");
		parsing_err_value(WRONG_DIRECTORY, tmp);
		free(tmp);
		free(dir);
		return (false);
	}
	if (!(pwd = getcwd(NULL, 0)))
	{
		free(dir);
		return (false);
	}
	set_env_target(env, "PWD", pwd);
	if (cmd_line->param[0] == '-' && ft_strlen(cmd_line->param) == 1)
	{
		write(1, dir, ft_strlen(dir));
		write(1, "\n", 1);
	}
	free(pwd);
	free(dir);
	return (true);	
}
