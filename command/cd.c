#include "command.h"

// //pipe flag가 있으면 실행 안되고 현 위치를 나타내야 한다. ; 콜론으로 구분된 것들만 동작
// // ex> cd .. | cd.. ; cd .. == cd ..
// // - 표시가 나오면 oldpwd에 저장된 위치로 옮겨진다 
// // - 표시가 있고, oldpwd에 저장된 위치가 없으면 오류메시지와 오류를 발생시킨다.
// // - 오류 메시지 : cd: OLDPWD 설정되지 않음
// // chdir 함수의 파라미터로 상대경로도 넣을 수 있다.
// // chdir 함수의 -1일때 환경변수 pwd값과 oldpwd값은 그대로 있어야 한다.
// // redir flag가 있으면 해당 파일 이름의 빈 파일을 생성하고, cd도 정상적으로 동작한다.

t_list	*find_env_target_list(char *target)
{
	char	*key;
	char	*value;
	int		i;
	t_list	*env;

	env = g_env;
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

void	set_env_target(char *target, char *value)
{
	t_list	*target_env;
	char	*target_tmp;
	void	*tmp;

	if (!(target_env = find_env_target_list(target)))
	{
		target_env = ft_calloc(sizeof(t_list), 1);
		target_tmp = ft_strjoin(target, "=");
		target_env->content = ft_strjoin(target_tmp, value);
		free(target_tmp);
		target_env->next = NULL;
		ft_lstadd_back(&g_env, target_env);
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




static char	*set_home_dir(char *param)
{
	char	*home;
	char	*dir;
	char	*tmp;

	home = get_env_value("HOME");
	if (*home == '\0')
	{
		make_err_msg(NO_HOME, "bash", "cd", "HOME not set\n");
		free(home);
		return (NULL);
	}
	if (ft_strlen(param) != 1 && !are_equal(param, "--"))
	{
		tmp = ft_substr(param, 1, ft_strlen(param));
		dir = ft_strjoin(home, tmp);
		free(tmp);
	}
	else
		dir = ft_strdup(home);
	free(home);
	return (dir);
}

static char	*set_dir(t_list *param_list)
{
	char	*dir;
	char	*tmp;
	char	*home;
	int		index;
	char	*param;

	if (ft_lstsize(param_list) > 1)
	{
		make_err_msg(TOO_MANY_REDIR_PARAM, 
					"bash", "cd", "too many arguments\n");
		return (NULL);
	}
	param = param_list->content;
	if (param[0] == '-' && ft_strlen(param) == 1)
	{
		dir = get_env_value("OLDPWD");
		if (*dir == '\0')
		{
			make_err_msg(NO_OLDPWD, "bash", "cd", "OLDPWD not set\n");
			free(dir);
			return (NULL);
		}
	}
	else if (param[0] == '~' || are_equal(param, "--"))
		dir = set_home_dir(param);
	else
		dir = ft_strdup(param);
	return (dir);
}

static bool	set_chdir(t_list *param_list, char *dir)
{
	char	*tmp;
	char	*param;

	param = param_list->content;
	if (chdir(dir) < 0)
	{
		make_err_msg(NO_FILE_OR_DIRECTORY, 
					"bash", "cd", "No such file or directory\n");
		free(dir);
		return (false);
	}
	if (param[0] == '-' && ft_strlen(param) == 1)
	{
		write(1, dir, ft_strlen(dir));
		write(1, "\n", 1);
	}
	return (true);
}

static bool	set_pwd_to_env(char *env_value, char *dir)
{
	char	*pwd;

	if (!(pwd = getcwd(NULL, 0)))
	{
		free(dir);
		return (false);
	}
	set_env_target(env_value, pwd);
	free(pwd);
	return (true);
}

bool	cd(t_cmd_line *cmd_line)
{
	char		*dir;
	char		*old_pwd;
	t_list		*param_list;

	param_list = cmd_line->param;
	if (!(dir = set_dir(param_list)))
		return (false);
	if (!(old_pwd = getcwd(NULL, 0)))
	{
		free(dir);
		return (false);
	}
	if (!set_chdir(param_list, dir))
	{
		free(old_pwd);
		return (false);
	}
	set_env_target("OLDPWD", old_pwd);
	free(old_pwd);
	if (!set_pwd_to_env("PWD",dir))
		return (false);
	free(dir);
	return (true);
}
