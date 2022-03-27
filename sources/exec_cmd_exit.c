#include "minishell.h"

static int	cmd_size(t_tkn *tkn, int i)
{
	int j;

	j = 0;
	while (tkn->cmd[i][j] != NULL)
		j++;
	return (j);
}

static int	cmd_digit(t_tkn *tkn, int i)
{
	int j;
	int	flag;

	j = 0;
	flag = 0;
	while (tkn->cmd[i][1][j] != '\0')
	{
		if (ft_isdigit(tkn->cmd[i][1][j]) == 1)
		{
			flag = 1;
		}
		j++;
	}

	return (flag);
}

void	exec_cmd_exit(t_tkn *tkn, int i)
{
	int	len;
	int	is_digit;
	int	ret;

	len = cmd_size(tkn, i);
	printf("len %d", len);
	is_digit = cmd_digit(tkn, i);
	if (is_digit == 1)
	{
		ft_putendl_fd("exit:\nexit: ", 2);
		ft_putendl_fd(tkn->cmd[i][1], 2);
		ft_putendl_fd(": requer argumento numérico\n", 2);
		return ;
	}
	else if (len > 2)
	{
		ft_putendl_fd("exit\nbash: exit: número excessivo de argumentos\n", 2);
		tkn->exit_signal = 2
		return ;
	}
	if (tkn->cmd[i][1] == NULL)
		ret = 0;
	else
		ret = ft_atoi(tkn->cmd[i][1]);
	
	exit_shell(tkn);
	free_tab(&tkn->envp, tkn->envp_count);
	rl_clear_history();
	exit(ret);



}
