#include "command.h"

char	**get_path_arr(void)
{
	t_list			*paths;
	char			*value;
	char			**path_arr;

	if (!(paths = find_env_target_list("PATH")))
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
			if (fstat(fd, &file_stat) == -1)
				return (NULL);
			if (file_stat.st_mode & __S_IFREG)
			{
				close(fd);
				return (full_file_name);
			}
			free(full_file_name);
			close(fd);
			return (NULL);
		}
	}
	return (NULL);
}

void	free_dir_and_path(DIR *dir, char *path)
{
	free(path);
	closedir(dir);
}

char	*search_path(char *file_name)
{
	char			**path_arr;
	DIR				*dir_ptr;
	char			*path;
	int				i;
	char			*file_path;

	if (!(path_arr = get_path_arr()))
		return (NULL);
	i = 0;
	while (path_arr[i])
	{
		if (!(dir_ptr = opendir(path_arr[i])))
			return (NULL);
		path = ft_strjoin(path_arr[i], "/");
		if ((file_path = get_file(path, dir_ptr, file_name)))
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

char	*search_file(t_cmd_line *cmd_line, char *file_name)
{
	DIR				*dir_ptr;
	struct stat		buf;
	char			*absolute_path;
	char			*file_path;

	absolute_path = change_to_absolute_path(file_name);
	if (stat(absolute_path, &buf) < 0)
	{
		file_path = search_path(file_name);
		if (file_path)
		{
			free(absolute_path);
			return (file_path);
		}
		free(absolute_path);
		return (NULL);
	}
	if (buf.st_mode & __S_IFDIR)
	{
		free(absolute_path);
		make_err_msg(IS_NOT_EXECUTABLE, cmd_line->command, 0, "is directory\n");
		built_in_error();
		exit(g_exit_code);
	}
	free(cmd_line->command);
	cmd_line->command = ft_strdup(absolute_path);
	return (absolute_path);
}
