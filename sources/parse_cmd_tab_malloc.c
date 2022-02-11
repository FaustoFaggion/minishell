/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_tab_malloc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:05:09 by fagiusep          #+#    #+#             */
/*   Updated: 2022/02/11 13:07:41 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	malloc_char(t_cmd *cmd)
{
	cmd->len_ptr = 0;
	cmd->len_ptr = parse_cmd_tab_len(cmd, cmd->z);
	cmd->tab_y[cmd->y] = ft_substr(cmd->line, cmd->z, cmd->len_ptr);
	if (cmd->tab_y[cmd->y] == NULL)
		free_tab(cmd, cmd->y_tab);
	printf ("tab_y %s\n", cmd->tab_y[cmd->y]);
	cmd->z = cmd->z + cmd->len_ptr;
	cmd->y++;
	cmd->flag = 0;
}

static void	malloc_metachar(t_cmd *cmd)
{
	if (cmd->flag == 0)
	{
		while (cmd->y < cmd->y_tab)
		{
			cmd->tab_y[cmd->y] = NULL;
			cmd->y++;
		}
		cmd->tab_x[cmd->x] = cmd->tab_y;
		cmd->tab_y = (char **)malloc(((sizeof(char *)) * (cmd->y_tab + 1)));
		cmd->x++;
		cmd->y = 0;
	}
	parse_cmd_tab_len(cmd, cmd->z);
	cmd->tab_y[cmd->y] = ft_substr(cmd->line, cmd->z, cmd->len_ptr);
	if (cmd->tab_y[cmd->y] == NULL)
		free_tab(cmd, cmd->y_tab);
	cmd->y++;
	while (cmd->y < cmd->y_tab)
	{
		cmd->tab_y[cmd->y] = NULL;
		cmd->y++;
	}
	cmd->tab_x[cmd->x] = cmd->tab_y;
}

static void	malloc_prepare_next(t_cmd *cmd)
{
	cmd->z = cmd->z + cmd->len_ptr;
	cmd->tab_y = (char **)malloc(((sizeof(char *)) * (cmd->y_tab + 1)));
	if (cmd->line[cmd->z] == '\0')
	{
		free(cmd->tab_y);
		cmd->tab_y = NULL;
	}
	cmd->y = 0;
	cmd->flag = 1;
	cmd->x++;
}

static void	malloc_finish(t_cmd *cmd)
{
	if (cmd->tab_y != NULL)
	{
		while (cmd->y < cmd->y_tab)
		{
			cmd->tab_y[cmd->y] = NULL;
			cmd->y++;
		}
		cmd->tab_x[cmd->x] = cmd->tab_y;
		cmd->tab_x[cmd->x + 1] = NULL;
	}
	else
	{
		free(cmd->tab_y);
		cmd->tab_x[cmd->x] = NULL;
	}
}

char	**parse_cmd_tab_malloc(t_cmd *cmd)
{
	cmd->x = 0;
	cmd->y = 0;
	cmd->z = 0;
	cmd->flag = 1;
	cmd->len_ptr = 0;
	cmd->tab_y = (char **)malloc(((sizeof(char *)) * (cmd->y_tab + 1)));
	if (!cmd->tab_x)
		return (NULL);
	while (cmd->line[cmd->z] != '\0')
	{
		while (cmd->line[cmd->z] == ' ' && cmd->line[cmd->z] != '\0')
			cmd->z++;
		if (ft_strchr("|<>", cmd->line[cmd->z]) == NULL)
			malloc_char(cmd);
		else
		{
			malloc_metachar(cmd);
			malloc_prepare_next(cmd);
			if (!cmd->tab_x)
				break ;
		}
	}
	if (cmd->line[cmd->z] == '\0')
		malloc_finish(cmd);
	return (cmd->tab_y);
}
