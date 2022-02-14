/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_tab_malloc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:05:09 by fagiusep          #+#    #+#             */
/*   Updated: 2022/02/14 16:01:39 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	malloc_char(t_cmd *cmd)
{
	if (cmd->flag == 1)
	{
		cmd->y = 0;
		cmd->tab_y = (char **)malloc(((sizeof(char *)) * (cmd->size_tab_y + 1)));
		if (!cmd->tab_y)
			return ;
	}
	cmd->len_ptr = 0;
	cmd->len_ptr = parse_cmd_tab_len(cmd, cmd->z);
	cmd->tab_y[cmd->y] = ft_substr(cmd->line, cmd->z, cmd->len_ptr);
	if (cmd->tab_y[cmd->y] == NULL)
		free_tab(cmd->tab_y, cmd->size_tab_y);
	cmd->z = cmd->z + cmd->len_ptr;
	cmd->y++;
	cmd->flag = 0;
}

static void	close_malloc(t_cmd *cmd)
{
	while (cmd->y < cmd->size_tab_y)
		{
			cmd->tab_y[cmd->y] = NULL;
			cmd->y++;
		}
		cmd->tab_x[cmd->x] = cmd->tab_y;
		cmd->x++;
}
static void	malloc_metachar(t_cmd *cmd)
{
	if (cmd->flag == 0)
		close_malloc(cmd);
	cmd->tab_y = (char **)malloc(((sizeof(char *)) * (cmd->size_tab_y + 1)));
	if (cmd->tab_y == NULL)
		free_tab(cmd->tab_y, cmd->size_tab_y);
	cmd->y = 0;
	parse_cmd_tab_len(cmd, cmd->z);
	cmd->tab_y[cmd->y] = ft_substr(cmd->line, cmd->z, cmd->len_ptr);
	if (cmd->tab_y[cmd->y] == NULL)
		free_tab(cmd->tab_y, cmd->size_tab_y);
	cmd->y++;
	close_malloc(cmd);
	cmd->z = cmd->z + cmd->len_ptr;
	cmd->flag = 1;
}

static void	malloc_finish(t_cmd *cmd)
{
	if (cmd->flag == 0)
	{
		while (cmd->y < cmd->size_tab_y)
		{
			cmd->tab_y[cmd->y] = NULL;
			cmd->y++;
		}
		cmd->tab_x[cmd->x] = cmd->tab_y;
		cmd->tab_x[cmd->x + 1] = NULL;
	}
	else
		cmd->tab_x[cmd->x] = NULL;
}

char	**parse_cmd_tab_malloc(t_cmd *cmd)
{
	cmd->x = 0;
	cmd->y = 0;
	cmd->z = 0;
	cmd->flag = 1;
	cmd->len_ptr = 0;
	while (cmd->line[cmd->z] != '\0')
	{
		while (cmd->line[cmd->z] == ' ' && cmd->line[cmd->z] != '\0')
			cmd->z++;
//		grammar_rules(cmd, cmd->z);
		if (ft_strchr("|<>", cmd->line[cmd->z]) == NULL)
			malloc_char(cmd);
		else
		{
			malloc_metachar(cmd);
			if (!cmd->tab_x)
				break ;
		}
	}
	if (cmd->line[cmd->z] == '\0')
		malloc_finish(cmd);
	return (cmd->tab_y);
}
