/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:21:14 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/19 11:06:17 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_var(char *cmd_arg)
{
	int	x;

	if (ft_isdigit(cmd_arg[0]) == 0)
		return (1);
	else if (ft_strncmp(cmd_arg, "=", 1) == 0)
		return (1);
	x = 0;
	while (cmd_arg[x] != '\0')
	{
		if (cmd_arg[x] == '=')
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

	if (validate_var(tkn->cmd[i][1]) == 1)
		setup_error(tkn->cmd[i][1], 6);
	else
	{
		if (tkn->cmd[i][1] == NULL)
		{
			exec_cmd_env(tkn, 1);
			return ;
		}
		swap = (char *)malloc(ft_strlen(tkn->cmd[i][1]) + 1);
		ft_memcpy(swap, tkn->cmd[i][1], ft_strlen(tkn->cmd[i][1]) + 1);
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
		free_tab(&var, 2);
		temp = tkn->envp;
		tkn->envp = (char **)malloc(sizeof(char *) * (tkn->envp_count + 2));
		x = 0;
		while (temp[x] != NULL)
		{
			tkn->envp[x] = ft_strdup(temp[x]);
			x++;
		}
		tkn->envp[x] = swap;
		tkn->envp[++x] = NULL;
		free_tab(&temp, tkn->envp_count);
		tkn->envp_count++;
	}
}
