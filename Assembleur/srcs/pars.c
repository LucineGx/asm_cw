/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 19:56:42 by lgaveria          #+#    #+#             */
/*   Updated: 2017/12/06 21:08:46 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int		how_many_label_char(char *s)
{
	int		count;
	int		i;
	int		j;
	char	*to_compare;

	if (!s)
		return (0);
	count = 0;
	i = 0;
	to_compare = LABEL_CHARS;
	while (s[i] && i == count)
	{
		j = -1;
		while (to_compare[++j])
			if (to_compare[j] == s[i])
				count++;
		i++;
	}
	if (s[i - 1] == LABEL_CHAR)
		return (count);
	else
		return(0);
}

static t_champ	*new_label(char *name, t_champ *champ)
{
	t_lab	*new;
	t_lab	*tmp;

	if (!(new = malloc(sizeof(t_lab))))
		return (NULL); //ATTENTION
	new->pc = 0;
	new->name = ft_strsub(name, 0, how_many_label_char(name));
	new->lst = NULL;
	new->next = NULL;
	tmp = (*champ).lab;
	if (!tmp)
		(*champ).lab = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (champ);
}

static t_champ	*new_instruction(char *name, t_champ *champ)
{
	t_inst	*new;
	t_inst	*tmp;
	t_lab	*current_lab;

	if (!(new = malloc(sizeof(t_inst))))
		return (NULL); //ATTENTION
	new->size = 0;
	new->name = ft_strdup(name);
	new->next = NULL;
	current_lab = (*champ).lab;
	if (!current_lab)
		current_lab = (new_label("origin_label", champ))->lab;
	while (current_lab->next != NULL)
		current_lab = current_lab->next;
	tmp = current_lab->lst;
	if (!tmp)
		current_lab->lst = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (champ);
}

static char		**init_instruction_tab(void)
{
	char	**tab;

	if (!(tab = malloc(sizeof(char*) * 17)))
		return (NULL); // ATTENTION
	tab[0] = ft_strdup("live");
	tab[1] = ft_strdup("ld");
	tab[2] = ft_strdup("st");
	tab[3] = ft_strdup("add");
	tab[4] = ft_strdup("sub");
	tab[5] = ft_strdup("and");
	tab[6] = ft_strdup("or");
	tab[7] = ft_strdup("xor");
	tab[8] = ft_strdup("zjump");
	tab[9] = ft_strdup("ldi");
	tab[10] = ft_strdup("sti");
	tab[11] = ft_strdup("fork");
	tab[12] = ft_strdup("lld");
	tab[13] = ft_strdup("lldi");
	tab[14] = ft_strdup("lfork");
	tab[15] = ft_strdup("aff");
	tab[16] = NULL;
	return (tab);
}

static int		get_instruction(char *s, t_champ *champ)
{
	char	**to_compare;
	int		i;

	to_compare = init_instruction_tab();
	i = 0;
	while (to_compare[i])
	{
		if (ft_strncmp(s, to_compare[i], ft_strlen(to_compare[i])) == 0)
		{
			champ = new_instruction(to_compare[i], champ);
			return (1);
		}
		i++;
	}
	return (0);
}

t_champ			*do_parsing(t_champ *champ, char **input, int i)
{
	int		j;

	while (input[++i])
	{
		j = -1;
		while (j != -2 && input[i][++j])
		{
			if (ft_iswhitespace(input[i][j]))
				j++;
			else if (input[i][j] == COMMENT_CHAR)
				j = -2;
			else if (how_many_label_char(&(input[i][j])))
			{
				champ = new_label(&(input[i][j]), champ);
				j += how_many_label_char(&(input[i][j]));
			}
			else if (get_instruction(&(input[i][j]), champ))
				j = -2;
		}
	}
	return (champ);
}
