/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_it.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:00:49 by lgaveria          #+#    #+#             */
/*   Updated: 2017/12/06 19:17:13 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	create_cor_file(char *file_name, t_champ *champ)
{
	char	*tmp;
	int		size;
	int		fd;

	size = ft_strlen(file_name);
	if ((tmp = ft_strstr(file_name, ".s")))
	{
		if(!(tmp[2]))
		{
			if (!(tmp = malloc(sizeof(char) * (size + 3))))
				exit_free("unsuccessful malloc\n", champ, NULL);
			tmp = ft_strncpy(tmp, file_name, size - 1);
			tmp[size - 1] = '\0';
			tmp = ft_strcat(tmp, "cor\0");
			fd = open(tmp, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			free(tmp);
			return (fd);
		}
	}
	else
		exit_free("invalid file name\n", champ, NULL);
	return (-1);
}

static void	write_header(int fd, t_champ *champ)
{
	int		tmp;
	int		count;

	tmp = COREWAR_EXEC_MAGIC;
	ft_bswap(&tmp, 4);
	write(fd, &tmp, 4);
	write(fd, (*champ).name, ft_strlen((*champ).name));
	count = ft_strlen((*champ).name) + 3;
	printf("[00] COUNT = %d\n", count + 1);
	while ((++count) < PROG_NAME_LENGTH + 5)
		write(fd, "\0", 1);
	printf("[01] COUNT = %d\n", count);
	while ((count++) % 4 != 0)
		write(fd, "\0", 1);
	printf("[02] COUNT = %d\n", count - 1);
	//___prog_size pas encore gere___
	tmp = 0;//tmp = (*champ).prog_size;
	//ft_bswap(&tmp, 4);
	write(fd, &tmp, 4);
	write(fd, (*champ).com, ft_strlen((*champ).com));
	count += ft_strlen((*champ).com) + 2;
	printf("[03] COUNT = %d\n", count + 1);
	while ((++count) && (tmp++) + ft_strlen((*champ).com) <= COMMENT_LENGTH)
		write(fd, "\0", 1);
	printf("[04] COUNT = %d\n", count);
	while ((count++) % 4 != 0)
		write(fd, "\0", 1);
	printf("[05] COUNT = %d\n", count - 1);
}

void		end_it(t_champ *champ, char *file_name)
{
	int fd;

	fd = create_cor_file(file_name, champ);
	write_header(fd, champ);
	write(1, file_name, ft_strlen(file_name));
	write(1, " done\n", 6);
	free_champ(champ);
}
