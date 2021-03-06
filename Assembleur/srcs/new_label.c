/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:53:42 by lgaveria          #+#    #+#             */
/*   Updated: 2018/01/02 14:59:02 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

t_champ		*new_label(char *name, t_champ *pl)
{
	t_lab	*new;
	t_lab	*tmp;
	int		i;

	i = 0;
	while (ft_iswhitespace(name[i]))
		i++;
	name = &(name[i]);
	if (!(new = ft_memalloc(sizeof(t_lab))))
		return (NULL); // a gerer
	new->name = ft_strsub(name, 0, how_many_label_char(name));
	tmp = (*pl).lab;
	if (!tmp)
		(*pl).lab = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (pl);
}
