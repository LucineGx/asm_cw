/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:01:26 by lgaveria          #+#    #+#             */
/*   Updated: 2017/11/29 18:57:09 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include <stdlib.h>
# include "op.h"
# include "../../libftt/srcs/libft.h"

typedef struct	s_champ
{
	char		*name;
	int			comment;
}				t_champ;

void			manage_header(int fd, char **input, t_champ *champ);
void			free_tab(char **tab);

/*
** gestion d'erreur
*/

void	error(char *str);

#endif
