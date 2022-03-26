/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:51:10 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/26 17:06:24 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_count(t_tkn *tkn, int i)
{
	int	count;

	count = 0;
	if (ft_strncmp(tkn->lexemas[i], "PIPE", 4) == 0)
		count = 1;
	if (ft_strncmp(tkn->lexemas[i], "LESS", 4) == 0
		|| ft_strncmp(tkn->lexemas[i], "DLESS", 5) == 0
		|| ft_strncmp(tkn->lexemas[i], "GREAT", 5) == 0
		|| ft_strncmp(tkn->lexemas[i], "DGREAT", 6) == 0)
		count = 2;
	return (count);
}

static int	cmd_metachar(t_tkn *tkn, int i)
{
	int		count;
	int		j;
	char	**temp;
	char	**temp_lex;

	count = cmd_count(tkn, i);
	temp = (char **) malloc(sizeof(char *) * (count + 1));
	temp_lex = (char **) malloc(sizeof(char *) * (count + 1));
	j = 0;
	while (count > 0)
	{
		temp[j] = ft_strdup(tkn->tokens[i]);
		temp_lex[j] = ft_strdup(tkn->lexemas[i]);
		j++;
		i++;
		count--;
	}
	temp[j] = NULL;
	temp_lex[j] = NULL;
	tkn->cmd[tkn->cmd_count] = temp;
	tkn->cmd_lex[tkn->cmd_count] = temp_lex;
	tkn->cmd_count++;
	return (i);
}

static int	count_word(t_tkn *tkn, int i)
{
	int	count;

	count = 0;
	while (ft_strncmp(tkn->lexemas[i + count], "WORD", 4) == 0
		|| ft_strncmp(tkn->lexemas[i + count], "ASSIGNMENT_WORD", 15) == 0)
	{
		count++;
		if (tkn->lexemas[i + count] == NULL)
			break ;
	}
	return (count);
}

static void	utils_word(t_tkn *tkn, char ***temp, char ***temp_lex)
{
	tkn->cmd[tkn->cmd_count] = *temp;
	tkn->cmd_lex[tkn->cmd_count] = *temp_lex;
	tkn->cmd_count++;
}

static int	cmd_word(t_tkn *tkn, int i)
{
	int		count;
	int		j;
	char	**temp;
	char	**temp_lex;

	count = count_word(tkn, i);
	temp = (char **) malloc(sizeof(char *) * (count + 1));
	if (temp == NULL)
		return (1);
	temp_lex = (char **) malloc(sizeof(char *) * (count + 1));
	if (temp_lex == NULL)
		return (1);
	j = 0;
	while (count > 0)
	{
		temp[j] = ft_strdup(tkn->tokens[i]);
		temp_lex[j] = ft_strdup(tkn->lexemas[i]);
		j++;
		i++;
		count--;
	}
	temp[j] = NULL;
	temp_lex[j] = NULL;
	utils_word(tkn, &temp, &temp_lex);
	return (i);
}

static int	count_tab(t_tkn *tkn)
{
	int	i;
	int	count;
	int	pipe;
	int	redirect;

	count = 0;
	pipe = 0;
	redirect = 0;
	i = -1;
	while (++i < tkn->tkn_count)
	{
		if (ft_strncmp(tkn->lexemas[i], "PIPE", 4) == 0)
			pipe++;
		else if (ft_strncmp(tkn->lexemas[i], "WORD", 4) != 0
			&& ft_strncmp(tkn->lexemas[i], "ASSIGNMENT_WORD", 15) != 0)
			redirect++;
	}
	count = (pipe +(pipe + 1)) + redirect;
	return (count);
}

void	cmd_tab(t_tkn *tkn)
{
	int	i;
	int	count;

	tkn->cmd_count = 0;
	count = count_tab(tkn);
	tkn->cmd = (char ***)malloc(((tkn->tkn_count * sizeof(char *))
				+ (count * sizeof(char *))) + 1);
	if (!tkn->cmd)
		return ;
	tkn->cmd_lex = (char ***)malloc(((tkn->tkn_count * sizeof(char *))
				+ (count * sizeof(char *))) + 1);
	if (!tkn->cmd)
		return ;
	i = 0;
	while (i < tkn->tkn_count)
	{
		if (ft_strncmp(tkn->lexemas[i], "WORD", 4) != 0
			&& ft_strncmp(tkn->lexemas[i], "ASSIGNMENT_WORD", 15) != 0)
			i = cmd_metachar(tkn, i);
		else
			i = cmd_word(tkn, i);
	}
	tkn->cmd[tkn->cmd_count] = NULL;
}
