#include "libft.h"

char	*ft_strdup_free(char *s)
{
	char *new;
	new = ft_strdup(s);
	free(s);
	return (new);
}
