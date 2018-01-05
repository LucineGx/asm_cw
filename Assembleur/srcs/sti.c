#include "../includes/asm.h"

static int	get_first_param(char *s, t_inst *new)
{
	int	i;

	i = 0;
	while (s[i] && ft_iswhitespace(s[i]))
		i++;
	if (s[i++] != 'r' || !(ft_isdigit(s[i + 1])))
		return (0);
	new->param_one = itohex(ft_atoi(&(s[1])), 1);
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (s[i] != SEPARATOR_CHAR)
		return (0);
	new->size_one[1] = 1;
	return (1);
}

static int	get_second_param(char *s, t_inst *new)
{
	int	i;

	i = 0;
	while (s[i] && ft_iswhitespace(s[i]))
		i++;
	if (s[i] == 'r' && ft_isdigit(s[i + 1]))
	{
		new->param_two = itohex(ft_atoi(&(s[1])), 1);
		new->size_two[0] = 1;
		new->size_two[1] = 1;
	}
	else if (s[i] == '%' && ft_isdigit(s[i + 1]))
	{
		new->param_two = itohex(ft_atoi(&(s[1])), 2);
		new->size_two[0] = 2;
		new->size_two[1] = 2;
	}
}

static int	get_third_param(char *s, t_inst *new)
{
}

static char	get_ocp(t_inst *new)
{
	int ocp;

	ocp = new->size_one[1] * 64;
	ocp += new->size_two[1] * 16;
	ocp += new->size_three[1] * 4;
	return (ocp);
}

t_champ		*make_sti(t_champ *pl, char *s)
{
	int		i;
	t_inst	*new;

	i = 3;
	new = (new_instruction("sti\0", &pl));
	new->opcode = 11;
	if (!(new->size_one[0] = get_first_param(&s[i], new)))
		return (NULL); // a voir
	while (s[i++] != SEPARATOR_CHAR);
	if (!(new->size_two[0] = get_second_param(&s[i], new)))
		return (NULL); // a voir
	while (s[i++] != SEPARATOR_CHAR);
	if (!(new->size_three[0] = get_third_param(&s[i], new)))
		return (NULL); // a voir
	new->ocp = get_ocp(new);
}
