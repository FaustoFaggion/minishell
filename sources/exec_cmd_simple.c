/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:17:33 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/22 17:04:24 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_child(t_tkn *tkn, int i)
{
	if (built_in_cmd(tkn, i) == 1)
	{
		if (execve(tkn->path_0, tkn->cmd[i], tkn->envp) == -1)
		{
			write(2, "error execve\n", 13);
			exit(1);
		}
		exit_shell(tkn);
	}
	exit_shell(tkn);
	exit(0);
	return (0);
}

void	exec_simple_cmd(t_tkn *tkn, int i)
{
	int	pid;

	if (ft_strncmp(tkn->cmd[i][0], "cd", 2) == 0)
	{
		built_in_cmd(tkn, i);
			return ;
	}
	if (cmd_setup(tkn, i) == 0)
	{
		pid = fork();
		if (pid < 0)
			exit(write(1, "fork error\n", 11));
		if (pid == 0)
			exec_child(tkn, i);
		waitpid(pid, NULL, 0);
	}
}
