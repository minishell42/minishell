#include "test.h"

char	**get_path_arr(t_list *env)
{
	t_list			*paths;
	char			*value;
	char			**path_arr;

	if (!(paths = find_env_target_list(env, "PATH")))
		return (NULL);
	value = ft_strchr(paths->content, '=');
	if (!value || !(value + 1))
		return (NULL);
	value++;
	if (!(path_arr = ft_split(value, ':')))
		return (NULL);
	return (path_arr);
}

char	*get_file(char *path, DIR *dir_ptr, char *file_name)
{
	struct dirent	*file;
	struct stat		file_stat;
	char			*full_file_name;
	int				fd;

	while ((file = readdir(dir_ptr)))
	{
		if (are_equal(file_name, file->d_name))
		{
			full_file_name = ft_strjoin(path, file->d_name);
			if ((fd = open(full_file_name, O_RDONLY)) == -1)
				return (NULL);
			if(fstat(fd, &file_stat) == -1)
				return (NULL);
			if (file_stat.st_mode & __S_IFREG)
			{
				close(fd);
				return (full_file_name);
			}
			free(full_file_name);
			close(fd);
		}
	}
	return (NULL);
}


void free_dir_and_path(DIR *dir, char *path)
{
	free(path);
	closedir(dir);
}
	// 환경변수중에 PATH를 찾는다.
	// PATH를 구분자로 쪼갠다 (:)
	// 쪼갠 path의 디렉터리에 파일네임이 존재하는지 확인한다.
	// readdir, stat
	// 존재한다면 path + filename을 리턴.
char	*search_file(char *file_name, t_list *env)
{
	char			**path_arr;
	DIR				*dir_ptr;
	char			*path;
	int				i;
	char			*file_path;

	path_arr = get_path_arr(env);
	i = 0;
	while (path_arr[i])
	{
		if(!(dir_ptr = opendir(path_arr[i])))
			return (NULL);
		path = ft_strjoin(path_arr[i], "/");
		if((file_path = get_file(path, dir_ptr, file_name)))
		{
			free_str_array(path_arr);
			free_dir_and_path(dir_ptr, path);
			return (file_path);
		}
		free_dir_and_path(dir_ptr, path);
		i++;
	}
	free_str_array(path_arr);
	return (NULL);
}

int main(int argc, char **argv, char *envp[])
{
	t_list *env;

	if (argc != 1)
		return (0);
	argv[1] = 0;
	env = get_env_llist(envp);
	// test_get_command_line(env);
	// test_cd(env);
	//  test_command_lines(env);
	// test_redirection(env);
	// test_validate_line();

	// test_export(env);

	char	*res;
	res = search_file("echo", env);
	printf("full path = %s\n", res);
	free(res);
	ft_lstclear(&env, free);

	return (0);
}

