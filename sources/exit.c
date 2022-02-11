/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:19:26 by fagiusep          #+#    #+#             */
/*   Updated: 2022/02/11 11:19:27 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
