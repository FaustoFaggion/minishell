#include "minishell.h"

static int	validate_var(t_tkn *tkn, int i)
{
	int	x;

	if (ft_isdigit(tkn->cmd[i][1][0]) == 0 || ft_strncmp(tkn->cmd[i][1], "=", 1) == 0)
		return (1);
	printf("%s ", tkn->cmd[i][0]);
	printf("%s ", tkn->cmd[i][1]);
	x = 0;
	while (tkn->cmd[i][1][x] != '\0')
	{
		printf("%c ", tkn->cmd[i][1][x]);
		if (tkn->cmd[i][1][x] != '=')
			return (0);
		x++;
	}
	return (1);
}

void	exec_cmd_export(t_tkn *tkn, int i)
{
	int		x;
	char	**temp;
	char	**var;
	char	*swap;
	char	*swap_2;

	if (validate_var(tkn, i) == 1)
	{
		printf("bash: export: `%s`: não é um identificador válido\n", tkn->cmd[i][1]);
	}
	else
	{
		swap = (char *)malloc(ft_strlen(tkn->cmd[i][1]) + 1);
		ft_memcpy(swap, tkn->cmd[i][1], ft_strlen(tkn->cmd[i][1]) + 1);
		var = ft_split(swap, '=');
		x = 0;
		while (tkn->envp[x] != NULL)
		{
			if (ft_strncmp(tkn->envp[x], var[0], ft_strlen(var[0])) == 0)
			{
				swap_2 = tkn->envp[x];
				tkn->envp[x] = swap;
				free(swap_2);
				return ;
			}
			x++;
		}
		free_tab(&var, 2);
		temp = tkn->envp;
		tkn->envp = NULL;
		tkn->envp = (char **)malloc(sizeof(char *) * (tkn->envp_count + 2));
		x = 0;
		while (temp[x] != NULL)
		{
			tkn->envp[x] = temp[x];
			x++;
		}
		tkn->envp[x] = swap;
		tkn->envp[++x] = NULL;
		tkn->envp_count++;
		printf("count%d\n", tkn->envp_count);
		free(temp);
	}
}	