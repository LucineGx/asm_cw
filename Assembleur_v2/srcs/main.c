/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:56:27 by lgaveria          #+#    #+#             */
/*   Updated: 2017/11/29 19:07:30 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static char	**read_champ(char *file_name)
{
	char	**ret;
	char	buf;
	int		fd;
	int		i;
	int		gnl_ret;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		error("invalid file\n"); //erreur a gerer
	i = 0;
	if (!(ret = malloc(sizeof(char*) * 2)))
		error("kaputt malloc");
	ret[0] = NULL;
	ret[1] = NULL;
	while ((gnl_ret = get_next_line(fd, &(ret[i]))) > 0)
	{
		if (!(ret = realloc(ret, sizeof(char*) * (i + 3))))
			return (NULL); //erreur a gerer
		ret[++i] = NULL;
	}
	if (gnl_ret == -1)
		return (NULL); //erreur a gerer
	close(fd);
	return (ret);
}

static int	create_cor_file(char *file_name, char **input)
{
	char	*tmp;
	int		size;
	int		fd;

	if (!input)
		return (-1);
	size = ft_strlen(file_name);
	if ((tmp = ft_strstr(file_name, ".s")))
		if (!(tmp[2]))
		{
			if (!(tmp = malloc(sizeof(char) * (size + 3))))
				return (-1);
			tmp = ft_strncpy(tmp, file_name, size - 1);
			tmp[size - 1] = 'c';
			tmp[size] = 'o';
			tmp[size + 1] = 'r';
			tmp[size + 2] = '\0';
			fd = open(tmp, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			free(tmp);
			return (fd);
		}
	return (-1);
}

void		init_champ(t_champ *new)
{
	(*new).name = NULL;
	(*new).comment = 0;
}

int			main(int argc, char **argv)
{
	int		i;
	char	**input;
	t_champ	champ;

	i = 1;
	if (argc < 2)
		error("usage : ./asm [champ to compile]\n");
	while (i != argc)
	{
		input = read_champ(argv[i]);
		init_champ(&champ);
		manage_header(create_cor_file(argv[i], input), input, &champ);
		free_tab(input);
		i++;
	}
	return (0);
}
