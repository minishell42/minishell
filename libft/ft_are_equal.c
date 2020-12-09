#include "libft.h"

bool	are_equal(char *s1, char *s2)
{
	int			s1_len;
	int			s2_len;

	if (!s1 && !s2)
		return (true);
	if (!s1 || !s2)
		return (false);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len == s2_len && ft_strncmp(s1, s2, ft_strlen(s1)) == 0)
		return (true);
	return (false);
}
