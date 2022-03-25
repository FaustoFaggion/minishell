/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:20:20 by fagiusep          #+#    #+#             */
/*   Updated: 2022/03/25 17:40:03 by fagiusep         ###   ########.fr       */
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

static void	init_tkn(t_tkn *tkn)
{
	int		i;
	char	**temp;
	
	tkn->tokens = NULL;
	tkn->lexemas = NULL;
	tkn->path_0 = NULL;
	i = -1;
	while (tkn->envp[++i] != NULL)
	{
		if (ft_strncmp("PATH=", tkn->envp[i], 5) == 0)
		{
			temp = ft_split(tkn->envp[i], '=');
			tkn->path = ft_split(temp[1], ':');
			if (tkn->path == NULL)
			{
				write(2, "ft_split error on function check\n", 33);
				exit(1);
			}
			free_tab(&temp, 2);
		}
	}
	tkn->path_count = 0;
	while (tkn->path[tkn->path_count] != NULL)
		tkn->path_count++;
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
	x = 0;
	while (envp[x] != NULL)
		x++;
	tkn.envp = (char **)malloc((x + 1) * sizeof(char *));
	x = 0;
	while (envp[x] != NULL)
	{
		tkn.envp[x] = ft_strdup(envp[x]);
		x++;
	}
	tkn.envp[x] = NULL;
	tkn.envp_count = 0;
	while (tkn.envp[tkn.envp_count] != NULL)
		tkn.envp_count++;
	while (1)
	{
		init_tkn(&tkn);
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
//			expansion_envp(&tkn);
			expansion(&tkn);
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