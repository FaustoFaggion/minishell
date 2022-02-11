#include "minishell.h"

void	parse_ptr_count(t_cmd *cmd)
{
	int	i;
	int	count_y;
	int	flag;

	i = 0;
	count_y = 0;
	flag = 1;
	cmd->x_tab = 0;
	cmd->y_tab = 0;
	while (cmd->line[i] != '\0')
	{
		while (cmd->line[i] == ' ' && cmd->line[i] != '\0')
			i++;
		if (ft_strchr("|<>", cmd->line[i]) != NULL)
		{
			i = metachar_check(cmd, i);
			cmd->x_tab++;
			count_y = 1;
			if (count_y > cmd->y_tab)
				cmd->y_tab = count_y;
			count_y = 0;
			flag = 1;
		}
		else if (ft_strchr("\'\"", cmd->line[i]) != NULL)
		{
			i = quotes_check(cmd, i, cmd->line[i]);
			if (i == -1)
			{
				write(2, "ERROR\nUnclosed quote.\n", 21);
				exit(1);
			}
			count_y++;
			if (count_y > cmd->y_tab)
				cmd->y_tab = count_y;
			if (flag == 1)
			{
				cmd->x_tab++;
				flag = 0;
			}
		}
		else
		{
			while (ft_strchr("|<> ", cmd->line[i]) == NULL)
				i++;
			count_y++;
			if (count_y > cmd->y_tab)
				cmd->y_tab = count_y;
			if (flag == 1)
			{
				cmd->x_tab++;
				flag = 0;
			}
		}
	}
	cmd->y_tab++;
}