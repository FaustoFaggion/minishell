/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:19:26 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/26 14:49:09 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char ***tab, int i)
{
	int	x;

	x = 0;
	if (*tab != NULL)
	{
		while (x < i)
		{
			free((*tab)[x]);
			x++;
		}
		free((*tab)[x]);
		free(*tab);
		*tab = NULL;
	}
}

void	exit_shell(t_tkn *tkn)
{
	int	x;
	int	y;

	x = 0;
	if (tkn->cmd != NULL)
	{
		while (x < tkn->cmd_count)
		{
			y = 0;
			while ( tkn->cmd[x][y] != NULL)
			{
				free(tkn->cmd[x][y]);
				free(tkn->cmd_lex[x][y]);
				y++;
			}
			free(tkn->cmd[x]);
			free(tkn->cmd_lex[x]);
			x++;
		}
		free(tkn->cmd);
		tkn->cmd = NULL;
		free(tkn->cmd_lex);
		tkn->cmd_lex = NULL;
	}

	if (tkn->tokens != NULL)
		free_tab(&tkn->tokens, tkn->tkn_count);
	if (tkn->lexemas != NULL)
		free_tab(&tkn->lexemas, tkn->tkn_count);
	if (tkn->line != NULL)
		free(tkn->line);
	if (tkn->path_0 != NULL)
		free(tkn->path_0);
	free_tab(&tkn->path, tkn->path_count);
}

void	exit_shell_quote(t_tkn *tkn, int i)
{
	int	x;

	x = 0;
	if (tkn->tokens != NULL)
	{
		while (x < i)
		{
			free(tkn->tokens[x]);
			x++;
		}
		free(tkn->tokens);
	}
	x = 0;
	if (tkn->lexemas != NULL)
	{
		while (x < tkn->tkn_count)
		{
			free(tkn->lexemas[x]);
			x++;
		}
		free(tkn->lexemas);
	}
	if (tkn->line != NULL)
		free(tkn->line);
	x = 0;
	if (tkn->path != NULL)
	{
		while (x < tkn->path_count)
		{
			free(tkn->path[x]);
			x++;
		}
		free(tkn->path);
		tkn->path = NULL;
	}
}
