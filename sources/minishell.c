/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:20:20 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/07 16:01:22 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	token_recog(t_tkn *tkn)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	printf ("TOKENS = ");
	while (tkn->lexemas[i] != NULL)
	{
		printf ("%s  ", tkn->tokens[i]);
		i++;
	}
	printf ("%s  ", tkn->tokens[i]);
	printf ("\n");
	i = 0;
	printf ("LEXEMAS = ");
	while (tkn->lexemas[i] != NULL)
	{
		printf ("%s  ", tkn->lexemas[i]);
		i++;
	}
	printf ("%s  ", tkn->lexemas[i]);
	printf ("\n");
	x = 0;
	y = 0;
	while (tkn->cmd[x] != NULL)
	{
		y = 0;
		while (tkn->cmd[x][y] != NULL)
		{
			printf("cmd[%d][%d] %s  ", x, y, tkn->cmd[x][y]);
			y++;
		}
		printf("%s  ", tkn->cmd[x][y]);
		printf("\n");
		x++;
	}
	printf("cmd[%d] %p\n", x, tkn->cmd[x]);
}

static void	print_dir(void)
{
	char		dir[1024];
	char		*user;
//	char		*hostname;

	user = getenv("USER");
	printf("%s@ ", user);
	getcwd(dir, sizeof(dir));
	printf("%s", dir);
}

int	main(void)
{
	t_tkn		tkn;
	t_filename	filename;

	ft_bzero(&tkn, sizeof(tkn));
	ft_bzero(&filename, sizeof(filename));
	while (1)
	{
		print_dir();
		tkn.line = readline("$ ");
		if (tkn.line == NULL)
			printf ("line = NULL");
		if (ft_strlen(tkn.line) != 0)
			add_history(tkn.line);
		token_analysis(&tkn);
		lexical_analysis(&tkn);
		sintax_analysis(&tkn);
		expansion_envp(&tkn);
		expansion_quote(&tkn);
		cmd_tab(&tkn);
		exec_cmd_tab(&tkn);
		if (DEBUG == 1)
			token_recog(&tkn);
		exit_shell(&tkn);
		
//		printf("%s\n", line);
//		exit(0);
	}
}