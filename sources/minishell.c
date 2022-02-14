/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:20:20 by fagiusep          #+#    #+#             */
/*   Updated: 2022/02/14 14:33:33 by fagiusep         ###   ########.fr       */
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

static void	token_recog(t_cmd *cmd)
{
	int	x;
	int	y;

	parse_cmd_tab(cmd);
	x = 0;
	y = 0;
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
}

int	main(void)
{
	t_cmd	cmd;

	while (1)
	{
		print_dir();
		cmd.line = readline("$ ");
		add_history(cmd.line);
		token_recog(&cmd);
//		printf("%s\n", line);
		exit_shell(&cmd);
		free(cmd.line);
		exit(0);
	}
}
