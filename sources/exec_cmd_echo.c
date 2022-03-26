#include "minishell.h"

void	exec_cmd_echo(t_tkn *tkn, int i)
{
	int	j;

	j = 1;
	if (tkn->cmd[i][1] == NULL)
	{
		printf("\n");
		return ;
	}
	if (ft_strncmp(tkn->cmd[i][1], "-n", 2) == 0)
		j = 2;
	else
	{
		while (tkn->cmd[i][j] != NULL)
		{
			printf(">>>>>%s ", tkn->cmd[i][j]);
			j++;
		}
	}
	if (ft_strncmp(tkn->cmd[i][1], "-n", 2) != 0)
		printf("\n");
	return ;
}