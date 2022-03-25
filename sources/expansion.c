/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:07:10 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/25 15:26:36 by fagiusep         ###   ########.fr       */
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
			if (tkn->tokens[i][j] == '$')
				j = prepare_envp(&tkn, &tkn->tokens[i], j);
			if (tkn->tokens[i][j] == '\"')
				j = prepare_quote(&tkn, &tkn->tokens[i], j, i);
			if (tkn->tokens[i][j] == '\'')
				j = s_quoted(&tkn->tokens[i], j);
			j++;
		}
		i++;
	}
}
