#include "minishell.h"

void	exec_cmd_envp(t_tkn *tkn)
{
	int	i;

	i = 0;
	while (tkn->envp[i] != NULL)
	{
		printf("%s\n", tkn->envp[i]);
		i++;
	}
}