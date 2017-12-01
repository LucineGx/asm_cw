/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:54:43 by lgaveria          #+#    #+#             */
/*   Updated: 2017/11/29 19:44:19 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	check_comment(int fd, char *input, t_champ *champ)
{
	int		i;
	int		count;
	char	zero;

	if (ft_strncmp(input, ".comment", 8) != 0)
		return ; //erreur a gerer
	if ((*champ).comment != 0)
		return ; //ereur a gerer
	i = 8;
	while (ft_iswhitespace(input[i]))
		i++;
	count = 0;
	while (input[++i] != '\"' && count < COMMENT_LENGTH)
	{
		write(fd, &(input[i]), 1);
		count++;
	}
	(*champ).comment = 1;
	zero = 0;
	while (count <= COMMENT_LENGTH)
	{
		write(fd, &zero, 1);
		count++;
	}
}

/*
** en haut et en bas:
** manque la gestion d'erreur sur ce qui compose le reste de la ligne
*/

void	check_name(int fd, char *input, t_champ *champ)
{
	int		i;
	int		count;
	char	zero;

	if (ft_strncmp(input, ".name", 5) != 0)
		return ; //erreur a gerer
	if ((*champ).name)
		return ; //erreur a gerer
	i = 5;
	while (ft_iswhitespace(input[i]))
		i++;
	count = 0;
	while (input[++i] && input[i] != '\"' && count < PROG_NAME_LENGTH)
	{
		write(fd, &(input[i]), 1);
		(*champ).name = ft_strjoinchar((*champ).name, input[i]);
		count++;
	}
	zero = 0;
	while (count <= PROG_NAME_LENGTH)
	{
		write(fd, &zero, 1);
		count++;
	}
}

void	manage_header(int fd, char **input, t_champ *champ)
{
	int	magic ;
	int	i;

	if (fd == -1)
		return ;
	magic = COREWAR_EXEC_MAGIC;
	ft_bswap(&magic, sizeof(int));
	write(fd, &magic, 4);
	i = 0;
	while (input[i] && (!(*champ).name || !(*champ).comment))
	{
		if (input[i][0] == '#')
			i++;
		else
		{
			check_name(fd, input[i], champ);
			check_comment(fd, input[i], champ);
			i++;
		}
	}
	close(fd);
}
