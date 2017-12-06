/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:56:27 by lgaveria          #+#    #+#             */
/*   Updated: 2017/12/06 21:08:48 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static char		**read_champ(char *file_name)
{
	char	**ret;
	int		fd;
	int		i;
	int		gnl_ret;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		exit_free("invalid file\n", NULL, NULL);
	if (!(ret = malloc(sizeof(char*) * 1)))
		exit_free("unsuccessful malloc\n", NULL, NULL);
	i = 0;
	while ((gnl_ret = get_next_line(fd, &(ret[i]))) > 0)
	{
		if (!(ret = realloc(ret, sizeof(char*) * (i + 2))))
			exit_free("unsuccessful malloc\n", NULL, NULL);
		ret[++i] = NULL;
	}
	if (gnl_ret == -1)
		exit_free("unsuccessful read\n", NULL, ret); //erreur a gerer
	close(fd);
	return (ret);
}

static t_champ	*init_champ(t_champ *new, char **input)
{
	if (!(new = malloc(sizeof(t_champ))))
		exit_free("unsuccessful malloc\n", NULL, input);
	(*new).name = NULL;
	(*new).com = NULL;
	(*new).lab = NULL;
	return (new);
}

int				main(int argc, char **argv)
{
	int		i;
	char	**input;
	t_champ	*champ;

	i = 1;
	if (argc < 2)
		exit_free("usage : ./asm [champ to compile]\n", NULL, NULL);
	while (i != argc)
	{
		input = read_champ(argv[i]);
		if (!input)
			exit_free("invalid file\n", NULL, NULL);
		champ = init_champ(champ, input);
		champ = manage_header(input, champ);
		free_tab(input); // sera modifie
		end_it(champ, argv[i]);
		i++;
	}
	return (0);
}
