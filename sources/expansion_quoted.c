/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_quoted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:07:10 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/25 12:33:53 by fagiusep         ###   ########.fr       */
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

static int check_expansion_2(char **tkn, int j)
{
	if ((*tkn)[j] == 95)
		return (0);
	else if ((*tkn)[j] >= 48 && (*tkn)[j] <= 57)
		return (0); 
	else if ((*tkn)[j] >= 65 && (*tkn)[j] <= 90)
		return (0);
	else if ((*tkn)[j] >= 97 && (*tkn)[j] <= 122)
		return (0);
	return (1);
}

static int check_expansion_1(char **tkn, int j)
{
	if ((*tkn)[j] == 33 || (*tkn)[j] == 96)
		return (0);
	else if ((*tkn)[j] >= 35 && (*tkn)[j] <= 60)
		return (0); 
	else if ((*tkn)[j] >= 62 && (*tkn)[j] <= 64)
		return (0);
	else if ((*tkn)[j] >= 91 && (*tkn)[j] <= 94)
		return (0);
	else if ((*tkn)[j] >= 123 && (*tkn)[j] <= 126)
		return (0);
	return (1);
}

static int check_expansion(t_tkn **tkn, char **quote, int j)
{
	if ((*quote)[j] == '?')
	{
		j++;
		printf("falta expandir '?'");
		(*tkn)->exp_flag = 0;
	}	
	else if (check_expansion_1(quote, j) == 0)
	{
		(*tkn)->exp_start--;
		while ((*quote)[j] != ' ' && (*quote)[j] != '\0')
			j++;
		(*tkn)->exp_flag = 1;
	}
	else
	{
		while ((*quote)[j] != ' ' && (*quote)[j] != '\0'
			&& check_expansion_2(quote, j) == 0) 
			j++;
		(*tkn)->exp_flag = 0;
	}
	return (j);
}

static void	expand_envp(t_tkn **tkn, char **exp_envp)
{
	char	**temp;
	char	*swap;
	int		j;

	j = 0;
	while ((*tkn)->envp[j] != NULL)
	{
		if (ft_strncmp((*tkn)->envp[j], *exp_envp, ft_strlen(*exp_envp)) == 0)
		{
			temp = ft_split((*tkn)->envp[j], '=');
			swap = *exp_envp;
			*exp_envp = ft_strdup(temp[1]);
			free_tab(&temp, 2);
			free(swap);
			break ;
		}
		j++;
	}
	if ((*tkn)->envp[j] == NULL)
	{
		swap = *exp_envp;
		*exp_envp = ft_strdup(" ");
		free(swap);
	}
}

static int	prepare_envp(t_tkn **tkn, char **quote, int j, int i)
{
	char	*temp;
	char	*temp_2;
	char	*exp_envp;
	char	*swap;
	
	printf("env j = %d - ", j);
	printf("quote = %s - ", *quote);
	temp = ft_substr(*quote, 0, j);
	printf("temp = %s - ", temp);
	j++;
	(*tkn)->exp_start = j;
	j = check_expansion(tkn, quote, j);
	exp_envp = ft_substr(*quote, (*tkn)->exp_start, j - (*tkn)->exp_start);
	printf("..exp_envp = %s - ", exp_envp);
	(*tkn)->exp_start = j;
	while ((*quote)[j] != '\0')
		j++;
	temp_2 = ft_substr(*quote, (*tkn)->exp_start, j - (*tkn)->exp_start);
	printf("..temp_2 = %s\n", temp_2);
	
	printf("\n\nlexemas = %s\n\n", (*tkn)->lexemas[i]);
	
	if ((*tkn)->exp_flag == 0)
	expand_envp(tkn, &exp_envp);
	if (exp_envp[0] != ' ')
	{
		swap = temp;
		temp = ft_strjoin(swap, exp_envp);
		j = ft_strlen(temp);
		free(swap);
		printf(">>temp = %s\n", temp);
	}
	swap = temp;
	temp = ft_strjoin(swap, temp_2);
	free(swap);
	swap = *quote;
	*quote = ft_strdup(temp);
	free(swap);
	free(exp_envp);
	free(temp_2);
	return (j - 1);
}
static void	check_for_envp(t_tkn **tkn, char **quote, int i)
{
	int	j;
	
	j = 0;
	while ((*quote)[j] != '\0')
	{
		if ((*quote)[j] == '$')
			j = prepare_envp(tkn, quote, j, i);
		j++;
	}
}

static void	expand_d_quote(t_tkn **tkn, char **quote, int i)
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
	check_for_envp(tkn, quote, i);
}

static int	prepare_quote(t_tkn **tkn, char **token, int j, int i)
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
	expand_d_quote(tkn, &quote, i);
	printf("\n>>>>>>>quote = %s\n", quote);
	swap = temp;
	temp = ft_strjoin(swap, quote);
	j = ft_strlen(temp);
	free(swap);
	free(quote);
	swap = temp;
	temp = ft_strjoin(swap, temp_2);
	free(swap);
	free(temp_2);
	swap = (*tkn)->tokens[i];
	(*tkn)->tokens[i] = ft_strdup(temp);
	free(swap);
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
				j = prepare_quote(&tkn, &tkn->tokens[i], j, i);
			if (tkn->tokens[i][j] == '\'')
				j = s_quoted(&tkn->tokens[i], j);
			j++;
		}
		i++;
	}
}
