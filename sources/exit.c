/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:19:26 by fagiusep          #+#    #+#             */
/*   Updated: 2022/02/11 13:01:19 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(t_cmd *cmd, size_t i)
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

void	exit_shell(t_cmd *cmd)
{
	int	x;
	int	y;

	x = 0;
	if (cmd->tab_x != NULL)
	{
		while (x < cmd->x_tab)
		{
			y = 0;
			while (y < cmd->y_tab && cmd->tab_x[x][y])
			{
				free(cmd->tab_x[x][y]);
				cmd->tab_x[x][y] = NULL;
				y++;
			}
			x++;
		}
		free(cmd->tab_x);
		cmd->tab_x = NULL;
	}
}
