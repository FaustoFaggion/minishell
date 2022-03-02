/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:19:26 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/01 16:18:29 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab, size_t i)
{
	if (tab != NULL)
	{
		while (((int)i - 1) > 0)
		{
			free(tab[i]);
			tab[i] = NULL;
			i--;
		}
		free(tab);
		tab = NULL;
	}
}

void	exit_shell(t_tkn *tkn)
{
	int	x;

	x = 0;
/*	if (cmd->tab_x != NULL)
	{
		while (x < cmd->size_tab_x)
		{
			y = 0;
			while (y < cmd->size_tab_y && cmd->tab_x[x][y])
			{
				free(cmd->tab_x[x][y]);
				cmd->tab_x[x][y] = NULL;
				y++;
			}
			free(cmd->tab_x[x]);
			x++;
		}
		free(cmd->tab_x);
		cmd->tab_x = NULL;
	}
*/
	x = 0;
	if (tkn->tokens[x] != NULL)
	{
		while (tkn->tokens[x])
		{
			free(tkn->tokens[x]);
			free(tkn->lexemas[x]);

			x++;
		}
	}
	free(tkn->tokens);
	free(tkn->lexemas);
}
