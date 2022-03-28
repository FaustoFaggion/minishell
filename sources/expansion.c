/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:07:10 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/28 16:42:27 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	s_quoted(char **tkn, int j)
{
	int	k;

	while ((*tkn)[j + 1] != '\'')
	{
		(*tkn)[j] = (*tkn)[j + 1];
		j++;
	}
	k = 0;
	while ((*tkn)[j + k + 2] != '\0')
	{
		(*tkn)[j + k] = (*tkn)[j + k + 2];
		k++;
	}
	(*tkn)[j + k] = '\0';
	return (j - 1);
}

static void	cmd_path_ck(t_tkn *tkn, int i)
{
	int x;
	
	x = -1;
	if (ft_strncmp(tkn->tokens[i], "/usr/bin/", 9) == 0)
	{
		while (tkn->tokens[i][++x + 9] != '\0')
			tkn->tokens[i][x] = tkn->tokens[i][x + 9];
		tkn->tokens[i][x] = '\0';
		while (tkn->tokens[i][++x] != '\0')
			tkn->tokens[i][x] = '\0';
	}
	else if (ft_strncmp(tkn->tokens[i], "/bin/", 5) == 0)
	{
		while (tkn->tokens[i][++x + 5] != '\0')
			tkn->tokens[i][x] = tkn->tokens[i][x + 5];
		tkn->tokens[i][x] = '\0';
		while (tkn->tokens[i][++x] != '\0')
			tkn->tokens[i][x] = '\0';
	}
}

void	expansion(t_tkn *tkn)
{
	int		i;
	int		j;

	i = 0;
	while (tkn->tokens[i])
	{
		j = 0;
		while (tkn->tokens[i][j] != '\0')
		{
			if(j == 0)
				cmd_path_ck(tkn, i);
			if (tkn->tokens[i][j] == '$')
				j = prepare_envp(&tkn, &tkn->tokens[i], j);
			else if (tkn->tokens[i][j] == '\"')
				j = prepare_quote(&tkn, &tkn->tokens[i], j, i);
			else if (tkn->tokens[i][j] == '\'')
				j = s_quoted(&tkn->tokens[i], j);
			j++;
		}
		i++;
	}
}
