#include "minishell.h"

void	exec_cmd_cd(t_tkn *tkn, int i)
{
	//char	*swap;
	int		x;
	char		dir[1024];

	if (tkn->cmd[i][1] == NULL)
		chdir("/home");
	else if (tkn->cmd[i][2] != NULL)
		printf("bah: cd: número excessivo de argumentos\n");
	else
	{
		if (chdir(tkn->cmd[i][1]) == -1)
			printf("bash: %s: Arquivo ou diretório inexistente\n", tkn->cmd[i][1]);
	}
	x = 0;
	while (tkn->envp[x])
	{
		if (ft_strncmp(tkn->envp[x], "PWD=", 4) == 0)
		{
		//	swap = tkn->envp[x];
			getcwd(dir, sizeof(dir));
			tkn->envp[x] = ft_strjoin("PWD=", dir);
		//	free(swap);
			break ;
		}
		x++;
	}
/*	x = 0;
	while (tkn->envp[x])
	{
		printf("%s\n", tkn->envp[x]);
		x++;
	}
*/
}