/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_it.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:00:49 by lgaveria          #+#    #+#             */
/*   Updated: 2017/12/18 19:37:46 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
**	Ecriture de la structure du header dans le .cor.
**	!!! manque toujours le prog_size
*/

static void	write_header(int fd, t_champ *pl)
{
	unsigned int	tmp;

	tmp = COREWAR_EXEC_MAGIC;
	ft_bswap(&tmp, 4);
	pl->head->magic = tmp;
	write(fd, pl->head, sizeof(header_t));
	free(pl->head);
	pl->head = NULL;
}

/*
**	Création ou ouvertured u fichier .cor, renvoie le file descriptor
**	correspondant.
*/

static int	create_cor_file(char *file_name, t_champ *pl)
{
	char	*tmp;
	int		size;
	int		fd;

	size = ft_strlen(file_name);
	if (!(tmp = ft_memalloc(sizeof(char) * (size + 3))))
		exit_free("unsuccessful malloc\n", pl, NULL);
	tmp = ft_strncpy(tmp, file_name, size - 1);
	tmp[size - 1] = '\0';
	tmp = ft_strcat(tmp, "cor\0");
	fd = open(tmp, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	free(tmp);
	write_header(fd, pl);
	return (fd);
}

/*
**	Ecriture du header puis des instructions encodées dans le fichier. D'abord
**	l'opcode, puis l'ocp et enfin les parametres un par un.
*/

void		end_it(t_champ *pl, char *file_name)
{
	int		fd;
	t_lab	*ltmp;
	t_inst	*itmp;
	char	*to_write;

	fd = create_cor_file(file_name, pl);
	ltmp = pl->lab;
	while (ltmp)
	{
		itmp = ltmp->lst;
		while(itmp)
		{
			write(fd, &(itmp->opcode), 1);
			to_write = ft_strjoin_free(itmp->ocp, itmp->param_one, 0);
			to_write = ft_strjoin_free(to_write, itmp->param_two, 1);
			to_write = ft_strjoin_free(to_write, itmp->param_three, 1);
			if (to_write)
				write(fd, to_write, ft_strlen(to_write));
			itmp = itmp->next;
		}
		ltmp = ltmp->next;
	}
	write(1, file_name, ft_strlen(file_name));
	write(1, " executed\n", 10);
	free_champ(pl);
}
