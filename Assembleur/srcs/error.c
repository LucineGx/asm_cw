/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:18:49 by ahouel            #+#    #+#             */
/*   Updated: 2017/12/06 19:15:04 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
**	En cas d error afficher str et exit le programme
*/

void	free_instructions(t_inst *lst)
{
	if (lst->next)
	{
		free_instructions(lst->next);
		lst->next = NULL;
	}
	if (lst->opcode)
		free(lst->opcode);
	if (lst->ocp)
		free(lst->ocp);
	if (lst->param_one)
		free(lst->param_one);
	if (lst->param_two)
		free(lst->param_two);
	if (lst->param_three)
		free(lst->param_three);
	free(lst);
	lst = NULL;
}

void	free_labs(t_lab *lab)
{
	if (lab->next)
	{
		free_labs(lab->next);
		lab->next = NULL;
	}
	if (lab->lst)
		free_instructions(lab->lst);
	free(lab);
	lab = NULL;
}

void	free_champ(t_champ *champ)
{
	if ((*champ).name)
		free((*champ).name);
	if ((*champ).com)
		free((*champ).com);
	if ((*champ).lab)
		free_labs((*champ).lab);
	free(champ);
	champ = NULL;
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	exit_free(char *str, t_champ *champ, char **input)
{
	ft_putstr(str);
	free_champ(champ);
	free_tab(input);
	exit(EXIT_FAILURE);
}
