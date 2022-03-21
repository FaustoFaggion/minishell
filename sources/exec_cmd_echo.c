#include "minishell.h"

static int	exec_child(t_tkn *tkn, int i)
{
	int	j;

	j = 1;
	if (tkn->cmd[i][1] == NULL)
	{
		printf("\n");
		exit(0);
	}
	if (ft_strncmp(tkn->cmd[i][1], "-n", 2) == 0)
		j = 2;
	else
	{
		while (tkn->cmd[i][j] != NULL)
		{
			printf("%s", tkn->cmd[i][j]);
			j++;
		}
	}
	if (ft_strncmp(tkn->cmd[i][1], "-n", 2) != 0)
		printf("\n");
	exit(0);
	return (0);
}

void	exec_cmd_echo(t_tkn *tkn, int i)
{
	int pid;

	pid = fork();
		if (pid < 0)
			exit(write(1, "fork error\n", 11));
		if (pid == 0)
			exec_child(tkn, i);
		waitpid(pid, NULL, 0);
}