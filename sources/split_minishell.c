/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:13:26 by fagiusep          #+#    #+#             */
/*   Updated: 2022/02/09 17:37:43 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	i = 0;
	cmd->y_tab = 0;
	while (cmd->line[i] != '\0')
	{
		while (cmd->line[i] == ' ' && cmd->line[i] != '\0')
			i++;
		if (ft_strchr("|<>", cmd->line[i]) != NULL)
		{
			i = metachar_check(cmd, i);
			cmd->y_tab++;
		}
		else if (ft_strchr("\'", cmd->line[i]) != NULL || ft_strchr("\"", cmd->line[i]) != NULL)
		{
			i = quotes_check(cmd, i);
			if (i == -1)
			{
				write(2, "ERROR\nUnclosed quote.\n", 21);
				exit(1);
			}
			cmd->y_tab++;
		}
		else
		{
			while (ft_strchr("|<> ", cmd->line[i]) == NULL)
				i++;
			cmd->y_tab++;
		}
	}
}

static void	free_tab(t_cmd *cmd, size_t i)
{
	while ((int)i >= 0)
	{
		free(cmd->tab[i]);
		cmd->tab[i] = NULL;
		i--;
	}
	free(cmd->tab);
	cmd->tab = NULL;
	
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

static void	mal_sub(t_cmd *cmd)
{
	int	len_ptr;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cmd->y_tab)
	{
		while (cmd->line[j] == ' ' && cmd->line[j] != '\0')
			j++;
		len_ptr = len_s(cmd, j);
		cmd->tab[i] = ft_substr(cmd->line, j, len_ptr);
		if (cmd->tab[i] == NULL)
			free_tab(cmd, i);
		j = j + len_ptr;
		i++;
	}
	cmd->tab[i] = NULL;
}

char	**split_minishell(t_cmd *cmd)
{
	if (!cmd->line)
		return (NULL);
	ft_ptr_count_shell(cmd);
	cmd->tab = (char **)malloc(((sizeof(char *)) * (cmd->y_tab + 1)));
	if (!cmd->tab)
		return (NULL);
	mal_sub(cmd);
	return (cmd->tab);
}
