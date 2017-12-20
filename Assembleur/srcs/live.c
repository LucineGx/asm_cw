/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:17:40 by lgaveria          #+#    #+#             */
/*   Updated: 2017/12/18 19:56:12 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

t_champ		*make_live(t_champ *champ, char *s)
{
	int		i;
	int		direct;
	t_inst	*new;

	i = 4;
	while (s[i] && ft_iswhitespace(s[i]))
		i++;
	if (s[i] != '%')
		return (champ); // a gerer
	i++;
	direct = ft_atoi(&(s[i]));
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (s[i] && !(ft_iswhitespace(s[i])))
		return (champ); // a gerer
	new = (new_instruction("live\0", &champ));
	new->size = 5;
	new->opcode = 1;
	new->param_one = itohex(direct, 4);
	printf("opcode: |%x|\nocp: |%x|\nparam_one: 0x|%x| ou |%s|\n", new->opcode, new->ocp, new->param_one, new->param_one);
	return (champ);
}
