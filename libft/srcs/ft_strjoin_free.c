#include "libft.h"
#include <stdio.h>

char	*ft_strjoin_free(char *s1, char *s2, int f)
{
	char	*new;

	if (!s1 || !s2)
	{
		if (!s1 && !s2)
			return (NULL);
		else if (!s1)
			new = ft_strdup(s2);
		else
			new = ft_strdup(s1);
	}
	else
	{
		new = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
		new = ft_strcpy(new, s1);
		new = ft_strcat(new, s2);
	}
	if (s1 && (f == 1 || f == 3))
		free(s1);
	if (s2 && (f == 2 || f == 3))
		free(s2);
	return (new);
}
