/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:17:11 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/21 16:22:45 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_not_found(t_tkn *tkn, int i)
{
	write(1, tkn->cmd[i][0], ft_strlen(tkn->cmd[i][0]));
	write(1, ": Command not found\n", 20);
}

int	cmd_setup(t_tkn *tkn, int i)
{
	int		x;
	char	*temp;

	x = 0;
	while (tkn->path[x])
	{
		tkn->path_0 = ft_strjoin(tkn->path[x], "/");
		if (tkn->path_0 == NULL)
			exit(1);
		temp = tkn->path_0;
		tkn->path_0 = ft_strjoin(temp, tkn->cmd[i][0]);
		free(temp);
		if (tkn->path_0 == NULL)
			exit(1);
		if (access(tkn->path_0, F_OK) == 0)
			return (0);
		free(tkn->path_0);
		tkn->path_0 = NULL;
		x++;
	}
	cmd_not_found(tkn, i);
	return (1);
}

int	built_in_cmd(t_tkn *tkn, int i)
{
	if (ft_strncmp(tkn->cmd[i][0], "echo", 4) == 0)
	{
		exec_cmd_echo(tkn, i);
		return (0);
	}
	return (1);
}

void	exec_cmd_tab(t_tkn *tkn)
{
	int	i;

	i = 0;
	while (tkn->cmd[i] != NULL)
	{
		if (ft_strncmp(tkn->cmd_lex[i][0], "WORD", 4) == 0
			|| ft_strncmp(tkn->cmd_lex[i][0], "ASSIGNMENT_WORD", 15) == 0)
		{
			if (tkn->cmd[i + 1] == NULL)
					exec_simple_cmd(tkn, i);
			else if (ft_strncmp(tkn->cmd_lex[i + 1][0], "PIPE", 4) == 0)
			{
				exec_cmd_pipe(tkn, i);
				i++;
			}
			else if (ft_strncmp(tkn->cmd_lex[i + 1][0], "GREAT", 5) == 0
				|| ft_strncmp(tkn->cmd_lex[i + 1][0], "DGREAT", 6) == 0)
			{
				exec_cmd_d_great(tkn, i);
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
