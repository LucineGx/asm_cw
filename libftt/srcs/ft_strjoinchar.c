#include "libft.h"

char	*ft_strjoinchar(char *s, char c)
{
	char	*ret;

	if (s)
	{
		if(!(ret = malloc(sizeof(char) * (ft_strlen(s) + 2))))
			return (NULL);
		ret = ft_strcpy(ret, s);
		ret[ft_strlen(s)] = c;
		ret[ft_strlen(s) + 1] = '\0';
		free(s);
	}
	else
	{
		if (!(ret = malloc(sizeof(char) * 2)))
			return (NULL);
		ret[0] = c;
		ret[1] = '\0';
	}
	return (ret);
}
