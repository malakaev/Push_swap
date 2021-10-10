#include "push_swap.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)

{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*h;
	char	*n;

	h = (char *)haystack;
	n = (char *)needle;
	if (*n == 0)
		return (h);
	k = 0;
	while ((h[k] != 0) && (k < len))
	{
		i = k;
		j = 0;
		while ((i < len) && (h[i++] == n[j++]))
		{
			if (n[j] == 0)
				return (h + k);
		}
		k++;
	}
	return (NULL);
}
