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

/*
** je vais remplacer cette string longue comme la mort et immaniable en un joli
** tableau finalement.
*/

void	check_comment(int fd, char *input)
{
	int		i;
	int		count;
	char	zero;

	if (ft_strncmp(input, ".comment \"", 10) != 0)
		return ; //erreur a gerer
	i = 9;
	count = 0;
	while (input[++i] != '\"' && count <= COMMENT_LENGTH)
	{
		write(fd, &(input[i]), 1);
		count++;
	}
	if (input[i + 1] != '\n')
		return ; //erreur a gerer
	zero = 0;
	while (count <= COMMENT_LENGTH)
	{
		write(fd, &zero, 1);
		count++;
	}
}

void	check_name(int fd, char *input)
{
	int		i;
	int		count;
	char	zero;

	if (ft_strncmp(input, ".name \"", 7) != 0)
		return ; //erreur a gerer
	i = 6;
	count = 0;
	while (input[++i] != '\"' && count <= PROG_NAME_LENGTH)
	{
		write(fd, &(input[i]), 1);
		count++;
	}
	if (input[i + 1] != '\n')
		return ; //erreur a gerer
	zero = 0;
	while (count <= PROG_NAME_LENGTH)
	{
		write(fd, &zero, 1);
		count++;
	}
}

void	manage_header(int fd, char *input)
{
	int magic ;

	write(1, "ok0\n", 4);
	if (fd == -1)
		return ;
	write(1, "ok1\n", 4);
	magic = COREWAR_EXEC_MAGIC;
	ft_bswap(&magic, sizeof(int));
	write(fd, &magic, 4);
	check_name(fd, input);
	check_comment(fd, ft_strstr(input, ".comment"));
	close(fd);
}
