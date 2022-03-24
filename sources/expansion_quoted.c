/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_quoted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:07:10 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/24 08:08:29 by fagiusep         ###   ########.fr       */
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
	while ((*tkn)[j + k	+ 2] != '\0')
	{
		(*tkn)[j + k] = (*tkn)[j + k + 2];
		k++;
	}
	(*tkn)[j + k] = '\0';
	return (j - 1);
}

static int	prepare_envp(char *token, int j)
{
	int		len;
	char	*temp;
	
	len = 0;
	while (token[j + len] != ' ' && token[j + len] != '\"')
		len++;
	temp = ft_substr(token, j, len);
	printf("temp %s\n", temp);
	free(temp);
	return (j + 1);
}

static int	d_quoted(char **tkn, int j)
{
	int	k;
	
	while ((*tkn)[j + 1] != '\"')
	{
		if ((*tkn)[j + 1] == '$')
			j = prepare_envp(*tkn, (j + 1));
		else
		{
			(*tkn)[j] = (*tkn)[j + 1];
			j++;
		}
	}
	k = 0;
	while ((*tkn)[j + k	+ 2] != '\0')
	{
		(*tkn)[j + k] = (*tkn)[j + k + 2];
		k++;
	}
	(*tkn)[j + k] = '\0';
	return (j - 1);
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
				j = d_quoted(&tkn->tokens[i], j);
				printf("j = %d ", j);
				printf("tkn = %s\n", tkn->tokens[i]);
			}
			if (tkn->tokens[i][j] == '\'')
				j = s_quoted(&tkn->tokens[i], j);
			j++;
		}
		i++;
	}
}
