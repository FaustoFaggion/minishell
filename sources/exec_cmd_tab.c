/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:17:11 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/20 15:58:18 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	special_case(t_tkn *tkn, int i)
{
	int j;

	j = 0;
	if (ft_strncmp(tkn->cmd[i][0], "env\0", 4) == 0 && tkn->cmd[i][1] != NULL)
	{
		free(tkn->cmd[i][j]);
		free(tkn->cmd_lex[i][j]);
		while (tkn->cmd[i][j] != NULL)
		{
			tkn->cmd[i][j] = tkn->cmd[i][j + 1];
			tkn->cmd_lex[i][j] = tkn->cmd_lex[i][j + 1];
			j++;
		}
	}
}

int	cmd_setup(t_tkn *tkn, int i)
{
	int		x;
	char	*temp;

	special_case(tkn, i);
	x = 0;
	if (tkn->path_0 != NULL)
		free(tkn->path_0);
	if (tkn->path != NULL)
	{
		while (tkn->path[x] != NULL)
		{
			tkn->path_0 = ft_strjoin(tkn->path[x], "/");
			if (tkn->path_0 == NULL)
				exit(1);
			temp = tkn->path_0;
			tkn->path_0 = ft_strjoin(temp, tkn->cmd[i][0]);
			free(temp);
			if (tkn->path_0 == NULL)
				exit(1);
			if (access(tkn->path_0, F_OK) == 0)
				return (0);
			free(tkn->path_0);
			tkn->path_0 = NULL;
			x++;
		}
	}
	setup_error(tkn->cmd[i][0], 0);
	return (1);
}

void	exec_cmd_tab(t_tkn *tkn)
{
	tkn->i_cmd = 0;
	while (tkn->cmd[tkn->i_cmd] != NULL)
	{
		if (ft_strncmp(tkn->cmd_lex[tkn->i_cmd][0], "LESS", 4) == 0
				|| ft_strncmp(tkn->cmd_lex[tkn->i_cmd][0], "DLESS", 5) == 0)
		{
			
			exec_cmd_d_less(tkn, tkn->i_cmd);
			tkn->i_cmd++;
		}
		else if (ft_strncmp(tkn->cmd_lex[tkn->i_cmd][0], "GREAT", 5) == 0
				|| ft_strncmp(tkn->cmd_lex[tkn->i_cmd][0], "DGREAT", 6) == 0)
		{
			printf("cmd_great exec_cmd_tab\n");
			exec_cmd_d_great(tkn);
			tkn->i_cmd++;
			
		}
		else if (ft_strncmp(tkn->cmd_lex[tkn->i_cmd][0], "WORD", 4) == 0
			|| ft_strncmp(tkn->cmd_lex[tkn->i_cmd][0], "ASSIGNMENT_WORD", 15) == 0)
		{
			
			if (tkn->cmd[tkn->i_cmd + 1] != NULL
				&& ft_strncmp(tkn->cmd_lex[tkn->i_cmd + 1][0], "PIPE", 4) == 0)
			{
				exec_cmd_pipe(tkn);
				tkn->i_cmd++;
			}
			else 
				exec_cmd_pipe(tkn);
			tkn->i_cmd++;
		}
	}
	dup2(1, STDIN_FILENO);
}
