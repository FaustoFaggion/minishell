/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:06:35 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/30 10:52:08 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	especial_char(t_tkn *tkn, int i, int j)
{
	char	*user;
	
	if (ft_strncmp(tkn->cmd[i][j], "~\0", 2) == 0
		|| ft_strncmp(tkn->cmd[i][j], "~\\0", 3) == 0)
	{
		user = getenv("USER");
		printf("/home/%s", user);
	}
	else
		printf("%s ", tkn->cmd[i][j]);

}

void	exec_cmd_echo(t_tkn *tkn, int i)
{
	int	j;

	j = 1;
	if (tkn->cmd[i][1] == NULL)
	{
		printf("\n");
		return ;
	}
	if (ft_strncmp(tkn->cmd[i][1], "-n", 2) == 0)
		j = 2;
	while (tkn->cmd[i][j] != NULL)
	{
		especial_char(tkn, i, j);
		j++;
	}
	if (ft_strncmp(tkn->cmd[i][1], "-n", 2) != 0)
		printf("\n");
	return ;
}
