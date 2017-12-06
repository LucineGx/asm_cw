#include "../includes/asm.h"

void	print_tab(char **tab)
{
	if (!tab)
		return ;
	int i = 0;
	while (tab[i])
	{
		ft_putstr(tab[i++]);
		write(1, "\n", 1);
	}
}
