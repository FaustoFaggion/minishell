/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:09:47 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/30 10:34:17 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_var(t_tkn *tkn, char *var)
{
	char	**temp;
	int		x;
	int		y;

	temp = (char **)malloc((tkn->envp_count) * sizeof(char *));
	x = 0;
	y = 0;
	while (tkn->envp[x + y] != NULL)
	{
		if (ft_strncmp(tkn->envp[x + y], var, ft_strlen(var)) == 0)
			y++;
		else
		{
			temp[x] = ft_strdup(tkn->envp[x + y]);
			x++;
		}
	}
	temp[x] = NULL;
	free_tab(&tkn->envp, tkn->envp_count);
	tkn->envp = temp;
	tkn->envp_count--;
}

void	exec_cmd_unset(t_tkn *tkn, char *cmd_arg)
{
	int		x;
	int		flag;
	char	*var;
	
	flag = 0;
	x = 0;
	if (ft_strncmp(cmd_arg, "PATH\0", 5) == 0 || ft_strncmp(cmd_arg, "HOME\0", 5) == 0)
	{
		printf("\n");
		return ;
	}
	var = ft_strjoin(cmd_arg, "=");
	while (tkn->envp[x] != NULL)
	{
		if (ft_strncmp(tkn->envp[x], var,
			ft_strlen(var)) == 0)
			flag = 1;
		x++;
	}
	if (flag == 1)
		unset_var(tkn, var);
	free(var);
}
