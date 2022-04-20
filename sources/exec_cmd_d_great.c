/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_d_great.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:16:28 by fagiusep          #+#    #+#             */
/*   Updated: 2022/04/20 09:22:54 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd_d_great(t_tkn *tkn)
{
	if (ft_strncmp(tkn->cmd_lex[tkn->i_cmd][0], "DGREAT", 6) == 0)
	{
		tkn->fd_out = open(tkn->cmd[tkn->i_cmd][1], O_RDWR | O_APPEND
				| O_CREAT, 0777);
	}
	else if (ft_strncmp(tkn->cmd_lex[tkn->i_cmd][0], "GREAT", 5) == 0)
	{
		tkn->fd_out = open(tkn->cmd[tkn->i_cmd][1], O_RDWR | O_TRUNC
				| O_CREAT, 0777);
	}
}
