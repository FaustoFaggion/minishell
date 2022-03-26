/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:10:58 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/26 17:10:59 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd_envp(t_tkn *tkn)
{
	int	i;

	i = 0;
	while (tkn->envp[i] != NULL)
	{
		printf("%s\n", tkn->envp[i]);
		i++;
	}
}
