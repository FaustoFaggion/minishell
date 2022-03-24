/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_quoted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:07:10 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/24 17:54:10 by fagiusep         ###   ########.fr       */
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
/*
static int check_var(char **tkn, int j)
{
if ((*tkn)[j + 1] = 32 || (*tkn)[j + 1] = 96)
return (1);
else if ((*tkn)[j + 1] >= 37 && (*tkn)[j + 1] <= 41)
return (1); 
else if ((*tkn)[j + 1] >= 43 && (*tkn)[j + 1] <= 44)
return (1);
else if ((*tkn)[j + 1] >= 46 && (*tkn)[j + 1] <= 47)
return (1);
else if ((*tkn)[j + 1] >= 58 && (*tkn)[j + 1] <= 62)
return (1);
else if ((*tkn)[j + 1] >= 91 && (*tkn)[j + 1] <= 93)
return (1);
return (0);
}
*/
static void	expand_d_quote(char **quote)
{
	int	j;
	
	j = 0;
	while ((*quote)[j + 1] != '\"')
	{
			(*quote)[j] = (*quote)[j + 1];
			j++;
	}
	(*quote)[j] = '\0';
	(*quote)[++j] = '\0';
}

static int	d_quoted(t_tkn *tkn, char **token, int j, int i)
{
	char	*temp;
	char	*temp_2;
	char	*quote;
	char	*swap;
	int		start;
	
	printf("inicio j = %d - ", j);
	printf("token = %s - ", *token);
	temp = ft_substr(*token, 0, j);
	printf("temp = %s - ", temp);
	start = j;
	j++;
	while ((*token)[j] != '\"')
		j++;
	j++;
	quote = ft_substr(*token, start, j - start);
	printf("quotes = %s - ", quote);
	start = j;
	while ((*token)[j] != '\0')
		j++;
	temp_2 = ft_substr(*token, start, j - start);
	printf("temp_2 = %s\n", temp_2);
	expand_d_quote(&quote);
	swap = temp;
	temp = ft_strjoin(swap, quote);
	j = ft_strlen(temp);
	free(swap);
	free(quote);
	swap = temp;
	temp = ft_strjoin(swap, temp_2);
	free(swap);
	free(temp_2);
	swap = tkn->tokens[i];
	tkn->tokens[i] = temp;
	free(swap);
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
				j = d_quoted(tkn, &tkn->tokens[i], j, i);
			if (tkn->tokens[i][j] == '\'')
				j = s_quoted(&tkn->tokens[i], j);
			j++;
		}
		i++;
	}
}
