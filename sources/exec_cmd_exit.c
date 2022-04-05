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
		if (j == 0 && tkn->cmd[i][1][j] != '+' && tkn->cmd[i][1][j] != '-'
					&& ft_isdigit(tkn->cmd[i][1][j]) == 1)
			flag = 1;
		if (j != 0 && ft_isdigit(tkn->cmd[i][1][j]) == 1)
			flag = 1;
		j++;
	}

	return (flag);
}

static int	not_valid_exit(t_tkn *tkn, int i, int len, int is_digit)
{
	if (is_digit == 1)
	{
		ft_putendl_fd("exit:\nexit: ", 2);
		ft_putendl_fd(tkn->cmd[i][1], 2);
		ft_putendl_fd(": requer argumento numérico\n", 2);
		global_exit = 2;
		return (1);
	}
	else if (len > 2)
	{
		ft_putendl_fd("exit\nbash: exit: número excessivo de argumentos\n", 2);
		global_exit = 1;
		return (1);
	}
	return (0);
}

void	exec_cmd_exit(t_tkn *tkn, int i)
{
	int	len;
	int	is_digit;

	if (tkn->cmd[i][1] == NULL)
		global_exit = 0;
	else
	{
		len = cmd_size(tkn, i);
		is_digit = cmd_digit(tkn, i);
		if (not_valid_exit(tkn, i, len, is_digit) == 1)
			return;
		else
		{
			if (ft_atoi(tkn->cmd[i][1]) > 256)
				global_exit = (ft_atoi(tkn->cmd[i][1]) % 256);
			else
				global_exit = (ft_atoi(tkn->cmd[i][1]));
		}
	}
		
		exit_shell(tkn);
		free_tab(&tkn->envp, tkn->envp_count);
		rl_clear_history();
		exit(global_exit);
	
}
