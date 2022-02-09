#include "minishell.h"

static void print_dir()
{
	char		*user;
//	char		*host;
	char		dir[1024];

	user = getenv("USER");
	printf("%s@ ", user);
	getcwd(dir, sizeof(dir));
	printf("%s", dir);
}

static void token_recog(t_cmd *cmd)
{
	int	i;
	
	split_minishell(cmd);
	i = 0;
/*	while (cmd->tab[x][y])
	{
		y = 0;
		while (cmd->tab[x][y])
		{
			printf("%s\n", cmd->tab[x][y]);
			y++;
		}
		x++;
	}*/
//	tab = split_minishell_2(tab_0);
	while (cmd->tab[i])
	{
		printf("%s\n", cmd->tab[i]);
		i++;
	}
}

int main(void)
{
	t_cmd cmd;
	
	while(1)
	{
		print_dir();
		cmd.line = readline("$ ");
		add_history(cmd.line);
		token_recog(&cmd);
//		printf("%s\n", line);
		free(cmd.line);
	}

}