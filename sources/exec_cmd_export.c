/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:21:14 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/30 15:40:44 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_var(char *cmd_arg)
{
	int	x;

	if (ft_isdigit(cmd_arg[0]) == 0
			|| ft_strncmp(cmd_arg, "=", 1) == 0)
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

void	exec_cmd_export(char ***envp, char *cmd_arg, int *count)
{
	int		x;
	char	**temp;
	char	**var;
	char	*swap;
	char	*swap_2;

	if (validate_var(cmd_arg) == 1)
		printf("bash: export: `%s`: não é um identificador válido\n", cmd_arg);
	else
	{
		swap = (char *)malloc(ft_strlen(cmd_arg) + 1);
		ft_memcpy(swap, cmd_arg, ft_strlen(cmd_arg) + 1);
		var = ft_split(swap, '=');
		x = 0;
		while ((*envp)[x] != NULL)
		{
			if (ft_strncmp((*envp)[x], var[0], ft_strlen(var[0])) == 0)
			{
				swap_2 = (*envp)[x];
				(*envp)[x] = ft_strdup(swap);
				free(swap_2);
				free(swap);
				free_tab(&var, 2);
				return ;
			}
			x++;
		}
		free_tab(&var, 2);
		temp = (*envp);
		(*envp) = (char **)malloc(sizeof(char *) * (*count + 2));
		x = 0;
		while (temp[x] != NULL)
		{
			(*envp)[x] = ft_strdup(temp[x]);
			x++;
		}
		(*envp)[x] = swap;
		(*envp)[++x] = NULL;
		free_tab(&temp, *count);
		(*count)++;
	}
}
