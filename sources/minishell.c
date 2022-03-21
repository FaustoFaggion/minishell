/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:20:20 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/21 13:11:41 by fagiusep         ###   ########.fr       */
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
		printf("cmd[%d][%d] %s  ", x, y, tkn->cmd[x][y]);
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

static void	init_tkn(t_tkn *tkn, char *envp[])
{
	int		i;
	
	tkn->tokens = NULL;
	tkn->lexemas = NULL;
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			tkn->envp = ft_split(envp[i], ':');
			if (tkn->envp == NULL)
			{
				write(2, "ft_split error on function check\n", 33);
				exit(1);
			}
		}
	}
	tkn->envp_count = 0;
	while (tkn->envp[tkn->envp_count] != NULL)
		tkn->envp_count++;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_tkn	tkn;
	int		x;
	
	if (argc > 1)
		printf("%s", argv[1]);
	while (1)
	{
		init_tkn(&tkn, envp);
		print_dir();
		tkn.line = readline("$ ");
		if (tkn.line == NULL)
			printf ("line = NULL");
		if (ft_strlen(tkn.line) != 0)
			add_history(tkn.line);
		x = token_analysis(&tkn);
		if (x == 0)
		{
			lexical_analysis(&tkn);
			sintax_analysis(&tkn);
			expansion_envp(&tkn);
			expansion_quote(&tkn);
			cmd_tab(&tkn);
			exec_cmd_tab(&tkn);
			if (DEBUG == 1)
				token_recog(&tkn);
			exit_shell(&tkn);
		}
//		exit(0);
		
//		printf("%s\n", line);
	}
}