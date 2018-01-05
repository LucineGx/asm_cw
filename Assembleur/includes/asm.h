/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:01:26 by lgaveria          #+#    #+#             */
/*   Updated: 2017/12/18 19:56:23 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include <stdlib.h>
# include <stdio.h> //
# include "op.h"
# include "../../libft/srcs/libft.h"

typedef struct	s_inst
{
	int				size;
	int				pc;
	char			*name;
	char			opcode;
	char			ocp;
	char			*param_one;
	int				size_one[2];
	char			*param_two;
	int				size_two[2];
	char			*param_three;
	int				size_three[2];
	struct s_inst	*next;
}				t_inst;

typedef struct	s_lab
{
	int				pc;
	char			*name;
	t_inst			*lst;
	struct s_lab	*next;
}				t_lab;

typedef struct	s_champ
{
	int			current_pc;
	header_t	*head;
	t_lab		*lab;
}				t_champ;

t_champ			*manage_header(char **input, t_champ *champ);
t_champ			*do_parsing(t_champ *champ, char **input, int i);
void			end_it(t_champ *champ, char *file_name);
t_inst			*new_instruction(char *name, t_champ **champ);
t_champ			*new_label(char *name, t_champ *champ);
int				how_many_label_char(char *s);
char			*itohex(int n, int size);
t_champ			*make_live(t_champ *pl, char *s);

/*
** gestion d'erreur && free
*/

void			exit_free(char *str, t_champ *champ, char **input);
void			free_tab(char **tab);
void			free_champ(t_champ *champ);

/*
** fonctions a supprimer dans la version finale
*/

void			print_tab(char **tab);
void			print_lst(t_champ *champ);

#endif
