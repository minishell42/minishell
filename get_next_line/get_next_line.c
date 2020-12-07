/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangpark <sangpark@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 19:24:44 by sangpark          #+#    #+#             */
/*   Updated: 2020/05/09 19:26:56 by sangpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int	fill(char *buffer, int fd, char **remainder)
{
	int		read_res;
	char	*new_line;
	char	*temp;

	new_line = 0;
	while (!new_line && !ft_strchr(*remainder, '\n'))
	{
		if ((read_res = read(fd, buffer, BUFFER_SIZE)) == ERROR_HAPPEND)
			return (ERROR_HAPPEND);
		buffer[read_res] = '\0';
		temp = *remainder;
		*remainder = ft_strjoin(*remainder, buffer);
		free(temp);
		new_line = ft_strchr(buffer, '\n');
		if (!read_res)
			return (EOF_REACHED);
	}
	return (READ_LINE);
}

int	save_remainder(char **remainder, char *new_line)
{
	char	*temp;
	int		remainder_len;

	temp = *remainder;
	remainder_len = ft_strlen(new_line);
	if (!remainder_len)
	{
		free(temp);
		*remainder = 0;
		return (0);
	}
	if (!(*remainder = malloc(sizeof(char) * (remainder_len + 1))))
		return (ERROR_HAPPEND);
	ft_strlcpy(*remainder, new_line, remainder_len + 1);
	free(temp);
	return (0);
}

int	put_line(char **remainder, char **line)
{
	char	*new_line;
	int		line_len;
	char	*ret;
	int		remainder_len;

	remainder_len = ft_strlen(*remainder);
	if (!*remainder)
		return (0);
	if (!(new_line = ft_strchr(*remainder, '\n')))
		new_line = ft_strchr(*remainder, '\0');
	*new_line = '\0';
	line_len = new_line - *remainder;
	if (!(ret = malloc(sizeof(char) * (line_len + 1))))
		return (ERROR_HAPPEND);
	ft_strlcpy(ret, *remainder, line_len + 1);
	if (line_len < remainder_len)
		new_line++;
	if (save_remainder(remainder, new_line) == ERROR_HAPPEND)
	{
		free(ret);
		return (ERROR_HAPPEND);
	}
	*line = ret;
	return (0);
}

int	get_next_line(int fd, char **line)
{
	char		*buffer;
	static char	*remainder;
	int			ret;

	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (ERROR_HAPPEND);
	if (!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (ERROR_HAPPEND);
	if ((ret = fill(buffer, fd, &remainder)) == ERROR_HAPPEND)
		return (ERROR_HAPPEND);
	free(buffer);
	if (put_line(&remainder, line) == ERROR_HAPPEND)
		return (ERROR_HAPPEND);
	return (ret);
}
