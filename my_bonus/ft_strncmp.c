#include "push_swap.h"

int	ft_strncmp(const char *str1, const char *str2, size_t len)

{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	while ((i < len) && (s1[i] == s2[i]))
		if (s1[i++] == 0)
			return (0);
	if (i == len)
		return (0);
	return (s1[i] - s2[i]);
}
