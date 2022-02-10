#include "minishell.h"

static int	metachar_check(t_cmd *cmd, int i)
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

static int	quotes_check(t_cmd *cmd, int i)
{
	if (cmd->line[i] == '\'')
	{
		i++;
		while (cmd->line[i] != '\'')
		{
			if (cmd->line[i] == '\0')
				return (-1);
			i++;
		}	
		i++;
	}
	else if (cmd->line[i] == '"')
	{
		i++;
		while (cmd->line[i] != '"')
		{
			if (cmd->line[i] == '\0')
				return (-1);
			i++;
		}	
		i++;
	}
	return (i);
}

static void	ft_ptr_count_shell(t_cmd *cmd)
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
		else if (ft_strchr("\'", cmd->line[i]) != NULL || ft_strchr("\"", cmd->line[i]) != NULL)
		{
			i = quotes_check(cmd, i);
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
}

static void	free_tab(t_cmd *cmd, size_t i)
{
	if (cmd->tab_y != NULL)
	{
		while (((int)i - 1) > 0)
		{
			free(cmd->tab_y[i]);
			cmd->tab_y[i] = NULL;
			i--;
		}
		free(cmd->tab_y);
		cmd->tab_y = NULL;
	}
}

int	len_s(t_cmd *cmd, int i)
{
	int	len_ptr;

	len_ptr = 0;
	if (ft_strchr("|<>", cmd->line[i]) != NULL)
	{
		len_ptr = i;
		i = metachar_check(cmd, i);
		len_ptr = i - len_ptr;
	}
	else if (ft_strchr("\'", cmd->line[i]) != NULL || ft_strchr("\"", cmd->line[i]) != NULL)
	{
		len_ptr = i;
		i = quotes_check(cmd, i);
		len_ptr = (i - len_ptr);
	}
	else
	{
		while (ft_strchr("|<> ", cmd->line[i + len_ptr]) == NULL && cmd->line[i + len_ptr] != '\0')
			len_ptr++;
	}
	return (len_ptr);
}

static char	**mal_sub(t_cmd *cmd)
{
	int	len_ptr;
	int	x;
	int	y;
	int	z;
	int	flag;

	x = 0;
	y = 0;
	z = 0;
	flag = 1;
	cmd->tab_y = (char **)malloc(((sizeof(char *)) * (cmd->y_tab + 1)));
	if (!cmd->tab_x)
		return(NULL);
	while (cmd->line[z] != '\0')
	{
		while (cmd->line[z] == ' ' && cmd->line[z] != '\0')
			z++;
		if (ft_strchr("|<>", cmd->line[z]) == NULL)
		{
			len_ptr = len_s(cmd, z);
			cmd->tab_y[y] = ft_substr(cmd->line, z, len_ptr);
			if (cmd->tab_y[y] == NULL)
				free_tab(cmd, cmd->y_tab);
			printf ("tab_y %s\n", cmd->tab_y[y]);
			z = z + len_ptr;
			y++;
			flag = 0;
		}
		else
		{
			if (flag == 0)
			{
				while (y < cmd->y_tab)
				{
					cmd->tab_y[y] = NULL;
					y++;
				}
			
				cmd->tab_x[x] = cmd->tab_y;
				cmd->tab_y = (char **)malloc(((sizeof(char *)) * (cmd->y_tab + 1)));
				x++;
				y = 0;
			}
			len_ptr = len_s(cmd, z);
			cmd->tab_y[y] = ft_substr(cmd->line, z, len_ptr);
			if (cmd->tab_y[y] == NULL)
				free_tab(cmd, cmd->y_tab);
			z = z + len_ptr;
			y++;
			while (y < cmd->y_tab)
			{
				cmd->tab_y[y] = NULL;
				y++;
			}
			cmd->tab_x[x] = cmd->tab_y;
			cmd->tab_y = (char **)malloc(((sizeof(char *)) * (cmd->y_tab + 1)));
			if (cmd->line[z] == '\0')
			{
				free(cmd->tab_y);
				cmd->tab_y = NULL;
			}

			if (!cmd->tab_x)
				break ;
			
			x++;
			y = 0;
			flag = 1;
		}
	}
	if (cmd->line[z] == '\0')
	{
		if (cmd->tab_y != NULL)
		{
			while (y < cmd->y_tab)
			{
				cmd->tab_y[y] = NULL;
				y++;
			}
			cmd->tab_x[x] = cmd->tab_y;
			cmd->tab_x[x + 1] = NULL;
		}
		else
		{
			free(cmd->tab_y);
			cmd->tab_x[x] = NULL;
		}
	}
	return (cmd->tab_y);
}

char	***parse_cmd_tab(t_cmd *cmd)
{
	if (!cmd->line)
		return (NULL);
	ft_ptr_count_shell(cmd);
	cmd->tab_x = (char ***)malloc(((sizeof(char *)) * (cmd->x_tab + 1)));
	if (!cmd->tab_x)
		return (NULL);
	mal_sub(cmd);
	return (cmd->tab_x);
}
