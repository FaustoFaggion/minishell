/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:51:10 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/07 14:51:11 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_metachar(t_tkn *tkn, int i)
{
	int		count;
	int		j;
	char	**temp;

	count = 0;
	while (ft_strncmp(tkn->lexemas[i + count], "WORD", 4) != 0
		&& ft_strncmp(tkn->lexemas[i + count], "ASSIGNMENT_WORD", 15) != 0)
		count++;
	temp = (char **) malloc(sizeof(char *) * (count + 1));
	j = 0;
	while (count > 0)
	{
		temp[j] = tkn->tokens[i];
		j++;
		i++;
		count--;
	}
	temp[j] = NULL;
	tkn->cmd[tkn->cmd_count] = temp;
	tkn->cmd_count++;
	temp = NULL;
	return (i);
}

static int	cmd_word(t_tkn *tkn, int i)
{
	int		count;
	int		j;
	char	**temp;

	count = 0;
	while (ft_strncmp(tkn->lexemas[i + count], "WORD", 4) == 0
		|| ft_strncmp(tkn->lexemas[i + count], "ASSIGNMENT_WORD", 15) == 0)
	{
		count++;
		if (tkn->lexemas[i + count] == NULL)
			break ;
	}
	temp = (char **) malloc(sizeof(char *) * (count + 1));
	j = 0;
	while (count > 0)
	{
		temp[j] = tkn->tokens[i];
		j++;
		i++;
		count--;
	}
	temp[j] = NULL;
	tkn->cmd[tkn->cmd_count] = temp;
	tkn->cmd_count++;
	return (i);
}

void	cmd_tab(t_tkn *tkn)
{
	int		i;
	int		count;

	tkn->cmd_count = 0;
	count = 0;
	i = -1;
	while (++i < tkn->tkn_count)
	{
		if (ft_strncmp(tkn->lexemas[i], "WORD", 4) != 0
			&& ft_strncmp(tkn->lexemas[i], "ASSIGNMENT_WORD", 15) != 0)
			count = count + 3;
		count++;
	}
	tkn->cmd = (char ***)malloc((sizeof(char **) * sizeof(tkn->tokens) * 2)
			+ (sizeof(char **) * 2));
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
