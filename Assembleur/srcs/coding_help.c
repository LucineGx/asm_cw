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

void	print_lst(t_champ *champ)
{
	t_lab	*labtmp;
	t_inst	*insttmp;

	printf("NAME = %s\n\t\t%s\n", champ->name, champ->com);
	printf("\n|label|\n");
	labtmp = champ->lab;
	while (labtmp)
	{
		printf("\n[%s]\n", labtmp->name);
		insttmp = labtmp->lst;
		while (insttmp)
		{
			printf("\t\t%s\n", insttmp->name);
			insttmp = insttmp->next;
		}
		labtmp = labtmp->next;
	}
}
