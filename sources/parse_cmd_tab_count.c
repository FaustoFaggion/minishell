/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_tab_count.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:15:03 by fagiusep          #+#    #+#             */
/*   Updated: 2022/02/11 11:33:26 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_matechar(t_cmd *cmd, int i)
{
	i = metachar_check(cmd, i);
	cmd->x_tab++;
	cmd->count_y = 1;
	if (cmd->count_y > cmd->y_tab)
		cmd->y_tab = cmd->count_y;
	cmd->count_y = 0;
	cmd->flag = 1;
	return (i);
}

static int	count_quotes(t_cmd *cmd, int i)
{
	i = quotes_check(cmd, i, cmd->line[i]);
	if (i == -1)
	{
		write(2, "ERROR\nUnclosed quote.\n", 21);
		exit(1);
	}
	cmd->count_y++;
	if (cmd->count_y > cmd->y_tab)
		cmd->y_tab = cmd->count_y;
	if (cmd->flag == 1)
	{
		cmd->x_tab++;
		cmd->flag = 0;
	}
	return (i);
}

static int	count_char(t_cmd *cmd, int i)
{
	while (ft_strchr("|<> ", cmd->line[i]) == NULL)
		i++;
	cmd->count_y++;
	if (cmd->count_y > cmd->y_tab)
		cmd->y_tab = cmd->count_y;
	if (cmd->flag == 1)
	{
		cmd->x_tab++;
		cmd->flag = 0;
	}
	return (i);
}

void	parse_cmd_tab_count(t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->count_y = 0;
	cmd->flag = 1;
	cmd->x_tab = 0;
	cmd->y_tab = 0;
	while (cmd->line[i] != '\0')
	{
		while (cmd->line[i] == ' ' && cmd->line[i] != '\0')
			i++;
		if (ft_strchr("|<>", cmd->line[i]) != NULL)
			i = count_matechar(cmd, i);
		else if (ft_strchr("\'\"", cmd->line[i]) != NULL)
			i = count_quotes(cmd, i);
		else
			i = count_char(cmd, i);
	}
	cmd->y_tab++;
}
