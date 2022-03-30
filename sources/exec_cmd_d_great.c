/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_d_great.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:16:28 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/30 10:15:01 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd(t_tkn *tkn, int i)
{
	if (built_in_cmd(tkn, i) == 1)
	{
		if (execve(tkn->path_0, tkn->cmd[i], NULL) == -1)
		{
			write(2, "error execve\n", 13);
			exit(1);
		}
		exit_shell(tkn);
	}
	exit_shell(tkn);
	free_tab(&tkn->envp, tkn->envp_count);
	rl_clear_history();
}

static int	exec_child_(t_tkn *tkn, int fd[], int i)
{
	int	y;
	char	*temp;
	
	y = 0;
	close(fd[0]);
	while (tkn->cmd_lex[i + y + 1] != NULL)
	{
	//	if(tkn->fd != 0)
	//		close(tkn->fd);
		if (ft_strncmp(tkn->cmd_lex[i + y + 1][0], "DGREAT", 6) == 0)
			tkn->fd = open(tkn->cmd[i + y + 1][1], O_RDWR | O_APPEND
					| O_CREAT, 0777);
		else if (ft_strncmp(tkn->cmd_lex[i + y + 1][0], "GREAT", 5) == 0)
			tkn->fd = open(tkn->cmd[i + y + 1][1], O_RDWR | O_TRUNC
					| O_CREAT, 0777);
		else
			break;
		y++;
	}
	temp = ft_get_next_line(tkn->fd);
	if (tkn->fd < 0)
	{
		printf("bash: %s: Arquivo ou diretório inexistente\n", tkn->cmd[i][1]);
		return (1);
	}
	else
		dup2(tkn->fd, STDOUT_FILENO);
	close(fd[1]);
	exec_cmd(tkn, i);
	exit(0);
	return (0);
}

void	exec_cmd_d_great(t_tkn *tkn, int i)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		exit(write(1, "pipe error\n", 11));
	if (cmd_setup(tkn, i) == 0)
	{
		pid = fork();
		if (pid < 0)
			exit(write(1, "fork error\n", 11));
		if (pid == 0)
			exec_child_(tkn, fd, i);
		waitpid(pid, NULL, 0);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}
