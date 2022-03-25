#include "minishell.h"


void	exec_cmd_unset(t_tkn *tkn, int i)
{
	int		x;
	int		flag;
	int		y;
	char	**temp;

	flag = 0;
	x = 0;
	while (tkn->envp[x] != NULL)
	{
		if (ft_strncmp(tkn->envp[x], tkn->cmd[i][1], ft_strlen(tkn->cmd[i][1])) == 0)
			flag = 1;
		x++;
	}
	if (flag == 1)
	{
		temp = (char **)malloc((tkn->envp_count) * sizeof(char *));
		x = 0;
		y = 0;
		while (tkn->envp[x + y] != NULL)
		{
			if (ft_strncmp(tkn->envp[x], tkn->cmd[i][1], ft_strlen(tkn->cmd[i][1])) != 0)
				y++;
			else
			{
				temp[x] = ft_strdup(tkn->envp[x + y]);
				x++;
			}
		}
		temp[x] = NULL;
		free_tab(&tkn->envp, 2);
		tkn->envp = temp;
		tkn->envp_count--;
	}
}	
