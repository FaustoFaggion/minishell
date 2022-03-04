/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_tab_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:09:33 by fagiusep          #+#    #+#             */
/*   Updated: 2022/02/11 13:09:34 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	metachar_check(t_cmd *cmd, int i)
{
	if (cmd->line[i] == '|')
		i++;
	else if (cmd->line[i] == '<')
	{
		i++;
		if (cmd->line[i] == '<')
			i++;
	}
	else if (cmd->line[i] == '>')
	{
		i++;
		if (cmd->line[i] == '>')
			i++;
	}
	return (i);
}

int	quotes_check(t_cmd *cmd, int i, char c)
{
	i++;
	while (cmd->line[i] != c)
	{
		if (cmd->line[i] == '\0')
		{
			exit_shell(cmd);
			exit(1);
		}
		i++;
	}	
	i++;
	return (i);
}

int	parse_cmd_tab_len(t_cmd *cmd, int i)
{
	cmd->len_ptr = 0;
	if (ft_strchr("|<>", cmd->line[i]) != NULL)
	{
		cmd->len_ptr = i;
		i = metachar_check(cmd, i);
		cmd->len_ptr = i - cmd->len_ptr;
	}
	else if (ft_strchr("\'\"", cmd->line[i]) != NULL)
	{
		cmd->len_ptr = i;
		i = quotes_check(cmd, i, cmd->line[i]);
		cmd->len_ptr = (i - cmd->len_ptr);
	}
	else
	{
		while (ft_strchr("|<> ", cmd->line[i + cmd->len_ptr]) == NULL
			&& cmd->line[i + cmd->len_ptr] != '\0')
			cmd->len_ptr++;
	}
	return (cmd->len_ptr);
}
