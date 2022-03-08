/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_analysis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:10:30 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/08 08:36:16 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	metachar_check(t_tkn *tkn, int i)
{
	if (tkn->line[i] == '|')
		i++;
	else if (tkn->line[i] == '<')
	{
		i++;
		if (tkn->line[i] == '<')
			i++;
	}
	else if (tkn->line[i] == '>')
	{
		i++;
		if (tkn->line[i] == '>')
			i++;
	}
	return (i);
}

static int	quotes_check(t_tkn *tkn, int i, char c)
{
	i++;
	printf("....%c", tkn->line[i]);
	while (tkn->line[i] != c)
	{
		if (tkn->line[i] == '\0')
		{
			exit_shell_quote(tkn, tkn->tkn_count);
			exit(1);
		}
		i++;
	}	
	i++;
	printf("....%c\n", tkn->line[i]);
	return (i);
}

void	token_count(t_tkn *tkn)
{
	int	i;

	i = 0;
	tkn->tkn_count = 0;
	while (tkn->line[i] != '\0')
	{
		while (tkn->line[i] == ' ' && tkn->line[i] != '\0')
			i++;
		if (ft_strchr("|<>", tkn->line[i]) != NULL)
			i = metachar_check(tkn, i);
		else if (ft_strchr("\'\"", tkn->line[i]) != NULL)
			i = quotes_check(tkn, i, tkn->line[i]);
		else
		{
			while (ft_strchr("|<> ", tkn->line[i]) == NULL)
			{
				if (tkn->line[i] == '\'')
					i = quotes_check(tkn, i, tkn->line[i]);
				else if (tkn->line[i] == '\"')
					i = quotes_check(tkn, i, tkn->line[i]);
				else
					i++;
			}
		}
		tkn->tkn_count++;
	}
}

static void	scan_cmd_line(t_tkn *tkn)
{
	int	i;
	int	x;
	int	start;

	i = 0;
	x = 0;
	while (tkn->line[i] != '\0')
	{
		while (tkn->line[i] == ' ' && tkn->line[i] != '\0')
			i++;
		start = i;
		if (ft_strchr("|<>", tkn->line[i]) != NULL)
			i = metachar_check(tkn, i);
		else if (ft_strchr("\'\"", tkn->line[i]) != NULL)
			i = quotes_check(tkn, i, tkn->line[i]);
		else
		{
			while (ft_strchr("|<> ", tkn->line[i]) == NULL)
			{
				if (tkn->line[i] == '\'')
					i = quotes_check(tkn, i, tkn->line[i]);
				else if (tkn->line[i] == '\"')
					i = quotes_check(tkn, i, tkn->line[i]);
				else
					i++;
			}
		}
		tkn->len = i - start;
		tkn->tokens[x] = ft_substr(tkn->line, start, tkn->len);
		x++;
	}
	tkn->tokens[x] = NULL;
}

void	token_analysis(t_tkn *tkn)
{
	token_count(tkn);
	tkn->tokens = (char **) malloc(sizeof(char *) * (tkn->tkn_count + 1));
	if (!tkn->tokens)
		return ;
	scan_cmd_line(tkn);
	return ;
}
