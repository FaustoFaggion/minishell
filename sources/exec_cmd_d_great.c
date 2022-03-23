#include "minishell.h"

static int	exec_child_(t_tkn *tkn, int fd[], int i)
{
	close(fd[0]);
	if (ft_strncmp(tkn->cmd_lex[i + 1][1], "WORD", 4) == 0)
	{
		if (ft_strncmp(tkn->cmd_lex[i + 1][0], "DGREAT", 6) == 0)
			tkn->fd = open(tkn->cmd[i + 1][1], O_RDWR | O_APPEND | O_CREAT, 0777);
		else if (ft_strncmp(tkn->cmd_lex[i + 1][0], "GREAT", 5) == 0)
			tkn->fd = open(tkn->cmd[i + 1][1], O_RDWR | O_TRUNC | O_CREAT, 0777);
	}
	if (tkn->fd < 0)
	{
		printf("bash: %s: Arquivo ou diretório inexistente\n", tkn->cmd[i][1]);
		return (1);
	}
	else
		dup2(tkn->fd, STDOUT_FILENO);
	close(fd[1]);
	if (built_in_cmd(tkn, i) == 1)
	{
		if (execve(tkn->path_0, tkn->cmd[i], NULL) == -1)
		{
			write(2, "error execve\n", 13);
			exit(1);
		}
		exit_shell(tkn);
	}
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
