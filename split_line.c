char		**split_line(char *line, char c)
{
    char        **res;
    int         i;

	if (!line || !(*line))
	{
		res = (char **)ft_calloc(1, sizeof(char *));
		if (!res)
			return (0);
		return (res);
	}
    i = 0;
    while (line[i] == ' ')
}
