/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:17:11 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/08 13:29:35 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_not_found(t_tkn *tkn, int i)
{
	write(1, tkn->cmd[i][0], ft_strlen(tkn->cmd[i][0]));
	write(1, ": Command not found\n", 20);
}

static char	**get_env(char **temp, char ***swap)
{
	char	**path;

	*temp = getenv("PATH");
	*swap = ft_split(*temp, ':');
	path = *swap;
	return (path);
}

int	cmd_setup(t_tkn *tkn, int i)
{
	int		x;
	char	**swap;
	char	**path;
	char	*temp;

	path = get_env(&temp, &swap);
	x = -1;
	while (path[++x])
	{
		tkn->path = ft_strjoin(path[x], "/");
		if (tkn->path == NULL)
			exit(1);
		temp = tkn->path;
		tkn->path = ft_strjoin(temp, tkn->cmd[i][0]);
		free(temp);
		if (tkn->path == NULL)
			exit(1);
		if (access(tkn->path, F_OK) == 0)
			return (0);
		free(tkn->path);
		tkn->path = NULL;
	}
	cmd_not_found(tkn, i);
	return (1);
}

void	exec_cmd_tab(t_tkn *tkn)
{
	int	i;

	i = 0;
	while (tkn->cmd[i] != NULL)
	{
		if (ft_strncmp(tkn->cmd_lex[i][0], "WORD", 4) == 0
			|| ft_strncmp(tkn->cmd_lex[i][0], "ASSIGNMENT_WORD", 4) == 0)
		{
			if (tkn->cmd[i + 1] == NULL)
				exec_simple_cmd(tkn, i);
			else //if (ft_strncmp(tkn->cmd[i + 1][0], "|", 1) == 0)
			{
				exec_cmd_pipe(tkn, i);
				i++;
			}
			i++;
		}
		else
		{
			exec_cmd_redirect(tkn, i);
			i++;
		}
	}
	dup2(1, STDIN_FILENO);
}
