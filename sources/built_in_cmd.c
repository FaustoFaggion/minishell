/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:08:07 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/20 10:32:38 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static int	validate_var(t_tkn *tkn, int i)
{
	int	x;

	if (tkn->tokens[i + 1] != NULL)
		return (1);
	if (ft_isdigit(tkn->tokens[i][0]) == 0
			|| ft_strncmp(tkn->tokens[i], "=", 1) == 0)
		return (1);
	x = 0;
	while (tkn->tokens[i][x] != '\0')
	{
		if (tkn->tokens[i][x] == '=')
			return (0);
		x++;
	}
	return (1);
}

static void	prepare_amb_var(t_tkn *tkn, int i)
{
	int		x;
	char	**temp;
	char	**var;
	char	*swap;
	char	*swap_2;

	if (validate_var(tkn, i) == 1)
		return ;
	else
	{
		swap = (char *)malloc(ft_strlen(tkn->tokens[i]) + 1);
		ft_memcpy(swap, tkn->tokens[i], ft_strlen(tkn->tokens[i]) + 1);
		var = ft_split(swap, '=');
		x = 0;
		while (tkn->envp[x] != NULL)
		{
			if (ft_strncmp(tkn->envp[x], var[0], ft_strlen(var[0])) == 0)
			{
				swap_2 = tkn->envp[x];
				tkn->envp[x] = ft_strdup(swap);
				free(swap_2);
				free(swap);
				free_tab(&var, 2);
				return ;
			}
			x++;
		}
		x = 0;
		if (tkn->amb_v != NULL)
		{
			while (tkn->amb_v[x] != NULL)
			{
				if (ft_strncmp(tkn->amb_v[x], var[0], ft_strlen(var[0])) == 0)
				{
					swap_2 = tkn->amb_v[x];
					tkn->amb_v[x] = ft_strdup(swap);
					free(swap_2);
					free(swap);
					free_tab(&var, 2);
					return ;
				}
				x++;
			}
		}
		tkn->amb_v_count = x;
		free_tab(&var, 2);
		temp = NULL;
		if (tkn->amb_v != NULL)
			temp = tkn->amb_v;
		tkn->amb_v = (char **)malloc(sizeof(char *) * (tkn->amb_v_count + 2));
		x = 0;
		if (temp != NULL)
		{
			while (temp[x] != NULL)
			{
				tkn->amb_v[x] = ft_strdup(temp[x]);
				x++;
			}
		}
		tkn->amb_v[x] = swap;
		tkn->amb_v[++x] = NULL;
		free_tab(&temp, tkn->amb_v_count);
		tkn->amb_v_count++;
	}
}
*/
static int	built_in_utils(t_tkn *tkn, int i)
{
	if (ft_strncmp(tkn->cmd[i][0], "export\0", 7) == 0)
	{
		exec_cmd_export(tkn, i);
		return (0);
	}
	else if (ft_strncmp(tkn->cmd[i][0], "unset\0", 6) == 0)
	{
		exec_cmd_unset(&tkn->envp, tkn->cmd[i][1], &tkn->envp_count);
		return (0);
	}
	else if (ft_strncmp(tkn->cmd[i][0], "env\0", 4) == 0)
	{
		if (tkn->cmd[i][1] == NULL)
			exec_cmd_env(tkn, 0);
		return (0);
	}
	else if (ft_strncmp(tkn->cmd[i][0], "exit\0", 5) == 0)
	{
		exec_cmd_exit(tkn, i);
		return (0);
	}
/*	
	else if (ft_strncmp(tkn->cmd_lex[i][0], "ASSIGNMENT_WORD", 15) == 0)
	{
		printf("\n\n................\n\n");
		if (ft_strchr(tkn->cmd[i][0], '=') != NULL)
		{
			prepare_amb_var(tkn, i);
			return (0);
		}
	}
*/
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
