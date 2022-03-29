#include "minishell.h"

static int	built_in_utils(t_tkn *tkn, int i)
{
	if (ft_strncmp(tkn->cmd[i][0], "export\0", 7) == 0)
	{
		exec_cmd_export(tkn, tkn->cmd[i][1]);
		return (0);
	}
	else if (ft_strncmp(tkn->cmd[i][0], "unset\0", 6) == 0)
	{
		exec_cmd_unset(tkn, tkn->cmd[i][1]);
		return (0);
	}
	else if (ft_strncmp(tkn->cmd[i][0], "env\0", 4) == 0)
	{
		exec_cmd_envp(tkn);
		return (0);
	}
	else if (ft_strncmp(tkn->cmd[i][0], "exit\0", 5) == 0)
	{
		exec_cmd_exit(tkn, i);
		return (0);
	}
	return (1);
}

int	built_in_cmd(t_tkn *tkn, int i)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(tkn->cmd[i][0], "echo\0", 5) == 0)
	{
		exec_cmd_echo(tkn, i);
		return (ret);
	}
	else if (ft_strncmp(tkn->cmd[i][0], "pwd\0", 4) == 0)
	{
		exec_cmd_pwd();
		return (ret);
	}
	else if (ft_strncmp(tkn->cmd[i][0], "cd\0", 3) == 0)
	{
		exec_cmd_cd(tkn, i);
		return (ret);
	}
	else
	{
		ret = built_in_utils(tkn, i);
		return (ret);
	}
	return (1);
}