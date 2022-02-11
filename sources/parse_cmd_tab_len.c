#include "minishell.h"

int	metachar_check(t_cmd *cmd, int i)
{
	if (cmd->line[i] == '|')
		i++;
	else if (cmd->line[i] == '<')
	{
		i++;
		if (cmd->line[i] == '<')
			i++;
	}
	else if (cmd->line[i] == '>')
	{
		i++;
		if (cmd->line[i] == '>')
			i++;
	}
	return (i);
}

int	quotes_check(t_cmd *cmd, int i, char c)
{
	i++;
	while (cmd->line[i] != c)
	{
		if (cmd->line[i] == '\0')
		{
			exit_shell(cmd);
			exit(1);
		}
		i++;
	}	
	i++;
	return (i);
}

int	parse_cmd_tab_len(t_cmd *cmd, int i)
{
	int	len_ptr;

	len_ptr = 0;
	if (ft_strchr("|<>", cmd->line[i]) != NULL)
	{
		len_ptr = i;
		i = metachar_check(cmd, i);
		len_ptr = i - len_ptr;
	}
	else if (ft_strchr("\'\"", cmd->line[i]) != NULL)
	{
		len_ptr = i;
		i = quotes_check(cmd, i, cmd->line[i]);
		len_ptr = (i - len_ptr);
	}
	else
	{
		while (ft_strchr("|<> ", cmd->line[i + len_ptr]) == NULL
			&& cmd->line[i + len_ptr] != '\0')
			len_ptr++;
	}
	return (len_ptr);
}
