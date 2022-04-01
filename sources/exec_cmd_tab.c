/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:17:11 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/01 18:24:24 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_not_found(t_tkn *tkn, int i)
{
	write(1, tkn->cmd[i][0], ft_strlen(tkn->cmd[i][0]));
	write(1, ": Command not found\n", 20);
	global_exit = 127;
}

int	cmd_setup(t_tkn *tkn, int i)
{
	int		x;
	char	*temp;

	x = 0;
	if (tkn->path_0 != NULL)
		free(tkn->path_0);
	if (tkn->path != NULL)
	{
		while (tkn->path[x] != NULL)
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
	}
	cmd_not_found(tkn, i);
	return (1);
}

void	exec_cmd_tab(t_tkn *tkn)
{
	tkn->i_cmd = 0;
	while (tkn->cmd[tkn->i_cmd] != NULL)
	{
		if (ft_strncmp(tkn->cmd_lex[tkn->i_cmd][0], "WORD", 4) == 0
			|| ft_strncmp(tkn->cmd_lex[tkn->i_cmd][0], "ASSIGNMENT_WORD", 15) == 0)
		{
			if (tkn->cmd[tkn->i_cmd + 1] == NULL)
			{
				exec_cmd_pipe(tkn);	
			}
			else if (ft_strncmp(tkn->cmd_lex[tkn->i_cmd + 1][0], "PIPE", 4) == 0)
			{
				exec_cmd_pipe(tkn);
				tkn->i_cmd++;
			}
			else if (ft_strncmp(tkn->cmd_lex[tkn->i_cmd + 1][0], "GREAT", 5) == 0
				|| ft_strncmp(tkn->cmd_lex[tkn->i_cmd + 1][0], "DGREAT", 6) == 0)
			{
				exec_cmd_pipe(tkn);
				tkn->i_cmd++;
			}
			tkn->i_cmd++;
		}
		else
		{
			exec_cmd_d_less(tkn, tkn->i_cmd);
			tkn->i_cmd++;
		}
	}
	dup2(1, STDIN_FILENO);
}
