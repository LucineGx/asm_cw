/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:54:43 by lgaveria          #+#    #+#             */
/*   Updated: 2017/12/06 19:59:05 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
** on remplit tranquillement les variables qui correspondent au header dans la 
** structure
*/

static void	check_comment(char **input, t_champ *champ, int i)
{
	int		j;
	int		count;
	char	zero;

	if (ft_strncmp(input[i], ".comment", 8) != 0)
		return ;
	if ((*champ).com != 0)
		exit_free("a champ can have only one comment\n", champ, input);
	j = 8;
	while (ft_iswhitespace(input[i][j]))
		j++;
	count = 0;
	while (input[i][++j] && input[i][j] != '\"' && count < COMMENT_LENGTH)
		count++;
	(*champ).com = ft_strsub(input[i], j - count, count);
}

static void	check_name(char **input, t_champ *champ, int i)
{
	int		j;
	int		count;

	if (ft_strncmp(input[i], ".name", 5) != 0)
		return ;
	if ((*champ).name)
		exit_free("a champ can have only one name\n", champ, input);
	j = 5;
	while (ft_iswhitespace(input[i][j]))
		j++;
	count = 0;
	while (input[i][++j] && input[i][j] != '\"' && count < PROG_NAME_LENGTH)
		count++;
	(*champ).name = ft_strsub(input[i], j - count, count);
}

t_champ		*manage_header(char **input, t_champ *champ)
{
	int	i;

	i = 0;
	while (input[i] && ((*champ).name == NULL || (*champ).com == NULL))
	{
		if (input[i][0] == COMMENT_CHAR)
			i++;
		else
		{
			check_name(input, champ, i);
			check_comment(input, champ, i);
			i++;
		}
	}
	return (do_parsing(champ, input, i));
}
