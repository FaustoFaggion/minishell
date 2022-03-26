/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:59:12 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/26 12:18:18 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sintax_error(t_tkn *tkn, char c, int i)
{
	if (i == 1)
	{
		printf("bash: erro de sintaxe próximo ao token inesperado '%c'\n", c);
		exit_shell(tkn);
	//	exit(1);
	}
	if (i == 2)
	{
		printf("bash: erro de sintaxe próximo ao token inesperado '%c%c'\n",
			c, c);
		exit_shell(tkn);
	//	exit(1);
	}
}

static int	check_cmd(t_tkn *tkn, int i, char c, int x)
{
	if (tkn->lexemas[++i] == NULL)
	{
		sintax_error(tkn, c, x);
		return (-1);
	}
	else
	{
		if (ft_strncmp(tkn->lexemas[i], "WORD", 4) == 0)
			i++;
		else
		{
			sintax_error(tkn, c, x);
			return (-1);
		}
	}
	return (i);
}

static int	check_pipe(t_tkn *tkn, int i)
{
	if (tkn->lexemas[++i] == NULL)
	{
		sintax_error(tkn, '|', 1);
		return (-1);
	}	
	return (i);
}

int	sintax_analysis(t_tkn *tkn)
{
	int	i;

	i = 0;
	if (ft_strncmp(tkn->lexemas[i], "PIPE", 4) == 0)
	{
		sintax_error(tkn, '|', 1);
		return (1);
	}
	while (tkn->lexemas[i] != NULL)
	{
		if (ft_strncmp(tkn->lexemas[i], "LESS", 4) == 0)
			i = check_cmd(tkn, i, '<', 1);
		else if (ft_strncmp(tkn->lexemas[i], "DLESS", 5) == 0)
			i = check_cmd(tkn, i, '<', 2);
		else if (ft_strncmp(tkn->lexemas[i], "GREAT", 5) == 0)
			i = check_cmd(tkn, i, '>', 1);
		else if (ft_strncmp(tkn->lexemas[i], "DGREAT", 6) == 0)
			i = check_cmd(tkn, i, '>', 2);
		else if (ft_strncmp(tkn->lexemas[i], "ASSIGNMENT_WORD", 15) == 0)
			i++;
		else if (ft_strncmp(tkn->lexemas[i], "WORD", 4) == 0)
			i++;
		else if (ft_strncmp(tkn->lexemas[i], "PIPE", 4) == 0)
			i = check_pipe(tkn, i);
		else
			break ;
		if (i == -1)
			return (1);
	}
	return (0);
}
