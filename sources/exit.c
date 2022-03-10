/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:19:26 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/10 10:51:46 by fagiusep         ###   ########.fr       */
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
			free((*tab)[i]);
			i--;
		}
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
		free(tkn->tokens);
	if (tkn->lexemas != NULL)
		free(tkn->lexemas);
	if (tkn->line != NULL)
		free(tkn->line);
	if (tkn->path != NULL)
		free(tkn->path);
	x = 0;
	if (tkn->envp != NULL)
	{
		while (x < tkn->envp_count)
		{
			free(tkn->envp[x]);
			x++;
		}
		free(tkn->envp);
		tkn->envp = NULL;
	}
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
	if (tkn->envp != NULL)
	{
		while (x < tkn->envp_count)
		{
			free(tkn->envp[x]);
			x++;
		}
		free(tkn->envp);
		tkn->envp = NULL;
	}
}
