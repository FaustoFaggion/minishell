/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:01:42 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/04 16:26:25 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	check_built_in(t_tkn *tkn)
{
	if (ft_strncmp(tkn->cmd[tkn->i_cmd][0], "cd\0", 3) == 0)
	{
		built_in_cmd(tkn, tkn->i_cmd);
		return (0);
	}
	if (ft_strncmp(tkn->cmd[tkn->i_cmd][0], "export\0", 7) == 0)
	{
		built_in_cmd(tkn, tkn->i_cmd);
		return (0);
	}
	if (ft_strncmp(tkn->cmd[tkn->i_cmd][0], "unset\0", 7) == 0)
	{
		built_in_cmd(tkn, tkn->i_cmd);
		return (0);
	}
	if (ft_strncmp(tkn->cmd[tkn->i_cmd][0], "env\0", 4) == 0)
	{
		built_in_cmd(tkn, tkn->i_cmd);
		return (0);
	}
	if (ft_strncmp(tkn->cmd[tkn->i_cmd][0], "exit\0", 5) == 0)
	{
		built_in_cmd(tkn, tkn->i_cmd);
		return (0);
	}
	else if (ft_strncmp(tkn->cmd_lex[tkn->i_cmd][0], "ASSIGNMENT_WORD", 15) == 0)
	{
		built_in_cmd(tkn, tkn->i_cmd);
		return (0);
	}
	return (1);
}

static void	redirect_std_fileno(t_tkn *tkn, int fd[])
{
	char	*temp;
	int		flag;
	
	close(fd[0]);
	tkn->fd_out = 0;
	tkn->fd_in = 0;
	flag = 0;
	while (tkn->cmd_lex[tkn->i_cmd + 1] != NULL)
	{
		if (ft_strncmp(tkn->cmd_lex[tkn->i_cmd + 1][0], "DGREAT", 6) == 0)
		{
			if(tkn->fd_out != 0)
			close(tkn->fd_out);
			tkn->fd_out = open(tkn->cmd[tkn->i_cmd + 1][1], O_RDWR | O_APPEND
					| O_CREAT, 0777);
			flag = 1;
		}
		else if (ft_strncmp(tkn->cmd_lex[tkn->i_cmd + 1][0], "GREAT", 5) == 0)
		{
			printf("\n entrei >\n");
			if(tkn->fd_out != 0)
			close(tkn->fd_out);
			tkn->fd_out = open(tkn->cmd[tkn->i_cmd + 1][1], O_RDWR | O_TRUNC
					| O_CREAT, 0777);
			flag = 1;
		}
		else if (ft_strncmp(tkn->cmd_lex[tkn->i_cmd + 1][0], "LESS", 4) == 0)
		{
			if(tkn->fd_in != 0)
				close(tkn->fd_in);
			tkn->fd_in = open(tkn->cmd[tkn->i_cmd + 1][1], O_RDONLY);
			if (tkn->fd_in < 0)
			{
				printf("bash: %s: Arquivo ou diretório inexistente\n", tkn->cmd[tkn->i_cmd][1]);
				return ;
			}
			else
				dup2(tkn->fd_in, STDIN_FILENO);			
		}
		else if (ft_strncmp(tkn->cmd_lex[tkn->i_cmd + 1][0], "DLESS", 5) == 0)
		{
			exec_cmd_d_less(tkn, tkn->i_cmd + 1);
		}
		else
			break;
		tkn->i_cmd++;
	}
	if (flag == 1)
	{
		temp = ft_get_next_line(tkn->fd_out);
		if (tkn->fd_out < 0)
		{
			printf("bash: %s: Arquivo ou diretório inexistente\n", tkn->cmd[tkn->i_cmd][1]);
			return ;
		}
		else
			dup2(tkn->fd_out, STDOUT_FILENO);
		
	}
}

static void	define_std_fileno(t_tkn *tkn, int fd[], char **next_cmd)
{
	if (next_cmd != NULL)
	{
		if (ft_strncmp(next_cmd[0], "PIPE", 4) == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
		}
		else if (ft_strncmp(next_cmd[0], "DGREAT", 6) == 0
				|| ft_strncmp(next_cmd[0], "GREAT", 5) == 0
				|| ft_strncmp(next_cmd[0], "LESS", 4) == 0
				|| ft_strncmp(next_cmd[0], "DLESS", 5) == 0)
		{
			redirect_std_fileno(tkn, fd);
		}
		else
			printf("\nerro lógica if do redirect\n");
	}
}

static int	exec_child(t_tkn *tkn, int fd[], char **cmd, char **nex_cmd)
{
	int		i;
	
	handle_signal_child();
	i = tkn->i_cmd;
	close(fd[0]);
	define_std_fileno(tkn, fd, nex_cmd);
	close(fd[1]);
	if (built_in_cmd(tkn, i) == 1)
	{
		if (execve(tkn->path_0, cmd, tkn->envp) == -1)
		{
			write(2, "error execve\n", 13);
			exit(1);
		}
		exit_shell(tkn);
	}
	exit_shell(tkn);
	free_tab(&tkn->envp, tkn->envp_count);
	rl_clear_history();
	exit(0);
	return (0);
}

static int	is_redirect(t_tkn *tkn)
{
	if (ft_strncmp(tkn->cmd_lex[tkn->i_cmd][0], "DGREAT", 6) == 0
				|| (ft_strncmp(tkn->cmd_lex[tkn->i_cmd][0], "GREAT", 5) == 0))
		return (1);
	return (0);
}

void	exec_cmd_pipe(t_tkn *tkn)
{
	int	fd[2];
	int	pid;
	int	wstatus;

	if (check_built_in(tkn) == 1)
	{
		if (pipe(fd) == -1)
			exit(write(1, "pipe error\n", 11));
		if (cmd_setup(tkn, tkn->i_cmd) == 0)
		{
			pid = fork();
			if (pid < 0)
				exit(write(1, "fork error\n", 11));
			if (pid == 0)
				exec_child(tkn, fd, tkn->cmd_lex[tkn->i_cmd], tkn->cmd_lex[tkn->i_cmd + 1]);
			waitpid(pid, &wstatus, 0);
			if (!WIFSIGNALED(wstatus))
				global_exit = WEXITSTATUS(wstatus);
		}
		handle_signal_parent();
		close(fd[1]);
		if (tkn->cmd[tkn->i_cmd + 1] != NULL)
		{
			if (ft_strncmp(tkn->cmd_lex[tkn->i_cmd + 1][0], "PIPE", 4) == 0
					&& is_redirect(tkn) == 0)
			{
				dup2(fd[0], STDIN_FILENO);
			}
		}
		close(fd[0]);
	}
}
