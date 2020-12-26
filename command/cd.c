#include "command.h"

// //pipe flag가 있으면 실행 안되고 현 위치를 나타내야 한다. ; 콜론으로 구분된 것들만 동작
// // ex> cd .. | cd.. ; cd .. == cd ..
// // - 표시가 나오면 oldpwd에 저장된 위치로 옮겨진다 
// // - 표시가 있고, oldpwd에 저장된 위치가 없으면 오류메시지와 오류를 발생시킨다.
// // - 오류 메시지 : cd: OLDPWD 설정되지 않음
// // chdir 함수의 파라미터로 상대경로도 넣을 수 있다.
// // chdir 함수의 -1일때 환경변수 pwd값과 oldpwd값은 그대로 있어야 한다.
// // redir flag가 있으면 해당 파일 이름의 빈 파일을 생성하고, cd도 정상적으로 동작한다.

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

void	set_env_target(t_list *env, char *target, char *value)
{
	t_list	*target_env;
	char	*target_tmp;
	void	*tmp;

	if (!(target_env = find_env_target_list(env, target)))
	{
		target_env = ft_calloc(sizeof(t_list), 1);
		target_tmp = ft_strjoin(target, "=");
		target_env->content = ft_strjoin(target_tmp, value);
		free(target_tmp);
		target_env->next = NULL;
		ft_lstadd_back(&env, target_env);
	}
	else
	{
		tmp = target_env->content;
		target_tmp = ft_strjoin(target, "=");
		target_env->content = ft_strjoin(target_tmp, value);
		free(target_tmp);
		free(tmp);
	}
}

static char	*set_home_dir(t_cmd_line *cmd_line, t_list *env)
{
	char	*home;
	char	*dir;
	char	*tmp;

	home = get_env_value("HOME", env);
	if (*home == '\0')
	{
		make_err_msg(NO_HOME, "bash", "cd", "HOME not set\n");
		free(home);
		return (NULL);
	}
	if (ft_strlen(cmd_line->param) != 1 && !are_equal(cmd_line->param, "--"))
	{
		tmp = ft_substr(cmd_line->param, 1, ft_strlen(cmd_line->param));
		dir = ft_strjoin(home, tmp);
		free(tmp);
	}
	else
		dir = ft_strdup(home);
	free(home);
	return (dir);
}

static char	*set_dir_param(t_cmd_line *cmd_line)
{
	int		index;
	char	*dir;

	index = 0;
	dir = ft_strdup(cmd_line->param);
	check_character_in_line(dir, &index, ft_isspace);
	if (dir[index])
	{
		make_err_msg(TOO_MANY_REDIR_PARAM, "bash", "cd", "too many arguments\n");
		free(dir);
		return (NULL);
	}
	return (dir);
}

static char	*set_dir(t_cmd_line *cmd_line, t_list *env)
{
	char	*dir;
	char	*tmp;
	char	*home;
	int		index;

	if (cmd_line->param[0] == '-' && ft_strlen(cmd_line->param) == 1)
	{
		dir = get_env_value("OLDPWD", env);
		if (*dir == '\0')
		{
			make_err_msg(NO_OLDPWD, "bash", "cd", "OLDPWD not set\n");
			free(dir);
			return (NULL);
		}
	}
	else if (cmd_line->param[0] == '~' || are_equal(cmd_line->param, "--"))
		dir = set_home_dir(cmd_line, env);
	else
		dir = set_dir_param(cmd_line);
	return (dir);
}

static bool	set_chdir(t_cmd_line *cmd_line, char *dir)
{
	char	*tmp;

	if (chdir(dir) < 0)
	{
		make_err_msg(NO_FILE_OR_DIRECTORY, "bash", "cd", "No such file or directory\n");
		free(dir);
		return (false);
	}
	if (cmd_line->param[0] == '-' && ft_strlen(cmd_line->param) == 1)
	{
		write(1, dir, ft_strlen(dir));
		write(1, "\n", 1);
	}
	return (true);
}

bool	cd(t_cmd_line *cmd_line, t_list *env)
{
	char		*dir;
	char		*pwd;
	char		*p_tmp;

	if (!(dir = set_dir(cmd_line, env)))
		return (false);
	if (!(pwd = getcwd(NULL, 0)))
	{
		free(dir);
		return (false);
	}
	set_env_target(env, "OLDPWD", pwd);
	free(pwd);
	if (!set_chdir(cmd_line, dir))
		return (false);
	if (!(pwd = getcwd(NULL, 0)))
	{
		free(dir);
		return (false);
	}
	set_env_target(env, "PWD", pwd);
	free(pwd);
	free(dir);
	return (true);	
}
