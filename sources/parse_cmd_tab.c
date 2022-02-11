/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 20:40:17 by fagiusep          #+#    #+#             */
/*   Updated: 2022/02/11 11:36:32 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_tab(t_cmd *cmd, size_t i)
{
	if (cmd->tab_y != NULL)
	{
		while (((int)i - 1) > 0)
		{
			free(cmd->tab_y[i]);
			cmd->tab_y[i] = NULL;
			i--;
		}
		free(cmd->tab_y);
		cmd->tab_y = NULL;
	}
}

static char	**parse_malloc(t_cmd *cmd)
{
	int	len_ptr;
	int	x;
	int	y;
	int	z;
	int	flag;

	x = 0;
	y = 0;
	z = 0;
	flag = 1;
	cmd->tab_y = (char **)malloc(((sizeof(char *)) * (cmd->y_tab + 1)));
	if (!cmd->tab_x)
		return (NULL);
	while (cmd->line[z] != '\0')
	{
		while (cmd->line[z] == ' ' && cmd->line[z] != '\0')
			z++;
		if (ft_strchr("|<>", cmd->line[z]) == NULL)
		{
			len_ptr = parse_cmd_tab_len(cmd, z);
			cmd->tab_y[y] = ft_substr(cmd->line, z, len_ptr);
			if (cmd->tab_y[y] == NULL)
				free_tab(cmd, cmd->y_tab);
			printf ("tab_y %s\n", cmd->tab_y[y]);
			z = z + len_ptr;
			y++;
			flag = 0;
		}
		else
		{
			if (flag == 0)
			{
				while (y < cmd->y_tab)
				{
					cmd->tab_y[y] = NULL;
					y++;
				}
				cmd->tab_x[x] = cmd->tab_y;
				cmd->tab_y = (char **)malloc(((sizeof(char *)) * (cmd->y_tab + 1)));
				x++;
				y = 0;
			}
			len_ptr = parse_cmd_tab_len(cmd, z);
			cmd->tab_y[y] = ft_substr(cmd->line, z, len_ptr);
			if (cmd->tab_y[y] == NULL)
				free_tab(cmd, cmd->y_tab);
			z = z + len_ptr;
			y++;
			while (y < cmd->y_tab)
			{
				cmd->tab_y[y] = NULL;
				y++;
			}
			cmd->tab_x[x] = cmd->tab_y;
			cmd->tab_y = (char **)malloc(((sizeof(char *)) * (cmd->y_tab + 1)));
			if (cmd->line[z] == '\0')
			{
				free(cmd->tab_y);
				cmd->tab_y = NULL;
			}
			if (!cmd->tab_x)
				break ;
			x++;
			y = 0;
			flag = 1;
		}
	}
	if (cmd->line[z] == '\0')
	{
		if (cmd->tab_y != NULL)
		{
			while (y < cmd->y_tab)
			{
				cmd->tab_y[y] = NULL;
				y++;
			}
			cmd->tab_x[x] = cmd->tab_y;
			cmd->tab_x[x + 1] = NULL;
		}
		else
		{
			free(cmd->tab_y);
			cmd->tab_x[x] = NULL;
		}
	}
	return (cmd->tab_y);
}

char	***parse_cmd_tab(t_cmd *cmd)
{
	if (!cmd->line)
		return (NULL);
	parse_cmd_tab_count(cmd);
	cmd->tab_x = (char ***)malloc(((sizeof(char *)) * (cmd->x_tab + 1)));
	if (!cmd->tab_x)
		return (NULL);
	parse_malloc(cmd);
	return (cmd->tab_x);
}
