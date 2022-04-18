/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_d_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:07:23 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/18 14:49:16 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_for_envp(t_tkn **tkn, char **quote)
{
	int	j;

	j = 0;
	while ((*quote)[j] != '\0')
	{
		if ((*quote)[j] == '$')
			j = prepare_envp(tkn, quote, j);
		j++;
	}
}

static void	expand_d_quote(t_tkn **tkn, char **quote)
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
	check_for_envp(tkn, quote);
}

int	prepare_quote(t_tkn **tkn, char **token, int j, int i)
{
	char	*temp;
	char	*temp_2;
	char	*quote;
	int		start;

	temp = ft_substr(*token, 0, j);
	start = j;
	j++;
	while ((*token)[j] != '\"')
		j++;
	j++;
	quote = ft_substr(*token, start, j - start);
	start = j;
	while ((*token)[j] != '\0')
		j++;
	temp_2 = ft_substr(*token, start, j - start);
	expand_d_quote(tkn, &quote);
	j = join_token(&(*tkn)->tokens[i], &temp, &quote, &temp_2);
	return (j - 1);
}
