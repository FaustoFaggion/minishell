/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_quoted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:07:10 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/23 18:20:23 by fagiusep         ###   ########.fr       */
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

static int	d_quoted(char **tkn, int j)
{
	int	k;
	
	k = 0;
	while ((*tkn)[j + k + 1] != '\0')
	{
		if ((*tkn)[j + k + 1] == '\"')
			k++;
		else
		{
			(*tkn)[j] = (*tkn)[j + k + 1];
			j++;
		}
	}
	while ((*tkn)[j] != '\0')
		(*tkn)[j] = '\0';
	return (j);
}

void	expansion_quote(t_tkn *tkn)
{
	int		i;
	int		j;

	i = 0;
	while (tkn->tokens[i])
	{
		j = 0;
		while (tkn->tokens[i][j] != '\0')
		{
			if (tkn->tokens[i][j] == '\"')
			{
				printf("token expansion %s\n", tkn->tokens[i]);
				j = d_quoted(&tkn->tokens[i], j);
				printf("token expansion after  %s\n", tkn->tokens[i]);
			}
			if (tkn->tokens[i][j] == '\'')
				s_quoted(&tkn->tokens[i]);
			j++;
		}
		i++;
	}
}
