/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:20:20 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/04 12:48:44 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_dir(void)
{
	char		dir[1024];
	char		*user;
//	char		*host;

	user = getenv("USER");
	printf("%s@ ", user);
	getcwd(dir, sizeof(dir));
	printf("%s", dir);
}

static void	token_recog(t_tkn *tkn)
{
	int	i;
	
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
//	parse_cmd_tab(cmd);
	/*
	printf("x = %d, y = %d\n", cmd->size_tab_x, cmd->size_tab_y);
	while (x < cmd->size_tab_x)
	{
		y = 0;
		while (y < cmd->size_tab_y)
		{
			printf("%s  ", cmd->tab_x[x][y]);
			y++;
		}
		printf("\n");
		x++;
	}
	printf("gam_count %d\n", cmd->size_grammar);
	*/
}

int	main(int argc,char *argv[])
{
	t_tkn		tkn;
	t_filename	filename;
	int	i;
	i = argc;
	
	ft_bzero(&tkn, sizeof(tkn));
	ft_bzero(&filename, sizeof(filename));
	while (1)
	{
		print_dir();
		tkn.line = readline("$ ");
		add_history(tkn.line);
		token_analysis(&tkn);
		lexical_analysis(&tkn);
		sintax_analysis(&tkn);
		expansion_envp(&tkn);
		expansion_quote(&tkn);
		i = 0;
/*		while (envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
		
*/		
		printf("v=%s\n", argv[0]);
	
		token_recog(&tkn);
//		printf("%s\n", line);
		exit_shell(&tkn);
		free(tkn.line);
		exit(0);
	}
}
