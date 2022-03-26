#include "minishell.h"

static void	unset_var(t_tkn *tkn, int i)
{
	char	**temp;
	char	*temp_2;
	int		x;
	int		y;

	temp = (char **)malloc((tkn->envp_count) * sizeof(char *));
	x = 0;
	y = 0;
	temp_2 = ft_strjoin(tkn->cmd[i][1], "=");
	while (tkn->envp[x + y] != NULL)
	{
		if (ft_strncmp(tkn->envp[x + y], temp_2, ft_strlen(temp_2)) == 0)
			y++;
		else
		{
			temp[x] = ft_strdup(tkn->envp[x + y]);
			x++;
		}
	}
	temp[x] = NULL;
	free_tab(&tkn->envp, tkn->envp_count);
	free(temp_2);
	tkn->envp = temp;
	tkn->envp_count = x;
}

void	exec_cmd_unset(t_tkn *tkn, int i)
{
	int		x;
	int		flag;

	flag = 0;
	x = 0;
	while (tkn->envp[x] != NULL)
	{
		if (ft_strncmp(tkn->envp[x], tkn->cmd[i][1], ft_strlen(tkn->cmd[i][1])) == 0)
			flag = 1;
		x++;
	}
	if (flag == 1)
		unset_var(tkn, i);
}	
