/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_quoted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:07:10 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/07 21:23:43 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	s_quoted(char **tkn)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tkn[i][j] != '\'')
		j++;
	while (tkn[i][j + 1] != '\'')
	{
		tkn[i][j] = tkn[i][j + 1];
		j++;
	}
	tkn[i][j] = '\0';
	tkn[i][++j] = '\0';
}

static void	d_quoted(char **tkn)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tkn[i][j] != '\"')
		j++;
	while (tkn[i][j + 1] != '\"')
	{
		tkn[i][j] = tkn[i][j + 1];
		j++;
	}
	tkn[i][j] = '\0';
	tkn[i][++j] = '\0';
}

static int	check_amb_var(t_tkn *tkn, int i)
{
	int	j;
	int	flag;

	j = 1;
	flag = 0;
	while (tkn->tokens[i][j] != '\"')
	{
		if (tkn->tokens[i][j] == '$')
			flag = 1;
		j++;
	}
	return (flag);
}

void	expansion_quote(t_tkn *tkn)
{
	int		i;
	int		flag;
	int		j;
	int		qt;
	int		dqt;

	i = 0;
	while (tkn->tokens[i])
	{
		j = 0;
		dqt = 0;
		qt = 0;
		while (tkn->tokens[i][j] != '\0')
		{
			if (tkn->tokens[i][j] == '\"')
				dqt++;
			if (tkn->tokens[i][j] == '\'')
				qt++;
			j++;
		}
		if (dqt == 2)
		{
			flag = check_amb_var(tkn, i);
			if (flag == 0)
				d_quoted(&tkn->tokens[i]);
			else
				quoted_envp(&tkn->tokens[i]);
		}
		if (qt == 2)
			s_quoted(&tkn->tokens[i]);
		i++;
	}
}
