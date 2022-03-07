#include "minishell.h"

void	cmd_not_found(t_tkn *tkn, int i)
{
	write(1, tkn->cmd[i][0], ft_strlen(tkn->cmd[i][0]));
	write(1, ": Command not found\n", 20);
}

int	cmd_setup(t_tkn *tkn, int i)
{
	int		x;
	char	**swap;
	char	**path;
	char	*temp;

	temp = getenv("PATH");
	swap = ft_split(temp, ':');

	path = swap;
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

int	exec_child(t_tkn *tkn, int fd[], int i)
{

	if (tkn->cmd[i + 1] != NULL)
	{
		if (ft_strncmp(tkn->cmd[i + 1][0], "|", 1) == 0 )
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
	}
	if (execve(tkn->path, tkn->cmd[i], NULL) == -1)
	{
		write(2, "error execve\n", 13);
		exit(1);
	}
	exit(0);
	return (0);
}

void	exec_cmd_tab(t_tkn *tkn)
{
	int	i;
	int	fd[2];
	int	pid;

	i = 0;
	while (tkn->cmd[i] != NULL)
	{
		if (tkn->cmd[i + 1] != NULL)
		{
			if (ft_strncmp(tkn->cmd[i + 1][0], "|", 1) == 0 )
			{
				if (pipe(fd) == -1)
					exit(write(1, "pipe error\n", 11));
			}
		}
		if (cmd_setup(tkn, i) == 0)
		{
			pid = fork();
			if (pid < 0)
				exit(write(1, "fork error\n", 11));
			if (pid == 0)
				exec_child(tkn, fd, i);
			waitpid(pid, NULL, 0);
		}
		if (tkn->cmd[i + 1] != NULL)
		{
			if (ft_strncmp(tkn->cmd[i + 1][0], "|", 1) == 0 )
			{
				close(fd[1]);
				dup2(fd[0], STDIN_FILENO);
				close(fd[0]);
				i++;
			}
		}

		i++;
	}
	dup2(1, STDIN_FILENO);
}
