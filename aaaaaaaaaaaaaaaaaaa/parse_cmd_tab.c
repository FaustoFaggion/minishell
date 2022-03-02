/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 20:40:17 by fagiusep          #+#    #+#             */
/*   Updated: 2022/02/14 14:34:18 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***parse_cmd_tab(t_cmd *cmd)
{
	if (!cmd->line)
		return (NULL);
	parse_cmd_tab_count(cmd);
	cmd->grammar = (char **) malloc(sizeof(char *) * (cmd->size_grammar + 1));
	if (!cmd->grammar)
		return (NULL);
	cmd->tab_x = (char ***)malloc((sizeof(char *) * (cmd->size_tab_x + 1)));
	if (!cmd->tab_x)
		return (NULL);
	parse_cmd_tab_malloc(cmd);
	return (cmd->tab_x);
}
