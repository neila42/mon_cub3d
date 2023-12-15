#include "parse.h"

int	reverse_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i1;
	size_t	i2;

	i1 = ft_strlen(s1) - 1;
	i2 = ft_strlen(s2) - 1;

    while (i1 > 0 && (s1[i1] == ' ' || s1[i1] == '\n' || s1[i1] == '\t'))
		i1--;
	if (n == 0)
		return (0);
	while (i1 >= 0 && i2 >= 0 && n)
	{
		if (s1[i1] != s2[i2])
			break ;
		i1--;
		i2--;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char) s1[i1] - (unsigned char) s2[i2]);
}

void	fail(char *str)
{
	ft_putstr_fd(str, 1);
	exit(1);
}

